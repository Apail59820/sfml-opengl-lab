#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>

#include "../include/gui.h"

int main()
{
    auto window = sf::RenderWindow({1920u, 1080u}, "SFML OpenGL Lab");
    window.setFramerateLimit(144);
    if (!ImGui::SFML::Init(window))
        return -1;

    sf::Clock clock;
    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        ImGui::SFML::Update(window, clock.restart());

        GUI::Render();

        window.clear(sf::Color::White);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
