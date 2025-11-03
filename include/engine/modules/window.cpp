#include "window.h"

#include "dev_console.h"
#include "gui.h"
#include "../defines.h"
#include "../engine.h"
#include "../../misc/LogSys/log_sys.h"
#include "../../misc/ChronoClock/chrono_clock.h"
#include "../../misc/EnumEra/enum_era.h"

#include <string>

#ifndef _RELEASE
namespace easygine {
    extern aether::lgs::Timer EngineClock;
    extern aether::lgs::Logger EngineLogger;
}
#endif

namespace easygine {
    namespace graphics {
        void WindowViews::addView(sf::View view) {
            this->m_Views.emplace_back(view);
        }

        void WindowViews::removeView(unsigned long long index) {
            if (index < this->m_Views.size()) {
                this->m_Views.erase(this->m_Views.begin() + index);
            }
        }
        
        bool Window::init(const sf::String &title) {
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Window initialization started.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

            this->m_Title = title;
            this->m_FullscreenModes = sf::VideoMode::getFullscreenModes();

            std::string win_mode = easygine::CORE::core().gameSettings()->getStringSetting(GAME_SETTING_WINDOW_MODE, enumera_TO_STRING(EC_WindowMode::Windowed), false);
            if (win_mode == enumera_TO_STRING(EC_WindowMode::Fullscreen)) {
                this->m_CurrWinMode = EC_WindowMode::Fullscreen;
            }
            else if (win_mode == enumera_TO_STRING(EC_WindowMode::Borderless)) {
                this->m_CurrWinMode = EC_WindowMode::Borderless;
            }
            else if (win_mode == enumera_TO_STRING(EC_WindowMode::Maximized)) {
                this->m_CurrWinMode = EC_WindowMode::Maximized;
            }
            else if (win_mode == enumera_TO_STRING(EC_WindowMode::Windowed)) {
                this->m_CurrWinMode = EC_WindowMode::Windowed;
            }
            else {
                this->m_CurrWinMode = EC_WindowMode::Windowed;
            }
            sf::VideoMode vid_mode;
            vid_mode.width = easygine::CORE::core().gameSettings()->getUintSetting(GAME_SETTING_WINDOW_RATIO_X, 400u, false);
            vid_mode.height = easygine::CORE::core().gameSettings()->getUintSetting(GAME_SETTING_WINDOW_RATIO_Y, 200u, false);
            vid_mode.bitsPerPixel = easygine::CORE::core().gameSettings()->getUintSetting(GAME_SETTING_BITS_PER_PIXEL, 32u, false);
            this->m_VideoMode = vid_mode;

            this->m_Window = std::make_shared<sf::RenderWindow>(this->m_VideoMode, this->m_Title, sf::Style::Default);

            if (!this->m_Window) {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Window creation failed.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);

                return false;
            }

            this->m_RenderTexture = std::make_shared<sf::RenderTexture>();
            if (!this->m_RenderTexture->create(this->m_Window->getSize().x, this->m_Window->getSize().y)) {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Render texture creation failed.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::FatalError, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::FatalError, true, true);

                return false;
            }

