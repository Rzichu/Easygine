#include "input.h"

#include "dev_console.h"
#include "../engine.h"
#include "../../misc/LogSys/log_sys.h"

#include <memory>
#include <utility>

#ifndef _RELEASE
namespace easygine {
    extern aether::lgs::Timer EngineClock;
    extern aether::lgs::Logger EngineLogger;
}
#endif

namespace easygine {
    namespace input {
        bool InputManager::init() {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Input initialization started.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);



            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Input initialization successful.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

            return true;
        }

        void InputManager::deinit() {
            
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Input deinitialized.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }

        bool InputManager::keyDown(sf::Keyboard::Key key) const {
            if (internal_handle_core.gameWindow()->focused()) {
                return sf::Keyboard::isKeyPressed(key);
            }
            return false;
        }

        bool InputManager::keyUp(sf::Keyboard::Key key) const {
            if (internal_handle_core.gameWindow()->focused()) {
                return !sf::Keyboard::isKeyPressed(key);
            }
            return false;
        }

        bool InputManager::mouseBtnDown(sf::Mouse::Button btn) const {
            if (internal_handle_core.gameWindow()->focused()) {
                return sf::Mouse::isButtonPressed(btn);
            }
            return false;
        }

        bool InputManager::mouseBtnUp(sf::Mouse::Button btn) const {
            if (internal_handle_core.gameWindow()->focused()) {
                return !sf::Mouse::isButtonPressed(btn);
            }
            return false;
        }

        void InputManager::addAction(const std::string &action_name, sf::Event::EventType event, bool save) {
            this->m_ActionMap[action_name] = easygine::CORE::core().gameSettings()->getActionSetting(action_name, S_ActionData_Event(event), save).toAction();

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Added action \'")lgs_MSG(action_name)lgs_MSG("\'.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }

        void InputManager::addAction(const std::string &action_name, sf::Keyboard::Key key, thor::Action::ActionType action_type, bool save) {
            this->m_ActionMap[action_name] = easygine::CORE::core().gameSettings()->getActionSetting(action_name, S_ActionData_KeyboardKey(key, action_type), save).toAction();

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Added action \'")lgs_MSG(action_name)lgs_MSG("\'.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }

        void InputManager::addAction(const std::string &action_name, sf::Mouse::Button button, thor::Action::ActionType action_type, bool save) {
            this->m_ActionMap[action_name] = easygine::CORE::core().gameSettings()->getActionSetting(action_name, S_ActionData_MouseButton(button, action_type), save).toAction();

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Added action \'")lgs_MSG(action_name)lgs_MSG("\'.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }

        void InputManager::addAction(const std::string &action_name, thor::JoystickAxis joystick_axis, bool save) {
            this->m_ActionMap[action_name] = easygine::CORE::core().gameSettings()->getActionSetting(action_name, S_ActionData_JoystickAxis(joystick_axis), save).toAction();

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Added action \'")lgs_MSG(action_name)lgs_MSG("\'.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }

        void InputManager::addAction(const std::string &action_name, thor::JoystickButton joystick_button, thor::Action::ActionType action_type, bool save) {
            this->m_ActionMap[action_name] = easygine::CORE::core().gameSettings()->getActionSetting(action_name, S_ActionData_JoystickButton(joystick_button, action_type), save).toAction();

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Added action \'")lgs_MSG(action_name)lgs_MSG("\'.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }

        // void InputManager::addAction(const std::string &action_name, const std::string &action_1, const std::string &action_2, bool need_both, bool save = true) {
        //     if (need_both) {
        //         this->m_ActionMap[action_name] = this->m_ActionMap[action_1] && this->m_ActionMap[action_2];
        //     }
        //     else {
        //         this->m_ActionMap[action_name] = this->m_ActionMap[action_1] || this->m_ActionMap[action_2];
        //     }

        //     lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Added action \'")lgs_MSG(action_name)lgs_MSG("\'.");
        //     CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
        //     lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        // }
        
        void InputManager::removeAction(const std::string &action_name) {
            this->m_ActionMap.removeAction(std::forward<const std::string &>(action_name));

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Removed action \'")lgs_MSG(action_name)lgs_MSG("\'.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }
    }
}