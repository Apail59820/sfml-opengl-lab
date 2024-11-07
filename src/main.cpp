#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "../include/Cube.h"

// Variables globales pour gérer l'angle de la caméra
float pitch = 0.0f;  // Rotation autour de l'axe X
float yaw = 0.0f;    // Rotation autour de l'axe Y
bool isFirstMouse = true;
sf::Vector2i lastMousePos;

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

void processMouseMovement(const sf::Vector2i& mousePos) {
    if (isFirstMouse) {
        lastMousePos = mousePos;
        isFirstMouse = false;
    }

    auto offsetX = static_cast<float>(mousePos.x - lastMousePos.x);
    auto offsetY = static_cast<float>(lastMousePos.y - mousePos.y);

    lastMousePos = mousePos;

    constexpr float sensitivity = 0.1f;
    offsetX *= sensitivity;
    offsetY *= sensitivity;

    yaw += offsetX;
    pitch += offsetY;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "OpenGL Lab", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    setupOpenGL();

    window.setMouseCursorVisible(true);
    window.setMouseCursorGrabbed(true);

    auto myCube = new Cube();

    while (window.isOpen()) {

        for (auto event = sf::Event(); window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            else if (event.type == sf::Event::MouseMoved) {
                processMouseMovement(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            }
        }

        sf::Vector2i windowCenter(static_cast<int>(window.getSize().x), static_cast<int>(window.getSize().y));
        sf::Mouse::setPosition(windowCenter);

        setProjection(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();

        std::cout << pitch << ", " << yaw << std::endl;

        // Appliquer les rotations de la caméra
        glRotatef(pitch, 1.0f, 0.0f, 0.0f);  // Rotation autour de l'axe X
        glRotatef(yaw, 0.0f, 1.0f, 0.0f);    // Rotation autour de l'axe Y

        glTranslatef(0.0f, 0.0f, -5.0f);  // Déplacement de la caméra en arrière

        window.clear();
        window.draw(*myCube);
        window.display();
    }

    delete myCube;

    return 0;
}