//
// Created by Amaury Paillard on 07/11/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics/RenderWindow.hpp"

#include "camera.h"

class Player {
public:
    Player(float startX, float startY, float startZ);

    void update(float deltaTime);
    void handleInput(float deltaTime);

    void setSpeed(const float newSpeed) { speed = newSpeed; }
    void setAcceleration(const float newAcceleration) { acceleration = newAcceleration; }

    [[nodiscard]] float getPositionX() const { return positionX; }
    [[nodiscard]] float getPositionY() const { return positionY; }
    [[nodiscard]] float getPositionZ() const { return positionZ; }

    Camera* getCamera() { return &camera; }

private:
    float positionX, positionY, positionZ;
    float speed, acceleration;
    float velocityY;
    bool isOnGround;

    float currentSpeedX, currentSpeedZ;
    float targetSpeedX, targetSpeedZ;

    Camera camera;
};

#endif //PLAYER_H
