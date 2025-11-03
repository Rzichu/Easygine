#pragma once

#include <SFML/Window.hpp>
#include <Thor/Input.hpp>

#include <memory>
#include <utility>
#include <string>
#include <functional>
#include <unordered_map>

namespace easygine {
    class CORE;
    
    namespace input {
        enum class ActionDataType {
            Event
            , KeyboardKey
            , MouseButton
            , JoystickAxis
            , JoystickButton
        };

        struct S_ActionData_Base {
            virtual thor::Action toAction() = 0;

        protected:
            S_ActionData_Base() = default;
        };

        struct S_ActionData_Event : public S_ActionData_Base {
            inline thor::Action toAction() override {
                return thor::Action(this->eventType);
            }

            S_ActionData_Event(sf::Event::EventType event_type)
            : eventType{event_type}
            {}

            sf::Event::EventType eventType;
        };

        struct S_ActionData_KeyboardKey : public S_ActionData_Base {
            inline thor::Action toAction() override {
                return thor::Action(this->keyboardKey, this->actionType);
            }

            S_ActionData_KeyboardKey(sf::Keyboard::Key keyboard_key, thor::Action::ActionType action_type)
            : keyboardKey{keyboard_key}
            , actionType{action_type}
            {}

            sf::Keyboard::Key keyboardKey;
            thor::Action::ActionType actionType;
        };

        struct S_ActionData_MouseButton : public S_ActionData_Base {
            inline thor::Action toAction() override {
                return thor::Action(this->mouseButton, this->actionType);
            }

            S_ActionData_MouseButton(sf::Mouse::Button mouse_button, thor::Action::ActionType action_type)
            : mouseButton{mouse_button}
            , actionType{action_type}
            {}

            sf::Mouse::Button mouseButton;
            thor::Action::ActionType actionType;
        };

        struct S_ActionData_JoystickAxis : public S_ActionData_Base {
            inline thor::Action toAction() override {
                return thor::Action(this->joystickAxis);
            }

            S_ActionData_JoystickAxis(thor::JoystickAxis joystick_axis)
            : joystickAxis{joystick_axis}
            {}

            thor::JoystickAxis joystickAxis;
        };

        struct S_ActionData_JoystickButton : public S_ActionData_Base {
            inline thor::Action toAction() override {
                return thor::Action(this->joystickButton, this->actionType);
            }

            S_ActionData_JoystickButton(thor::JoystickButton joystick_button, thor::Action::ActionType action_type)
                : joystickButton{joystick_button}
                , actionType{action_type}
                {}

            thor::JoystickButton joystickButton;
            thor::Action::ActionType actionType;
        };

        // struct S_ActionData_Complex : public S_ActionData_Base {
        //     thor::Action toAction() override;
        // };

        class InputManager {
            friend class easygine::CORE;
        public:
            bool keyDown(sf::Keyboard::Key key) const;

            bool keyUp(sf::Keyboard::Key key) const;

            bool mouseBtnDown(sf::Mouse::Button btn) const;

            bool mouseBtnUp(sf::Mouse::Button btn) const;

            inline sf::Vector2f mousePos() const {
                return this->m_MousePosView;
            }

            inline bool checkAction(const std::string &action_name) {
                return this->m_ActionMap.isActive(std::forward<const std::string &>(action_name));
            }

            void addAction(const std::string &action_name, sf::Event::EventType event, bool save = false);

            void addAction(const std::string &action_name, sf::Keyboard::Key key, thor::Action::ActionType action_type, bool save = false);

            void addAction(const std::string &action_name, sf::Mouse::Button button, thor::Action::ActionType action_type, bool save = false);

            void addAction(const std::string &action_name, thor::JoystickAxis joystick_axis,  bool save = false);

            void addAction(const std::string &action_name, thor::JoystickButton joystick_button, thor::Action::ActionType action_type, bool save = false);

            // void addAction(const std::string &action_name, const std::string &action_1, const std::string &action_2, bool need_both, bool save = false);

            void removeAction(const std::string &action_name);

            template<typename SIGNATURE>
            inline void connectCallback(const std::string &action_name, const std::function<SIGNATURE> &callable) {
                this->m_Callbacks.connect(action_name, callable);
            }

            inline void disconnectCallback(const std::string &action_name) {
                this->m_Callbacks.clearConnections(action_name);
            }

            inline void disconnectAllCallbacks() {
                this->m_Callbacks.clearAllConnections();
            }

            inline auto & getActionMap() {
                return this->m_ActionMap;
            }

            inline const auto & getActionMap() const {
                return this->m_ActionMap;
            }

            inline auto & getCallbacks() {
                return this->m_Callbacks;
            }

            inline const auto & getCallbacks() const {
                return this->m_Callbacks;
            }
            
        public:
            InputManager()  = default;
            ~InputManager() = default;

        private:
            bool init();

            void deinit();
        
        private:
            thor::ActionMap<std::string> m_ActionMap;
            thor::ActionMap<std::string>::CallbackSystem m_Callbacks;

            sf::Vector2i m_MousePosWin {0, 0};
            sf::Vector2f m_MousePosView {0.0f, 0.0f};
        };
    }
}