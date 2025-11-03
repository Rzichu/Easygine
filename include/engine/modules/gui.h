#pragma once

#include "../defines.h"
#include "lang.h"
#include "resource_manager.h"

#include <TGUI/TGUI.hpp>

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

namespace easygine {
    class CORE;

    namespace interface {
        class GuiScreen {
            friend class easygine::CORE;
        public:
            inline tgui::GuiSFML & gui() {
                return *this->m_Gui;
            }

            inline const tgui::GuiSFML & gui() const {
                return *this->m_Gui;
            }

            bool loadCursorStyle(tgui::Cursor::Type type, const tgui::String &filename, tgui::Vector2u hotspot);
            
            inline void resetCursorStyle(tgui::Cursor::Type type) {
                tgui::Cursor::resetStyle(type);
            }

            void addFont(const std::string &font_name, const std::string &filename);
            
            void removeFont(const std::string &font_name);
            
            void setMainFont(const std::string &font_name);
            
            const tgui::Font & GetFont(const std::string &font_name) const;

            void setWrittenLang(const std::string &locale, bool save = false);

            void setSpokenLang(const std::string &locale, bool save = false);

            inline void setClipboard(const tgui::String &text) {
                tgui::BackendSFML sf_gui;
                sf_gui.setClipboard(text);
            }
            
            inline tgui::String getClipboard() const {
                tgui::BackendSFML sf_gui;
                return sf_gui.getClipboard();
            }

        public:
            GuiScreen()    = default;
            ~GuiScreen()   = default;

        private:
            bool init();

            void deinit();

            void render();
        
        private:
            std::unique_ptr<tgui::GuiSFML> m_Gui;
            std::vector<std::pair<std::string, tgui::Font>> m_Fonts;
            std::string m_CurrentLocale[2] {"en_US", "en_US"};
        };
    }
}