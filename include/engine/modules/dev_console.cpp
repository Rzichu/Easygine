#include "dev_console.h"

#include "../engine.h"

namespace easygine {
    namespace internal_cmds {
        void cmd_help(CMD_PARAMS params) {
            if (params.empty()) {
                internal_handle_core.developerConsole()->p_CmdHelp(std::string());
            }
            else {
                internal_handle_core.developerConsole()->p_CmdHelp(params.at(0));
            }
        }

        void cmd_clear(CMD_PARAMS params) {
            internal_handle_core.developerConsole()->p_CmdClear();
        }
    }

    namespace utils {
        sf::Time CMD_TOGGLE_DELAY = sf::seconds(0.2f);

        bool DevConsole::init(const std::shared_ptr<interface::GuiScreen> &target) {
            if (target) {
                this->m_TargetGui = target;
                this->m_ConsoleGui = tgui::Group::create({"100%", "35%"});
                this->enableConsole(easygine::CORE::core().gameSettings()->getBoolSetting(GAME_SETTING_CONSOLE_ENABLED, false, false), false);

                auto panel = tgui::TextArea::create();
                panel->setReadOnly(true);
                panel->setPosition({"0", "0"});
                panel->setSize({"100%", "92%"});
                panel->setVerticalScrollbarPolicy(tgui::Scrollbar::Policy::Always);
                panel->getRenderer()->setBackgroundColor(tgui::Color::Black);
                panel->getRenderer()->setOpacity(0.6f);
                panel->getRenderer()->setTextColor(tgui::Color::White);
                panel->getRenderer()->setSelectedTextColor(tgui::Color::Black);
                panel->getRenderer()->setSelectedTextBackgroundColor(tgui::Color::White);
                panel->getRenderer()->setScrollbarWidth(15.0f);

                auto input = tgui::EditBox::create();
                input->setPosition({"0", "92%"});
                input->setSize({"100%", "8%"});
                input->getRenderer()->setBackgroundColor(tgui::Color::Black);
                input->getRenderer()->setOpacity(0.6f);
                input->getRenderer()->setTextColor(tgui::Color::White);
                input->getRenderer()->setCaretColor(tgui::Color::White);
                input->getRenderer()->setSelectedTextColor(tgui::Color::Black);
                input->getRenderer()->setSelectedTextBackgroundColor(tgui::Color::White);
                input->getRenderer()->setBackgroundColorHover(tgui::Color(20, 20, 20));

                m_ConsoleGui->add(panel, "cmd_buffer");
                m_ConsoleGui->add(input, "cmd_input");

                this->m_ConsoleGui->setVisible(false);
                this->m_TargetGui->gui().add(this->m_ConsoleGui, "devconsole");            
                this->m_CmdLineBuffer.push_front("Welcome in the console. You can try the 'help' command to see all available commands.\n----------------------------------------\n");
                this->m_Working = true;
                this->rewrite();

                this->addCmd("help", &internal_cmds::cmd_help, 0u, "Display all available commands.", "If an existing command name is passed as an argument it displays detailed description about that command.");
                this->addCmd("clear", &internal_cmds::cmd_clear, 0u, "Clear the console.", "This command simply clears the console.");

                return true;
            }
            return false;
        }

        void DevConsole::deinit() {
            this->m_Working = false;
            this->m_TargetGui = nullptr;
        }

        void DevConsole::enableConsole(bool enable, bool save) {
            this->m_Enabled = enable;
            if (save) {
                easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_CONSOLE_ENABLED, enable);
            }
        }

        void DevConsole::toggleConsole() {
            if (this->m_Enabled) {
                if (!this->m_ConsoleGui->isAnimationPlaying()) {
                    if (!this->m_Visible) {
                        this->m_ConsoleGui->moveToFront();
                        this->m_ConsoleGui->showWithEffect(tgui::ShowEffectType::SlideFromTop, CMD_TOGGLE_DELAY);
                        this->m_ConsoleGui->get("cmd_input")->cast<tgui::EditBox>()->setReadOnly(false);
                        this->m_ConsoleGui->get("cmd_input")->cast<tgui::EditBox>()->setFocused(true);
                        this->m_Visible = true;
                    }
                    else {
                        this->m_ConsoleGui->get("cmd_input")->cast<tgui::EditBox>()->setFocused(false);
                        this->m_ConsoleGui->get("cmd_input")->cast<tgui::EditBox>()->setReadOnly(true);
                        this->m_ConsoleGui->hideWithEffect(tgui::ShowEffectType::SlideToTop, CMD_TOGGLE_DELAY);
                        this->m_Visible = false;
                    }
                }
            }
        }

        void DevConsole::rewrite() {
            auto text_area = this->m_ConsoleGui->get("cmd_buffer")->cast<tgui::TextArea>();
            text_area->setText("");
            for (auto &line : this->m_CmdLineBuffer) {
                text_area->addText(line);
            }
        }

