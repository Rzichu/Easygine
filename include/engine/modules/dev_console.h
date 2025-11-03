#pragma once

#include "gui.h"
#include "../defines.h"
#include "../../misc/CmdLine/cmd_line.h"

#include <deque>
#include <memory>

namespace easygine {
    class CORE;

    namespace utils {
        extern sf::Time CMD_TOGGLE_DELAY;

        class DevConsole : virtual public aether::cmdline::ConsoleBase {
            friend class easygine::CORE;
        public:
            void enableConsole(bool enable, bool save = false);

            void toggleConsole();

            void toBuffer(const std::string &line);
            
            void toHistory(const std::string &line);

            void loadHistory(bool next);

            inline bool isVisible() const {
                return this->m_Visible;
            }

        public:
            DevConsole()            = default;
            virtual ~DevConsole()   = default;

        public:
            const DevConsole & operator<<(const std::string &line);

            void p_CmdHelp(const std::string& cmd);

            void p_CmdClear();
        
        private:
            bool init(const std::shared_ptr<interface::GuiScreen> &target);
            
            void deinit();

            void parseLine();

            void rewrite();
            
            const std::string & fromHistory(unsigned long long index) const;

        private:
            bool m_Enabled {false};
            bool m_Working {false};
            bool m_Visible {false};
            std::deque<std::string> m_CmdLineBuffer;
            std::deque<std::string> m_CmdLineHistory;
            std::shared_ptr<interface::GuiScreen> m_TargetGui {nullptr};
            tgui::Group::Ptr m_ConsoleGui;
            long long m_CurrHistoryPos {0};
        };
    }
}

// FOR LOGSYS "INTEGRATION"
#ifdef LOGSYS
#define CMD_LOG(console)    console
#define CMD_MSG(message)    << message
#else
#define CMD_LOG(console)
#define CMD_MSG(message)
#endif