#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

namespace easygine {
    class CORE;

    namespace graphics {
        enum class EC_WindowMode {
              Windowed
            , Maximized
            , Borderless
            , Fullscreen
        };

        class WindowViews {
            friend class easygine::CORE;
        public:
            void addView(sf::View view);

            void removeView(unsigned long long index);

        public:
            inline bool empty() {
                return this->m_Views.empty();
            }

            inline unsigned long long size() {
                return this->m_Views.size();
            }

            inline const auto & getViews() const {
                return this->m_Views;
            }

            inline sf::View & operator[](unsigned long long index) {
                return this->m_Views.at(index);
            }
            
            inline const sf::View & operator[](unsigned long long index) const {
                return this->m_Views.at(index);
            }

        protected:
            std::vector<sf::View> m_Views;
        };

        class Window {
            friend class easygine::CORE;
        public:
            void changeWindowMode(EC_WindowMode mode, bool save = false);

            inline WindowViews & getViews() {
                return this->m_WindowViews;
            }

            inline const WindowViews & getViews() const {
                return this->m_WindowViews;
            }

            void cursorVisible(bool hide);
            
            void verticalSync(bool enable, bool save = false);

            void setFramerate(unsigned int framerate, bool save = false);
            
            void windowVisible(bool hide);

            bool setResolution(sf::VideoMode mode, bool save = false);
            
            void setPos(const sf::Vector2i &pos);
            
            void setSize(const sf::Vector2u &size);

            inline sf::Vector2i getPos() const {
                return this->m_Window->getPosition();
            }
            
            inline sf::Vector2u getSize() const {
                return this->m_Window->getSize();
            }
            
            inline sf::Event getEvent() const {
                return this->m_Event;
            }

            inline sf::VideoMode getVidMode() const {
                return this->m_VideoMode;
            }
            
            inline const sf::String & getTitle() const {
                return this->m_Title;
            }

            inline const std::vector<sf::VideoMode> & getFullscreenModes() const {
                return this->m_FullscreenModes;
            }

            inline bool getVsync() const {
                return this->m_Vsync;
            }

            inline bool focused() const {
                return this->m_Window->hasFocus();
            }
            
            inline bool isOpen() const {
                return this->m_Window->isOpen();
            }

            void screenshot();

            inline void setClipboard(const sf::String &text) {
                sf::Clipboard::setString(text);
            }
            
            inline sf::String getClipboard() const {
                return sf::Clipboard::getString();
            }

            void close();

        public:
            Window()    = default;
            ~Window()   = default;

            Window(const Window &copy)              = delete;
            Window & operator=(const Window &copy)  = delete;

        private:
            bool init(const sf::String &title);
            
            void deinit();
        
        private:
            std::shared_ptr<sf::RenderTexture> m_RenderTexture {nullptr};
            std::shared_ptr<sf::RenderWindow> m_Window {nullptr};
            WindowViews m_WindowViews;
            sf::String m_Title {"Placeholder title"};
            EC_WindowMode m_CurrWinMode {EC_WindowMode::Windowed};
            sf::VideoMode m_VideoMode {480u, 270u, 32u};
            std::vector<sf::VideoMode> m_FullscreenModes;
            unsigned int m_FPSLimit {60u};
            bool m_Vsync {false};
            sf::Event m_Event;
        };
    }
}