        void DevConsole::toBuffer(const std::string &line) {
            if (this->m_Working) {
                if (this->m_CmdLineBuffer.size() + 1 > CMDLINE_BUFFER_SIZE) {
                    auto text_area = this->m_ConsoleGui->get("cmd_buffer")->cast<tgui::TextArea>();
                    auto console_text = text_area->getText();
                    console_text.erase(0ull, this->m_CmdLineBuffer.front().length());
                    text_area->setText(console_text);
                    this->m_CmdLineBuffer.pop_front();
                }
                this->m_CmdLineBuffer.push_back(line);
                this->m_ConsoleGui->get("cmd_buffer")->cast<tgui::TextArea>()->addText(std::forward<const std::string &>(line));
            }
            else {
                if (this->m_CmdLineBuffer.size() + 1 > CMDLINE_BUFFER_SIZE) {
                    this->m_CmdLineBuffer.pop_front();
                }
                this->m_CmdLineBuffer.push_back(std::forward<const std::string &>(line));
            }
        }

        void DevConsole::toHistory(const std::string &line) {
            if (this->m_CmdLineHistory.size() + 1 > CMDLINE_HISTORY_SIZE) {
                this->m_CmdLineHistory.pop_front();
            }
            this->m_CmdLineHistory.push_back(std::forward<const std::string &>(line));
        }

        void DevConsole::loadHistory(bool next) {
            auto input_box = this->m_ConsoleGui->get("cmd_input")->cast<tgui::EditBox>();
            if (next) {
                this->m_CurrHistoryPos -= 1ll;
                if (this->m_CurrHistoryPos < 0ll) {
                    input_box->setText("");
                    this->m_CurrHistoryPos = -1ll;
                }
                else {
                    input_box->setText(std::forward<const std::string &>(this->fromHistory(static_cast<unsigned long long>(this->m_CurrHistoryPos))));
                }
            } else {
                this->m_CurrHistoryPos += 1ll;
                long long last = static_cast<long long>(this->m_CmdLineHistory.size() - 1ull);
                if (this->m_CurrHistoryPos >= last) {
                    this->m_CurrHistoryPos = last;
                }
                input_box->setText(std::forward<const std::string &>(this->fromHistory(static_cast<unsigned long long>(this->m_CurrHistoryPos))));
            }
        }

        void DevConsole::parseLine() {
            std::string cmd_line = this->m_ConsoleGui->get("cmd_input")->cast<tgui::EditBox>()->getText().toStdString();
            this->m_ConsoleGui->get("cmd_input")->cast<tgui::EditBox>()->setText("");
            if (!cmd_line.empty()) {
                this->toHistory(cmd_line);
                this->toBuffer(cmd_line + "\n----------------------------------------\n");

                this->m_CurrHistoryPos = this->m_CmdLineHistory.size();

                EC_Result result = this->parse(cmd_line);
                switch (result) {
                    case EC_Result::UnknownCmd: {
                        this->toBuffer("Unrecognized command: " + this->m_CmdLineHistory.back() + "\n");
                        break;
                    }
                    case EC_Result::NotEnoughArgs: {
                        this->toBuffer("Insufficient number of arguments for command: " + this->m_CmdLineHistory.back() + "\n");
                        break;
                    }
                    case EC_Result::BadArgs: {
                        this->toBuffer("Arguments specified does not match the command: " + this->m_CmdLineHistory.back() + "\n");
                        break;
                    }
                    case EC_Result::Success: {
                        this->toBuffer("\n");
                        break;
                    }
                }
            }
        }

        const std::string & DevConsole::fromHistory(unsigned long long index) const {
            if (index > this->m_CmdLineHistory.size() - 1) {
                index = this->m_CmdLineHistory.size() - 1;
            }
            return this->m_CmdLineHistory.at(index);
        }

        const DevConsole & DevConsole::operator<<(const std::string &line) {
            this->toBuffer(line);
            return *this;
        }

        void DevConsole::p_CmdHelp(const std::string& cmd) {
            if (cmd.empty()) {
                for (auto &cmd : this->m_Commands) {
                    if (!cmd.second.is_hidden) {
                        this->toBuffer(cmd.first + std::string("\t\t\t") + cmd.second.description + std::string("\n"));
                    }
                }
            }
            else if (this->m_Commands.find(cmd) != this->m_Commands.end()) {
                this->toBuffer(cmd + std::string("\t\t\t") + this->m_Commands.at(cmd).description + std::string("\n\t\t\t") + this->m_Commands[cmd].details + std::string("\n"));
            }
            else {
                this->toBuffer(std::string("This command does not exist: ") + cmd + std::string("\n"));
            }
        }

        void DevConsole::p_CmdClear() {
            this->m_CmdLineBuffer.clear();
            this->m_ConsoleGui->get("cmd_buffer")->cast<tgui::TextArea>()->setText("");
        }
    }
}