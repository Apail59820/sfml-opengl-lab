//
// Created by Amaury Paillard on 07/11/2024.
//
#include "../include/player.h"
#include "../include/camera.h"
#include "SFML/Window/Keyboard.hpp"

Player::Player(const float startX, const float startY, const float startZ)
    : positionX(startX), positionY(startY), positionZ(startZ), speed(5.0f), acceleration(10.0f),
      velocityY(0.0f), isOnGround(true), currentSpeedX(0.0f), currentSpeedZ(0.0f),
      targetSpeedX(0.0f), targetSpeedZ(0.0f), camera(this) {}

void Player::update(const float deltaTime) {
    handleInput(deltaTime);
    camera.update();
}

void Player::handleInput(const float deltaTime) {
    const float radYaw = camera.getYaw() * (3.14159265f / 180.0f);

    targetSpeedX = 0.0f;
    targetSpeedZ = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        targetSpeedX += speed * std::sin(radYaw);
        targetSpeedZ -= speed * std::cos(radYaw);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        targetSpeedX -= speed * std::sin(radYaw);
        targetSpeedZ += speed * std::cos(radYaw);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        targetSpeedX -= speed * std::cos(radYaw);
        targetSpeedZ -= speed * std::sin(radYaw);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        targetSpeedX += speed * std::cos(radYaw);
        targetSpeedZ += speed * std::sin(radYaw);
    }

    currentSpeedX += (targetSpeedX - currentSpeedX) * acceleration * deltaTime;
    currentSpeedZ += (targetSpeedZ - currentSpeedZ) * acceleration * deltaTime;

    positionX += currentSpeedX * deltaTime;
    positionZ += currentSpeedZ * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isOnGround) {
        velocityY = 5.0f;
        isOnGround = false;
    }

    if (!isOnGround) {
        velocityY -= 9.81f * deltaTime;
        positionY += velocityY * deltaTime;

        if (positionY <= 0.0f) {
            positionY = 0.0f;
            velocityY = 0.0f;
            isOnGround = true;
        }
    }
}