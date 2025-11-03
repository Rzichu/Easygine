#include "include/engine/engine.h"

int main() {
    auto &core_handle = easygine::CORE::core();

    core_handle.init(GAME_TITLE);

    core_handle.developerConsole()->toBuffer(std::string("Game title: ") + GAME_TITLE + std::string("\n"));
    core_handle.developerConsole()->toBuffer(std::string("Game version: ") + GAME_VERSION + std::string("\n"));

    core_handle.developerConsole()->enableConsole(true);

    core_handle.gameInput()->addAction("close", sf::Keyboard::Key::Escape, thor::Action::PressOnce);
    core_handle.gameInput()->addAction("open_console", sf::Keyboard::Key::F5, thor::Action::PressOnce);

    auto fpscounter = tgui::Label::create("");
    fpscounter->getRenderer()->setBackgroundColor(tgui::Color(0, 0, 0, 128));
    fpscounter->getRenderer()->setTextColor(tgui::Color::White);
    core_handle.gameGui()->gui().add(fpscounter);

    while (core_handle.gameWindow()->isOpen()) {
        core_handle.update();

        fpscounter->setText("FPS: " + std::to_string(core_handle.getFPS()));

        if (core_handle.gameInput()->checkAction("open_console")) {
            core_handle.developerConsole()->toggleConsole();
        }
        if (core_handle.gameInput()->keyDown(sf::Keyboard::M)) {
            core_handle.gameWindow()->changeWindowMode(easygine::graphics::EC_WindowMode::Maximized);
        }
        if (core_handle.gameInput()->keyDown(sf::Keyboard::W)) {
            core_handle.gameWindow()->changeWindowMode(easygine::graphics::EC_WindowMode::Windowed);
        }
        if (core_handle.gameInput()->checkAction("close")) {
            core_handle.gameWindow()->close();
        }

        core_handle.render();
    }

    core_handle.deinit();
	
    return 0;
}