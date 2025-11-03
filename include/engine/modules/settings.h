#pragma once

#include "input.h"

#include <string>
#include <unordered_map>
#include <utility>

namespace easygine {
    namespace utils {
        class SettingsManager {
        public:
            void initSettingFile(const std::string &filename);
            void prepOtherFile(const std::string &filename, const std::string &entry);

            void setSetting(const std::string &name, bool value, const std::string &filename = "none");
            bool getBoolSetting(const std::string &name, bool def_value, bool generate, const std::string &filename = "none");

            void setSetting(const std::string &name, unsigned int value, const std::string &filename = "none");
            unsigned int getUintSetting(const std::string &name, unsigned int def_value, bool generate, const std::string &filename = "none");

            void setSetting(const std::string &name, double value, const std::string &filename = "none");
            double getDoubleSetting(const std::string &name, double def_value, bool generate, const std::string &filename = "none");

            void setSetting(const std::string &name, const std::string &value, const std::string &filename = "none");
            std::string getStringSetting(const std::string &name, const std::string &def_value, bool generate, const std::string &filename = "none");

            void setActionSetting(const std::string &name, const input::S_ActionData_Event &def_action, const std::string &filename = "none");
            input::S_ActionData_Event getActionSetting(const std::string &name, const input::S_ActionData_Event &def_action, bool generate, const std::string &filename = "none");

            void setActionSetting(const std::string &name, const input::S_ActionData_KeyboardKey &def_action, const std::string &filename = "none");
            input::S_ActionData_KeyboardKey getActionSetting(const std::string &name, const input::S_ActionData_KeyboardKey &def_action, bool generate, const std::string &filename = "none");

            void setActionSetting(const std::string &name, const input::S_ActionData_MouseButton &def_action, const std::string &filename = "none");
            input::S_ActionData_MouseButton getActionSetting(const std::string &name, const input::S_ActionData_MouseButton &def_action, bool generate, const std::string &filename = "none");

            void setActionSetting(const std::string &name, const input::S_ActionData_JoystickAxis &def_action, const std::string &filename = "none");
            input::S_ActionData_JoystickAxis getActionSetting(const std::string &name, const input::S_ActionData_JoystickAxis &def_action, bool generate, const std::string &filename = "none");

            void setActionSetting(const std::string &name, const input::S_ActionData_JoystickButton &def_action, const std::string &filename = "none");
            input::S_ActionData_JoystickButton getActionSetting(const std::string &name, const input::S_ActionData_JoystickButton &def_action, bool generate, const std::string &filename = "none");

            // void setActionSetting(const std::string &name, const std::string &action_1, const std::string &action_2, bool need_both, const std::string &filename = "none");
            // thor::Action getActionSetting(const std::string &name, const std::string &action_1, const std::string &action_2, bool need_both, bool generate, const std::string &filename = "none");

        public:
            SettingsManager()           = default;
            virtual ~SettingsManager()  = default;

        private:
            std::string m_SettingFile;
        };
    }
}