#pragma once

#include "defines.h"
#include "modules/dev_console.h"
#include "modules/resource_manager.h"
#include "modules/settings.h"
#include "modules/window.h"
#include "modules/input.h"
#include "modules/gui.h"
#include "modules/audio.h"
#include "modules/game_object_manager.h"

#include <SFML/System.hpp>

#include <memory>
#include <chrono>
#include <array>

namespace easygine {
    extern CORE internal_handle_core;

    class CORE final {
    public:
        bool init(const sf::String &title);
        
        void deinit();

        void update();

        void render();

        inline sf::Time deltaTime() const {
            return this->m_DeltaTime;
        }

        inline unsigned int getFPS() const {
            return this->m_FPSCount;
        }

        inline bool shadersSupported() const {
            return this->m_ShadersSupport[0ull];
        }

        inline bool geometryShadersSupported() const {
            return this->m_ShadersSupport[1ull];
        }

        static inline CORE & core() {
            return internal_handle_core;
        }

        inline const std::shared_ptr<graphics::Window> & gameWindow() const {
            return this->m_core_GameWindow;
        }
        
        inline const std::shared_ptr<interface::GuiScreen> & gameGui() const {
            return this->m_core_GameGui;
        }
        
        inline const std::shared_ptr<utils::DevConsole> & developerConsole() const {
            return this->m_core_DeveloperConsole;
        }
        
        inline const std::shared_ptr<input::InputManager> & gameInput() const {
            return this->m_core_GameInput;
        }
        
        inline const std::shared_ptr<audio::AudioMixer> & gameAudio() const {
            return this->m_core_GameAudio;
        }
        
        inline const std::shared_ptr<objects::GameObjectManager> & gameObjects() const {
            return this->m_core_GameObjects;
        }

        inline const std::shared_ptr<resources::ResourceManager> & gameResources() const {
            return this->m_core_ResourceManager;
        }

        inline const std::shared_ptr<utils::SettingsManager> & gameSettings() const {
            return this->m_core_GameSettings;
        }

    public:
        CORE()  = default;
        ~CORE() = default;

        CORE(const CORE &other) = delete;
        CORE & operator=(const CORE &other) = delete;

    private:
        void firstUpdate();
        
        void secondUpdate();

        void pollEvent();
        
        void updateMousePos();

    private:
        std::shared_ptr<utils::DevConsole> m_core_DeveloperConsole;
        std::shared_ptr<resources::ResourceManager> m_core_ResourceManager;
        std::shared_ptr<utils::SettingsManager> m_core_GameSettings;
        std::shared_ptr<graphics::Window> m_core_GameWindow;
        std::shared_ptr<interface::GuiScreen> m_core_GameGui;
        std::shared_ptr<input::InputManager> m_core_GameInput;
        std::shared_ptr<audio::AudioMixer> m_core_GameAudio;
        std::shared_ptr<objects::GameObjectManager> m_core_GameObjects;

    private: // variables
        sf::Time m_DeltaTime {sf::Time::Zero};
        sf::Clock m_DeltaClock;
        unsigned int m_FPSCount {0u};
        bool m_ShadersSupport[2] {false, false};
    };
}