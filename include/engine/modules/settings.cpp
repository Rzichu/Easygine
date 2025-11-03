#include "settings.h"

#include "../defines.h"
#include "dev_console.h"
#include "../engine.h"
#include "../../misc/LogSys/log_sys.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

#ifndef _RELEASE
namespace easygine {
    extern aether::lgs::Timer EngineClock;
    extern aether::lgs::Logger EngineLogger;
}
#endif

namespace easygine {
    namespace utils {
        void SettingsManager::initSettingFile(const std::string &filename) {
            this->m_SettingFile = filename;

            nlohmann::json sett_data;
            nlohmann::json patch;
            {
                std::ifstream r_sett_file;
                r_sett_file.open(filename);
                if (r_sett_file.is_open()) {
                    try {
                        sett_data = nlohmann::json::parse(r_sett_file);
                    }
                    catch (...) {
                    }
                    r_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Settings file missing. Rewriting...");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }

                patch["AA_PROJ_INDICATOR"] = GAME_TITLE + std::string(GAME_VERSION);
                sett_data.merge_patch(patch);
                
                std::ofstream w_sett_file;
                w_sett_file.open(filename);
                if (w_sett_file.is_open()) {
                    w_sett_file << std::setw(4) << sett_data;
                    w_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to init settings file.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }
            }

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Main settings file prepared: ")lgs_MSG(filename)lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
        }

        void SettingsManager::prepOtherFile(const std::string &filename, const std::string &entry) {
            nlohmann::json other_file_data;
            nlohmann::json patch;
            {
                std::ifstream r_sett_file;
                r_sett_file.open(filename);
                if (r_sett_file.is_open()) {
                    try {
                        other_file_data = nlohmann::json::parse(r_sett_file);
                    }
                    catch (...) {
                    }
                    r_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("File ")lgs_MSG(filename)lgs_MSG(" missing. Rewriting...");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }

                patch["AA_FILE_ENTRY"] = entry;
                other_file_data.merge_patch(patch);

                std::ofstream w_sett_file;
                w_sett_file.open(filename);
                if (w_sett_file.is_open()) {
                    w_sett_file << std::setw(4) << other_file_data;
                    w_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to prepare ")lgs_MSG(filename)lgs_MSG(" file.");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }
            }

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Settings file prepared: ")lgs_MSG(filename)lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
        }

        void SettingsManager::setSetting(const std::string &name, bool value, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            nlohmann::json sett_data;
            nlohmann::json patch;
            {
                std::ifstream r_sett_file;
                r_sett_file.open(use_file);
                if (r_sett_file.is_open()) {
                    sett_data = nlohmann::json::parse(r_sett_file);
                    r_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (read).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }

                patch[name] = value;
                sett_data.merge_patch(patch);

                std::ofstream w_sett_file;
                w_sett_file.open(use_file);
                if (w_sett_file.is_open()) {
                    w_sett_file << std::setw(4) << sett_data;
                    w_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (write).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }
            }

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Bool setting saved as \'")lgs_MSG(name)lgs_MSG("\' in file ")lgs_MSG(use_file)lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
        }

        bool SettingsManager::getBoolSetting(const std::string &name, bool def_value, bool generate, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            std::ifstream sett_file;
            sett_file.open(use_file);
            if (sett_file.is_open()) {
                try {
                    nlohmann::json sett_data = nlohmann::json::parse(sett_file);
                    bool value = sett_data.at(name).get<bool>();
                    sett_file.close();
                    return value;
                }
                catch (...) {
                    sett_file.close();
                    if (generate) {
                        this->setSetting(name, def_value, use_file);
                    }
                }
            }
            else {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
            }
            return def_value;
        }

        void SettingsManager::setSetting(const std::string &name, unsigned int value, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            nlohmann::json sett_data;
            nlohmann::json patch;
            {
                std::ifstream r_sett_file;
                r_sett_file.open(use_file);
                if (r_sett_file.is_open()) {
                    sett_data = nlohmann::json::parse(r_sett_file);
                    r_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (read).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }

                patch[name] = value;
                sett_data.merge_patch(patch);

                std::ofstream w_sett_file;
                w_sett_file.open(use_file);
                if (w_sett_file.is_open()) {
                    w_sett_file << std::setw(4) << sett_data;
                    w_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (write).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }
            }

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Uint setting saved as \'")lgs_MSG(name)lgs_MSG("\' in file ")lgs_MSG(use_file)lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
        }

        unsigned int SettingsManager::getUintSetting(const std::string &name, unsigned int def_value, bool generate, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            std::ifstream sett_file;
            sett_file.open(use_file);
            if (sett_file.is_open()) {
                try {
                    nlohmann::json sett_data = nlohmann::json::parse(sett_file);
                    unsigned int value = sett_data.at(name).get<unsigned int>();
                    sett_file.close();
                    return value;
                }
                catch (...) {
                    sett_file.close();
                    if (generate) {
                        this->setSetting(name, def_value, use_file);
                    }
                }
            }
            else {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
            }
            return def_value;
        }

        void SettingsManager::setSetting(const std::string &name, double value, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            nlohmann::json sett_data;
            nlohmann::json patch;
            {
                std::ifstream r_sett_file;
                r_sett_file.open(use_file);
                if (r_sett_file.is_open()) {
                    sett_data = nlohmann::json::parse(r_sett_file);
                    r_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (read).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }

                patch[name] = value;
                sett_data.merge_patch(patch);

                std::ofstream w_sett_file;
                w_sett_file.open(use_file);
                if (w_sett_file.is_open()) {
                    w_sett_file << std::setw(4) << sett_data;
                    w_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (write).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }
            }

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Double setting saved as \'")lgs_MSG(name)lgs_MSG("\' in file ")lgs_MSG(use_file)lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
        }

        double SettingsManager::getDoubleSetting(const std::string &name, double def_value, bool generate, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            std::ifstream sett_file;
            sett_file.open(use_file);
            if (sett_file.is_open()) {
                try {
                    nlohmann::json sett_data = nlohmann::json::parse(sett_file);
                    double value = sett_data.at(name).get<double>();
                    sett_file.close();
                    return value;
                }
                catch (...) {
                    sett_file.close();
                    if (generate) {
                        this->setSetting(name, def_value, use_file);
                    }
                }
            }
            else {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
            }
            return def_value;
        }

        void SettingsManager::setSetting(const std::string &name, const std::string &value, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            nlohmann::json sett_data;
            nlohmann::json patch;
            {
                std::ifstream r_sett_file;
                r_sett_file.open(use_file);
                if (r_sett_file.is_open()) {
                    sett_data = nlohmann::json::parse(r_sett_file);
                    r_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (read).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }

                patch[name] = value;
                sett_data.merge_patch(patch);

                std::ofstream w_sett_file;
                w_sett_file.open(use_file);
                if (w_sett_file.is_open()) {
                    w_sett_file << std::setw(4) << sett_data;
                    w_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (write).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }
            }

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("String setting saved as \'")lgs_MSG(name)lgs_MSG("\' in file ")lgs_MSG(use_file)lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
        }

        std::string SettingsManager::getStringSetting(const std::string &name, const std::string &def_value, bool generate, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            std::ifstream sett_file;
            sett_file.open(use_file);
            if (sett_file.is_open()) {
                try {
                    nlohmann::json sett_data = nlohmann::json::parse(sett_file);
                    std::string value = sett_data.at(name).get<std::string>();
                    sett_file.close();
                    return value;
                }
                catch (...) {
                    sett_file.close();
                    if (generate) {
                        this->setSetting(name, def_value, use_file);
                    }
                }
            }
            else {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
            }
            return def_value;
        }

        void SettingsManager::setActionSetting(const std::string &name, const input::S_ActionData_Event &def_action, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            nlohmann::json sett_data;
            nlohmann::json patch;
            {
                std::ifstream r_sett_file;
                r_sett_file.open(use_file);
                if (r_sett_file.is_open()) {
                    sett_data = nlohmann::json::parse(r_sett_file);
                    r_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (read).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }

                patch["actionbinds"]["events"][name] = { {"event", def_action.eventType} };
                sett_data.merge_patch(patch);

                std::ofstream w_sett_file;
                w_sett_file.open(use_file);
                if (w_sett_file.is_open()) {
                    w_sett_file << std::setw(4) << sett_data;
                    w_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (write).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }
            }

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Action setting saved as \'")lgs_MSG(name)lgs_MSG("\' in file ")lgs_MSG(use_file)lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
        }

        input::S_ActionData_Event SettingsManager::getActionSetting(const std::string &name, const input::S_ActionData_Event &def_action, bool generate, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            input::S_ActionData_Event bindings(def_action);
            std::ifstream sett_file;
            sett_file.open(use_file);
            if (sett_file.is_open()) {
                try {
                    nlohmann::json sett_data = nlohmann::json::parse(sett_file);
                    bindings.eventType = static_cast<sf::Event::EventType>(sett_data.at("actionbinds").at("events").at(name).at("event").get<int>());
                    sett_file.close();
                    return bindings;
                }
                catch (...) {
                    sett_file.close();
                    if (generate) {
                        this->setActionSetting(name, def_action, use_file);
                    }
                }
            }
            else {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
            }
            return bindings;
        }

        void SettingsManager::setActionSetting(const std::string &name, const input::S_ActionData_KeyboardKey &def_action, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            nlohmann::json sett_data;
            nlohmann::json patch;
            {
                std::ifstream r_sett_file;
                r_sett_file.open(use_file);
                if (r_sett_file.is_open()) {
                    sett_data = nlohmann::json::parse(r_sett_file);
                    r_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (read).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }

                patch["actionbinds"]["keyboard"][name] = { {"key", def_action.keyboardKey}, {"action_type", def_action.actionType} };
                sett_data.merge_patch(patch);

                std::ofstream w_sett_file;
                w_sett_file.open(use_file);
                if (w_sett_file.is_open()) {
                    w_sett_file << std::setw(4) << sett_data;
                    w_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (write).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }
            }

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Action setting saved as \'")lgs_MSG(name)lgs_MSG("\' in file ")lgs_MSG(use_file)lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
        }

        input::S_ActionData_KeyboardKey SettingsManager::getActionSetting(const std::string &name, const input::S_ActionData_KeyboardKey &def_action, bool generate, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            input::S_ActionData_KeyboardKey bindings(def_action);
            std::ifstream sett_file;
            sett_file.open(use_file);
            if (sett_file.is_open()) {
                try {
                    nlohmann::json sett_data = nlohmann::json::parse(sett_file);
                    bindings.keyboardKey = static_cast<sf::Keyboard::Key>(sett_data.at("actionbinds").at("keyboard").at(name).at("key").get<int>());
                    bindings.actionType = static_cast<thor::Action::ActionType>(sett_data.at("actionbinds").at("keyboard").at(name).at("action_type").get<unsigned int>());
                    sett_file.close();
                    return bindings;
                }
                catch (...) {
                    sett_file.close();
                    if (generate) {
                        this->setActionSetting(name, def_action, use_file);
                    }
                }
            }
            else {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
            }
            return bindings;
        }

        void SettingsManager::setActionSetting(const std::string &name, const input::S_ActionData_MouseButton &def_action, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            nlohmann::json sett_data;
            nlohmann::json patch;
            {
                std::ifstream r_sett_file;
                r_sett_file.open(use_file);
                if (r_sett_file.is_open()) {
                    sett_data = nlohmann::json::parse(r_sett_file);
                    r_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (read).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }

                patch["actionbinds"]["mouse"][name] = { {"button", def_action.mouseButton}, {"action_type", def_action.actionType} };
                sett_data.merge_patch(patch);

                std::ofstream w_sett_file;
                w_sett_file.open(use_file);
                if (w_sett_file.is_open()) {
                    w_sett_file << std::setw(4) << sett_data;
                    w_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (write).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }
            }

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Action setting saved as \'")lgs_MSG(name)lgs_MSG("\' in file ")lgs_MSG(use_file)lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
        }

        input::S_ActionData_MouseButton SettingsManager::getActionSetting(const std::string &name, const input::S_ActionData_MouseButton &def_action, bool generate, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            input::S_ActionData_MouseButton bindings(def_action);
            std::ifstream sett_file;
            sett_file.open(use_file);
            if (sett_file.is_open()) {
                try {
                    nlohmann::json sett_data = nlohmann::json::parse(sett_file);
                    bindings.mouseButton = static_cast<sf::Mouse::Button>(sett_data.at("actionbinds").at("mouse").at(name).at("button").get<int>());
                    bindings.actionType = static_cast<thor::Action::ActionType>(sett_data.at("actionbinds").at("mouse").at(name).at("action_type").get<unsigned int>());
                    sett_file.close();
                    return bindings;
                }
                catch (...) {
                    sett_file.close();
                    if (generate) {
                        this->setActionSetting(name, def_action, use_file);
                    }
                }
            }
            else {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
            }
            return bindings;
        }

        void SettingsManager::setActionSetting(const std::string &name, const input::S_ActionData_JoystickAxis &def_action, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            nlohmann::json sett_data;
            nlohmann::json patch;
            {
                std::ifstream r_sett_file;
                r_sett_file.open(use_file);
                if (r_sett_file.is_open()) {
                    sett_data = nlohmann::json::parse(r_sett_file);
                    r_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (read).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }

                patch["actionbinds"]["joystick_axes"][name] = { {"joystick_id", def_action.joystickAxis.joystickId}
                        , {"joystick_axis", def_action.joystickAxis.axis}
                        , {"joystick_threshold", def_action.joystickAxis.threshold}
                        , {"joystick_above_threshold", def_action.joystickAxis.above} };
                sett_data.merge_patch(patch);

                std::ofstream w_sett_file;
                w_sett_file.open(use_file);
                if (w_sett_file.is_open()) {
                    w_sett_file << std::setw(4) << sett_data;
                    w_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (write).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }
            }

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Action setting saved as \'")lgs_MSG(name)lgs_MSG("\' in file ")lgs_MSG(use_file)lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
        }

        input::S_ActionData_JoystickAxis SettingsManager::getActionSetting(const std::string &name, const input::S_ActionData_JoystickAxis &def_action, bool generate, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            input::S_ActionData_JoystickAxis bindings(def_action);
            std::ifstream sett_file;
            sett_file.open(use_file);
            if (sett_file.is_open()) {
                try {
                    nlohmann::json sett_data = nlohmann::json::parse(sett_file);
                    bindings.joystickAxis = thor::JoystickAxis(sett_data.at("actionbinds").at("joystick_axes").at(name).at("joystick_id").get<int>()
                            , static_cast<sf::Joystick::Axis>(sett_data.at("actionbinds").at("joystick_axes").at(name).at("joystick_axis").get<int>())
                            , sett_data.at("actionbinds").at("joystick_axes").at(name).at("joystick_threshold").get<float>()
                            , sett_data.at("actionbinds").at("joystick_axes").at(name).at("joystick_above_threshold").get<bool>());
                    sett_file.close();
                    return bindings;
                }
                catch (...) {
                    sett_file.close();
                    if (generate) {
                        this->setActionSetting(name, def_action, use_file);
                    }
                }
            }
            else {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
            }
            return bindings;
        }

        void SettingsManager::setActionSetting(const std::string &name, const input::S_ActionData_JoystickButton &def_action, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            nlohmann::json sett_data;
            nlohmann::json patch;
            {
                std::ifstream r_sett_file;
                r_sett_file.open(use_file);
                if (r_sett_file.is_open()) {
                    sett_data = nlohmann::json::parse(r_sett_file);
                    r_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (read).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }

                patch["actionbinds"]["joystick_buttons"][name] = { {"joystick_id", def_action.joystickButton.joystickId}, {"joystick_button", def_action.joystickButton.button}, {"action_type", def_action.actionType} };
                sett_data.merge_patch(patch);

                std::ofstream w_sett_file;
                w_sett_file.open(use_file);
                if (w_sett_file.is_open()) {
                    w_sett_file << std::setw(4) << sett_data;
                    w_sett_file.close();
                }
                else {
                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (write).");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
                }
            }

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Action setting saved as \'")lgs_MSG(name)lgs_MSG("\' in file ")lgs_MSG(use_file)lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
        }

        input::S_ActionData_JoystickButton SettingsManager::getActionSetting(const std::string &name, const input::S_ActionData_JoystickButton &def_action, bool generate, const std::string &filename) {
            const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

            input::S_ActionData_JoystickButton bindings(def_action);
            std::ifstream sett_file;
            sett_file.open(use_file);
            if (sett_file.is_open()) {
                try {
                    nlohmann::json sett_data = nlohmann::json::parse(sett_file);
                    bindings.joystickButton = thor::JoystickButton(sett_data.at("actionbinds").at("joystick_buttons").at(name).at("joystick_id").get<int>()
                                , sett_data.at("actionbinds").at("joystick_buttons").at(name).at("joystick_button").get<int>());
                    bindings.actionType = static_cast<thor::Action::ActionType>(sett_data.at("actionbinds").at("joystick_buttons").at(name).at("action_type").get<unsigned int>());
                    sett_file.close();
                    return bindings;
                }
                catch (...) {
                    sett_file.close();
                    if (generate) {
                        this->setActionSetting(name, def_action, use_file);
                    }
                }
            }
            else {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
            }
            return bindings;
        }

        // void SettingsManager::setActionSetting(const std::string &name, const std::string &action_1, const std::string &action_2, bool need_both, const std::string &filename) {
        //     const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

        //     nlohmann::json sett_data;
        //     nlohmann::json patch;
        //     {
        //         std::ifstream r_sett_file;
        //         r_sett_file.open(use_file);
        //         if (r_sett_file.is_open()) {
        //             sett_data = nlohmann::json::parse(r_sett_file);
        //             r_sett_file.close();
        //         }
        //         else {
        //             lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (read).");
        //             CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
        //             lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);                
        //         }

        //         patch["actionbinds"]["complex"][name] = { {"action_1", action_1}, {"action_2", action_2}, {"need_both", need_both} };
        //         sett_data.merge_patch(patch);

        //         std::ofstream w_sett_file;
        //         w_sett_file.open(use_file);
        //         if (w_sett_file.is_open()) {
        //             w_sett_file << std::setw(4) << sett_data;
        //             w_sett_file.close();
        //         }
        //         else {
        //             lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file (write).");
        //             CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
        //             lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);  
        //         }
        //     }
        // }

        // thor::Action SettingsManager::getActionSetting(const std::string &name, const std::string &action_1, const std::string &action_2, bool need_both, bool generate, const std::string &filename) {
        //     const std::string &use_file = (filename == "none") ? this->m_SettingFile : filename;

        //     thor::Action bindings;
        //     if (need_both) {
        //         bindings = this->loadActionElement(action_1, use_file) && this->loadActionElement(action_2, use_file);
        //     }
        //     else {
        //         bindings = this->loadActionElement(action_1, use_file) || this->loadActionElement(action_2, use_file);
        //     }
        //     std::ifstream sett_file;
        //     sett_file.open(use_file);
        //     if (sett_file.is_open()) {
        //         try {
        //             nlohmann::json sett_data = nlohmann::json::parse(sett_file);
        //             sett_file.close();
        //             bindings;
        //             return bindings;
        //         }
        //         catch (...) {
        //             if (sett_file.is_open()) {
        //                 sett_file.close();
        //             }
        //             if (generate) {
        //                 this->setActionSetting(name, std::forward<const std::string &>(action_1), std::forward<const std::string &>(action_2), need_both, use_file);
        //             }
        //         }
        //     }
        //     else {
        //         lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Failed to open settings file.");
        //         CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
        //         lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
        //     }
        //     return bindings;
        // }
    }
}