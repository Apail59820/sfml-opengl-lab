//
// Created by Amaury Paillard on 07/11/2024.
//

#include "../include/camera.h"

#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include <SFML/OpenGL.hpp>

#include "SFML/Window/Keyboard.hpp"

Camera::Camera(const sf::RenderWindow &window)
    : pitch(0.0f), yaw(0.0f), isFirstMouseMovement(true) {
    initializeCenter(window);
}

void Camera::initializeCenter(const sf::RenderWindow &window) {
    windowCenter = sf::Vector2i(static_cast<int>(window.getPosition().x + window.getSize().x / 2),
                                static_cast<int>(window.getPosition().y + window.getSize().y / 2));
}

void Camera::processKeyboardInput(const float deltaTime) {
    const float radYaw = yaw * (3.14159265f / 180.0f);

    targetSpeedX = 0.0f;
    targetSpeedZ = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        targetSpeedX += maxSpeed * std::sin(radYaw);
        targetSpeedZ -= maxSpeed * std::cos(radYaw);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        targetSpeedX -= maxSpeed * std::sin(radYaw);
        targetSpeedZ += maxSpeed * std::cos(radYaw);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        targetSpeedX -= maxSpeed * std::cos(radYaw);
        targetSpeedZ -= maxSpeed * std::sin(radYaw);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        targetSpeedX += maxSpeed * std::cos(radYaw);
        targetSpeedZ += maxSpeed * std::sin(radYaw);
    }

    currentSpeedX += (targetSpeedX - currentSpeedX) * acceleration * deltaTime;
    currentSpeedZ += (targetSpeedZ - currentSpeedZ) * acceleration * deltaTime;

    if (targetSpeedX == 0.0f) {
        currentSpeedX += -currentSpeedX * deceleration * deltaTime;
    }
    if (targetSpeedZ == 0.0f) {
        currentSpeedZ += -currentSpeedZ * deceleration * deltaTime;
    }

    positionX += currentSpeedX * deltaTime;
    positionZ += currentSpeedZ * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isOnGround) {
        velocityY = jumpStrength;
        isOnGround = false;
    }
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



void Camera::update(const float deltaTime) {
    processMouseMovement();
    processKeyboardInput(deltaTime);

    if (!isOnGround) {
        velocityY += gravity * deltaTime;
        positionY += velocityY * deltaTime;

        if (positionY <= 0.0f) {
            positionY = 0.0f;
            velocityY = 0.0f;
            isOnGround = true;
        }
    }
}

void Camera::applyView() const {
    glRotatef(pitch, 1.0f, 0.0f, 0.0f);
    glRotatef(yaw, 0.0f, 1.0f, 0.0f);
    glTranslatef(-positionX, -positionY, -positionZ);
}
