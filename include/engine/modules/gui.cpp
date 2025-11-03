#include "gui.h"

#include "dev_console.h"
#include "../engine.h"
#include "../../misc/LogSys/log_sys.h"

#include <TGUI/Loading/ImageLoader.hpp>

#ifndef _RELEASE
namespace easygine {
    extern aether::lgs::Timer EngineClock;
    extern aether::lgs::Logger EngineLogger;
}
#endif

namespace easygine {
    namespace interface {
        bool GuiScreen::init() {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("GUI initialization started.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

            this->m_Gui = std::make_unique<tgui::GuiSFML>();

            if (!this->m_Gui) {
                return false;
            }

            this->setWrittenLang(internal_handle_core.gameSettings()->getStringSetting(GAME_SETTING_LANGUAGE_TEXT, "en_US", false), false);
            this->setSpokenLang(internal_handle_core.gameSettings()->getStringSetting(GAME_SETTING_LANGUAGE_DUBBING, "en_US", false), false);

            bindtextdomain(GAME_TITLE, GAME_LOCALE_DIR);
            textdomain(GAME_TITLE);

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("GUI initialization successful.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

            return true;
        }

        void GuiScreen::deinit() {

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Gui deinitialized.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }
        void GuiScreen::render() {
            this->m_Gui->draw();
        }

        bool GuiScreen::loadCursorStyle(tgui::Cursor::Type type, const tgui::String &filename, tgui::Vector2u hotspot) {
            tgui::Vector2u imagesize;
            std::unique_ptr<std::uint8_t[]> imagepixels = tgui::ImageLoader::loadFromFile(filename, imagesize);
            if (imagepixels != nullptr) {
                tgui::Cursor::setStyle(type, imagepixels.get(), imagesize, hotspot);
                return true;
            }
            return false;
        }
        
        void GuiScreen::addFont(const std::string &font_name, const std::string &filename) {
            this->m_Fonts.emplace_back(std::make_pair(font_name, tgui::Font(filename)));

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("New font \'")lgs_MSG(font_name)lgs_MSG("\' added: ")lgs_MSG(filename)lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }

        void GuiScreen::removeFont(const std::string &font_name) {
            for (unsigned long long i {this->m_Fonts.size()}; i--;) {
                if (this->m_Fonts.at(i).first == font_name) {
                    if (this->m_Gui->getFont() == this->m_Fonts.at(i).second) {
                        this->m_Gui->setFont(tgui::Font::getGlobalFont());
                    }
                    this->m_Fonts.erase(this->m_Fonts.begin() + i);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Font removed: \'")lgs_MSG(font_name)lgs_MSG("\'.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
                }
            }
        }

        void GuiScreen::setMainFont(const std::string &font_name) {
            for (auto &font : this->m_Fonts) {
                if (font.first == font_name) {
                    this->m_Gui->setFont(font.second);

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Main font set: ")lgs_MSG(font_name);
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

                    break;
                }
            }
        }

        const tgui::Font & GuiScreen::GetFont(const std::string &font_name) const {
            for (auto &font : this->m_Fonts) {
                if (font.first == font_name) {
                    return font.second;
                }
            }
            return this->m_Fonts.at(0ull).second;
        }

        void GuiScreen::setWrittenLang(const std::string &locale, bool save) {
            setlocale(LC_MONETARY, locale.c_str());
            setlocale(LC_NUMERIC, locale.c_str());
            setlocale(LC_CTYPE, locale.c_str());
            setlocale(LC_MESSAGES, locale.c_str());
            this->m_CurrentLocale[0ull] = locale;
            if (save) {
                internal_handle_core.gameSettings()->setSetting(GAME_SETTING_LANGUAGE_TEXT, locale);
            }

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Text language set to: ")lgs_MSG(locale);
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }

        void GuiScreen::setSpokenLang(const std::string &locale, bool save) {
            this->m_CurrentLocale[1ull] = locale;
            if (save) {
                internal_handle_core.gameSettings()->setSetting(GAME_SETTING_LANGUAGE_DUBBING, locale);
            }

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Dubbing language set to: ")lgs_MSG(locale);
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }
    }
}