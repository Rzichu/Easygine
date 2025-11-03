#include "../engine.h"

#include "dev_console.h"
#include "../../misc/LogSys/log_sys.h"
#include "../../misc/ChronoClock/chrono_clock.h"

#include <nlohmann/json.hpp>

#include <fstream>
#include <string>
#include <future>

#ifndef _RELEASE
namespace easygine {
    aether::lgs::Timer EngineClock;
    aether::lgs::Logger EngineLogger("Engine Logger", "log.txt");
}
#endif

namespace easygine {
    CORE internal_handle_core;

    bool CORE::init(const sf::String &title) {
        this->m_core_DeveloperConsole = std::make_shared<utils::DevConsole>();
        if (!this->m_core_DeveloperConsole) {
            return false;
        }
        
        lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Initialization started.");
        CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Info, false, false));
        lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Info, true, true);

        this->m_core_GameSettings = std::make_shared<utils::SettingsManager>();
        this->m_core_GameSettings->initSettingFile(std::string(GAME_SETTINGS_PATH) + std::string("settings.json"));

        this->m_ShadersSupport[0ull] = sf::Shader::isAvailable();
        if (this->m_ShadersSupport[0ull]) {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Shaders supported.");
            CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Info, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Info, true, true);

            this->m_ShadersSupport[1ull] = sf::Shader::isGeometryAvailable();
            if (this->m_ShadersSupport[1ull]) {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Geometry shaders supported.");
                CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Info, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Info, true, true);
            }
            else {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Geometry shaders not supported.");
                CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);
            }
        }
        else {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Shaders not supported.");
            CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);
        }

        this->m_core_ResourceManager = std::make_shared<resources::ResourceManager>();
        if (!this->m_core_ResourceManager) {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Couldn't start Resource Management module.");
            CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);

            return false;
        }
        if (!this->m_core_ResourceManager->init()) {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Resource Management initialization failed.");
            CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);

            return false;
        }

        this->m_core_GameWindow = std::make_shared<graphics::Window>();
        if (!this->m_core_GameWindow) {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Couldn't start Window module.");
            CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);

            return false;
        }
        if (!this->m_core_GameWindow->init(title)) {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Window initialization failed.");
            CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);

            return false;
        }

        this->m_core_GameGui = std::make_shared<interface::GuiScreen>();
        if (!this->m_core_GameGui) {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Couldn't start GUI module.");
            CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);

            return false;
        }
        if (!this->m_core_GameGui->init()) {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("GUI initialization failed.");
            CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);

            return false;
        }
        this->m_core_GameGui->m_Gui->setTarget(*this->m_core_GameWindow->m_RenderTexture);
        if (!this->m_core_GameGui->m_Gui->getTarget()) {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("GUI initialization failed.");
            CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);

            return false;
        }

        if (!this->m_core_DeveloperConsole->init(this->m_core_GameGui)) {
            return false;
        }

        this->m_core_GameInput = std::make_shared<input::InputManager>();
        if (!this->m_core_GameInput) {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Couldn't start Input module.");
            CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);

            return false;
        }
        if (!this->m_core_GameInput->init()) {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Input initialization failed.");
            CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);

            return false;
        }

        this->m_core_GameAudio = std::make_shared<audio::AudioMixer>();
        if (!this->m_core_GameAudio) {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Couldn't start Audio module.");
            CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);

            return false;
        }
        if (!this->m_core_GameAudio->init()) {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Audio initialization failed.");
            CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);

            return false;
        }

        this->m_core_GameObjects = std::make_shared<objects::GameObjectManager>();
        if (!this->m_core_GameObjects) {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Couldn't start Game Objects module.");
            CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);

            return false;
        }
        if (!this->m_core_GameObjects->init()) {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Game Objects initialization failed.");
            CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);

            return false;
        }

        this->m_core_GameWindow->changeWindowMode(this->m_core_GameWindow->m_CurrWinMode, false);
        
        lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Initialization succeeded.");
        CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
        lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

        return true;
    }

    void CORE::deinit() {
        lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Deinitializating.");
        CMD_LOG(*internal_handle_core.m_core_DeveloperConsole)CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
        lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

        this->m_core_GameObjects->deinit();
        this->m_core_GameAudio->deinit();
        this->m_core_GameInput->deinit();
        this->m_core_DeveloperConsole->deinit();
        this->m_core_GameGui->deinit();
        this->m_core_GameWindow->deinit();
        this->m_core_ResourceManager->deinit();
    }

    void CORE::update() {
        this->m_DeltaTime = this->m_DeltaClock.restart();
        this->m_FPSCount = static_cast<unsigned int>(1.0f / this->m_DeltaTime.asSeconds());

        this->pollEvent();
        this->updateMousePos();

        this->firstUpdate();
        this->secondUpdate();
    }

    void CORE::render() {
        this->m_core_GameWindow->m_RenderTexture->clear();
        if (!this->m_core_GameWindow->m_WindowViews.empty()) {
            for (auto &view : this->m_core_GameWindow->m_WindowViews.m_Views) {
                this->m_core_GameWindow->m_RenderTexture->setView(view);
                this->m_core_GameObjects->render(*this->m_core_GameWindow->m_RenderTexture, sf::RenderStates());
            }
            this->m_core_GameWindow->m_RenderTexture->display();
            this->m_core_GameWindow->m_RenderTexture->setView(this->m_core_GameWindow->m_Window->getView());
        }
        else {
            this->m_core_GameObjects->render(*this->m_core_GameWindow->m_RenderTexture, sf::RenderStates());
            this->m_core_GameWindow->m_RenderTexture->display();
        }
        this->m_core_GameGui->render();

        this->m_core_GameWindow->m_Window->clear();
        this->m_core_GameWindow->m_Window->draw(sf::Sprite(this->m_core_GameWindow->m_RenderTexture->getTexture()), sf::RenderStates());
        this->m_core_GameWindow->m_Window->display();
    }

    void CORE::firstUpdate() {
        this->m_core_GameObjects->update();
        this->m_core_GameObjects->doFirstUpdates(this->m_DeltaTime);
    }

    void CORE::secondUpdate() {
        this->m_core_GameObjects->doUpdates(this->m_DeltaTime);
        this->m_core_GameAudio->update();
    }

    void CORE::pollEvent() {
        this->m_core_GameInput->getActionMap().clearEvents();

        while (this->m_core_GameWindow->m_Window->pollEvent(this->m_core_GameWindow->m_Event)) {
            if (this->m_core_GameWindow->m_Event.type == sf::Event::Resized) {
                this->m_core_GameWindow->m_Window->setView(sf::View(sf::FloatRect(0.0f, 0.0f, this->m_core_GameWindow->m_Event.size.width, this->m_core_GameWindow->m_Event.size.height)));
                this->m_core_GameWindow->m_RenderTexture->create(this->m_core_GameWindow->getSize().x, this->m_core_GameWindow->getSize().y);
            }

            if (this->m_core_DeveloperConsole->isVisible()) {
                if (this->m_core_GameInput->keyDown(sf::Keyboard::Key::Up)) {
                    this->m_core_DeveloperConsole->loadHistory(true);
                }
                else if (this->m_core_GameInput->keyDown(sf::Keyboard::Key::Down)) {
                    this->m_core_DeveloperConsole->loadHistory(false);
                }
                else if (this->m_core_GameInput->keyDown(sf::Keyboard::Key::Enter)) {
                    this->m_core_DeveloperConsole->parseLine();
                }
            }
            
            this->m_core_GameGui->m_Gui->handleEvent(this->m_core_GameWindow->m_Event);
            this->m_core_GameInput->getActionMap().pushEvent(this->m_core_GameWindow->m_Event);
            this->m_core_GameInput->getActionMap().invokeCallbacks(this->m_core_GameInput->m_Callbacks, nullptr);
        }
    }

    void CORE::updateMousePos() {
        this->m_core_GameInput->m_MousePosWin = sf::Mouse::getPosition(*this->m_core_GameWindow->m_Window);
        this->m_core_GameInput->m_MousePosView = this->m_core_GameWindow->m_Window->mapPixelToCoords(this->m_core_GameInput->m_MousePosWin);
    }
}