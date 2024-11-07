#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

#include "../include/Cube.h"
#include "../include/camera.h"


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
}


int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "OpenGL Lab", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    setupOpenGL();

    window.setMouseCursorVisible(false);
    window.setMouseCursorGrabbed(true);

    auto myCube = new Cube();
    auto otherCube = new Cube();

    otherCube->setPosition(sf::Vector3f(5.f, 0.f, -5.f));

    Camera camera(window);
    sf::Clock clock;

    while (window.isOpen()) {
        for (auto event = sf::Event(); window.pollEvent(event);) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }


        camera.update(clock.restart().asSeconds());

        setProjection(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();

        camera.applyView();

        window.clear();
        window.draw(*myCube);
        window.draw(*otherCube);
        window.display();
    }

    delete myCube;
    delete otherCube;

    return 0;
}
