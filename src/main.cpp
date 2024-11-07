#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

#include "../include/cube.h"
#include "../include/globals.h"
#include "../include/player.h"


void setProjection(const float width, const float height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    const float aspectRatio = width / height;
    glFrustum(-aspectRatio, aspectRatio, -1.0f, 1.0f, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

void setupOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_CLAMP);
}


int main() {
    Globals::window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "OpenGL Lab", sf::Style::Default, sf::ContextSettings(32));

    Globals::window->setVerticalSyncEnabled(true);

    setupOpenGL();

    Globals::window->setMouseCursorVisible(false);
    Globals::window->setMouseCursorGrabbed(true);

    const auto myCube = new cube();
    const auto otherCube = new cube();

    otherCube->setPosition(sf::Vector3f(5.f, 0.f, -5.f));

    sf::Clock clock;
    Player player(0.0f, 0.0f, 15.0f);

    while (Globals::window->isOpen()) {
        for (auto event = sf::Event(); Globals::window->pollEvent(event);) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                Globals::window->close();
            }
        }


        player.update(clock.restart().asSeconds());
        setProjection(static_cast<float>(Globals::window->getSize().x), static_cast<float>(Globals::window->getSize().y));


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        player.getCamera()->applyView();

        Globals::window->clear();
        Globals::window->draw(*myCube);
        Globals::window->draw(*otherCube);
        Globals::window->display();
    }

    delete myCube;
    delete otherCube;

    return 0;
}
