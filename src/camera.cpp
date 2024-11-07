//
// Created by Amaury Paillard on 07/11/2024.
//

#include "../include/camera.h"

#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include <SFML/OpenGL.hpp>

Camera::Camera(const sf::RenderWindow &window)
    : pitch(0.0f), yaw(0.0f), isFirstMouseMovement(true) {
    initializeCenter(window);
}

void Camera::initializeCenter(const sf::RenderWindow &window) {
    windowCenter = sf::Vector2i(static_cast<int>(window.getPosition().x + window.getSize().x / 2),
                                static_cast<int>(window.getPosition().y + window.getSize().y / 2));
}

void Camera::processMouseMovement() {
    const sf::Vector2i mousePos = sf::Mouse::getPosition();

    if (isFirstMouseMovement) {
        sf::Mouse::setPosition(windowCenter);
        isFirstMouseMovement = false;
        return;
    }

    auto offsetX = static_cast<float>(mousePos.x - windowCenter.x);
    auto offsetY = static_cast<float>(mousePos.y - windowCenter.y);

    if (std::abs(offsetX) < 2.f && std::abs(offsetY) < 2.f) {
        return;
    }

    offsetX *= sensitivity;
    offsetY *= sensitivity;

    yaw += offsetX;
    pitch += offsetY;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    sf::Mouse::setPosition(windowCenter);
}

void Camera::update() {
    processMouseMovement();
}

void Camera::applyView() const {
    glRotatef(pitch, 1.0f, 0.0f, 0.0f);
    glRotatef(yaw, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -5.0f);
}