            this->setFramerate(easygine::CORE::core().gameSettings()->getUintSetting(GAME_SETTING_FPS_LIMIT, 60, false), false);
            this->verticalSync(easygine::CORE::core().gameSettings()->getBoolSetting(GAME_SETTING_VSYNC, false, false), false);

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Window initialization successful.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);

            return true;
        }

        void Window::deinit() {
            
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Window deinitialized.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }

        void Window::changeWindowMode(EC_WindowMode mode, bool save) {
            switch (mode) {
                case EC_WindowMode::Windowed: {
                    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
                    mode.width /= 2;
                    mode.height /= 2;
                    this->m_Window->create(mode, this->m_Title, sf::Style::Close | sf::Style::Resize);
                    this->m_RenderTexture->create(this->m_Window->getSize().x, this->m_Window->getSize().y);
                    this->setFramerate(this->m_FPSLimit, save);
                    internal_handle_core.gameGui()->gui().setRelativeView({0, 0, 1, 1});
                    this->m_Window->setPosition({0, 0});
                    this->m_CurrWinMode = EC_WindowMode::Windowed;
                    if (save) {
                        easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_WINDOW_MODE, enumera_TO_STRING(EC_WindowMode::Windowed));
                    }

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Window mode changed to \"")lgs_MSG(enumera_TO_STRING(EC_WindowMode::Windowed))lgs_MSG("\".");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Info, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Info, true, true);
            
                    break;
                }
                case EC_WindowMode::Maximized: {
                    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
                    this->m_Window->create(mode, this->m_Title, sf::Style::Close);
                    this->m_RenderTexture->create(this->m_Window->getSize().x, this->m_Window->getSize().y);
                    this->setFramerate(this->m_FPSLimit, save);
                    internal_handle_core.gameGui()->gui().setRelativeView({0, 0, 1, 1});
                    this->m_CurrWinMode = EC_WindowMode::Maximized;
                    if (save) {
                        easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_WINDOW_MODE, enumera_TO_STRING(EC_WindowMode::Maximized));
                    }

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Window mode changed to \"")lgs_MSG(enumera_TO_STRING(EC_WindowMode::Maximized))lgs_MSG("\".");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Info, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Info, true, true);
            
                    break;
                }
                case EC_WindowMode::Borderless: {
                    this->m_Window->create(this->m_VideoMode, this->m_Title, sf::Style::None);
                    this->m_RenderTexture->create(this->m_Window->getSize().x, this->m_Window->getSize().y);
                    this->setFramerate(this->m_FPSLimit, save);
                    internal_handle_core.gameGui()->gui().setRelativeView({0, 0, 1, 1});
                    this->m_CurrWinMode = EC_WindowMode::Borderless;
                    if (save) {
                        easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_WINDOW_MODE, enumera_TO_STRING(EC_WindowMode::Borderless));
                    }

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Window mode changed to \"")lgs_MSG(enumera_TO_STRING(EC_WindowMode::Borderless))lgs_MSG("\".");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Info, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Info, true, true);
            
                    break;
                }
                case EC_WindowMode::Fullscreen: {
                    this->m_Window->create(this->m_VideoMode, this->m_Title, sf::Style::Fullscreen);
                    this->m_RenderTexture->create(this->m_Window->getSize().x, this->m_Window->getSize().y);
                    this->setFramerate(this->m_FPSLimit, save);
                    internal_handle_core.gameGui()->gui().setRelativeView({0, 0, 1, 1});
                    this->m_CurrWinMode = EC_WindowMode::Fullscreen;
                    if (save) {
                        easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_WINDOW_MODE, enumera_TO_STRING(EC_WindowMode::Fullscreen));
                    }

                    lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Window mode changed to \"")lgs_MSG(enumera_TO_STRING(EC_WindowMode::Fullscreen))lgs_MSG("\".");
                    CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Info, false, false));
                    lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Info, true, true);
            
                    break;
                }
            }
        }

        void Window::cursorVisible(bool hide) {        
            this->m_Window->setMouseCursorVisible(hide);

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Cursor toggled ")lgs_MSG((hide ? "on" : "off"))lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Info, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Info, true, true);
        }

        void Window::verticalSync(bool enable, bool save) {
            if (enable && this->m_FPSLimit > 0) {
                this->setFramerate(0, false);
            }
            this->m_Window->setVerticalSyncEnabled(enable);
            this->m_Vsync = enable;
            if (save) {
                easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_VSYNC, enable);
            }

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Vertical sync toggled ")lgs_MSG((enable ? "on, framerate limit disabled" : "off"))lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Info, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Info, true, true);
        }

        void Window::setFramerate(unsigned int framerate, bool save) {
            if (this->m_Vsync && framerate > 0) {
                this->verticalSync(false, false);
            }
            this->m_Window->setFramerateLimit(framerate);
            this->m_FPSLimit = framerate;
            if (save) {
                easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_FPS_LIMIT, framerate);
            }

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Framerate limit set to: ")lgs_MSG(framerate)lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Info, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Info, true, true);
        }

        void Window::windowVisible(bool hide) {
            this->m_Window->setVisible(hide);

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Window visibility toggled ")lgs_MSG((hide ? "on" : "off"))lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Info, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Info, true, true);
        }

        bool Window::setResolution(sf::VideoMode mode, bool save) {
            this->m_VideoMode = mode;
            this->changeWindowMode(this->m_CurrWinMode, false);
            if (save) {
                easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_WINDOW_RATIO_X, mode.width);
                easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_WINDOW_RATIO_Y, mode.height);
                easygine::CORE::core().gameSettings()->setSetting(GAME_SETTING_BITS_PER_PIXEL, mode.bitsPerPixel);
            }
            
            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Resolution set to ")lgs_MSG(this->m_VideoMode.width)lgs_MSG("x")
                lgs_MSG(this->m_VideoMode.height)lgs_MSG(", ")lgs_MSG(this->m_VideoMode.bitsPerPixel)lgs_MSG("bpp.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Info, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Info, true, true);

            return true;
        }

        void Window::setPos(const sf::Vector2i &pos) {
            this->m_Window->setPosition(pos);

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Window's position set to x: ")lgs_MSG(pos.x)lgs_MSG(", y: ")lgs_MSG(pos.y)lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }

        void Window::setSize(const sf::Vector2u &size) {
            this->m_Window->setSize(size);

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Window's size set to x: ")lgs_MSG(size.x)lgs_MSG(", y: ")lgs_MSG(size.y)lgs_MSG(".");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }

        void Window::screenshot() {
            sf::Texture screenTex;
            screenTex.create(this->m_VideoMode.width, this->m_VideoMode.height);
            screenTex.update(*this->m_Window);
            sf::Image screenshot = screenTex.copyToImage();

            aether::chrono_clock::Calendar current_time;
            current_time.loadLocal();
            
            if (screenshot.saveToFile(std::string(GAME_SCREENSHOTS_DIR) + current_time.toString() + std::string(".jpg"))) {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Screenshot taken.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
            }
            else {
                lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Couldn't take a screenshot.");
                CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Warning, false, false));
                lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Warning, true, true);
            }
        }

        void Window::close() {
            this->m_Window->close();

            lgs_LOGGER_MSG(EngineLogger)lgs_MSG("Close event processed.");
            CMD_LOG(*internal_handle_core.developerConsole())CMD_MSG(lgs_OUT(EngineLogger, 0.0, aether::lgs::MsgLvl::Debug, false, false));
            lgs_LOG(EngineLogger, lgs_TIMER_TIME(EngineClock), aether::lgs::MsgLvl::Debug, true, true);
        }
    }
}