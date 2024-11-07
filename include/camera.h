//
// Created by Amaury Paillard on 07/11/2024.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "SFML/Graphics/RenderWindow.hpp"

class Camera {
public:
    explicit Camera(const sf::RenderWindow& window);

    void initializeCenter(const sf::RenderWindow& window);
    void update(float deltaTime);
    void applyView() const;
private:
    float pitch;
    float yaw;
    sf::Vector2i windowCenter;
    bool isFirstMouseMovement;
    const float sensitivity = 0.1f;

    float positionX{};
    float positionY{};
    float positionZ = -5.f;

    float currentSpeedX{};
    float currentSpeedZ{};
    float targetSpeedX{};
    float targetSpeedZ{};

    const float maxSpeed = 5.0f;
    const float acceleration = 10.0f;
    const float deceleration = 5.0f;

    float velocityY{};
    bool isOnGround{};
    const float jumpStrength = 5.0f;
    const float gravity = -9.81f;

    void processMouseMovement();
    void processKeyboardInput(float deltaTime);
};

#endif //CAMERA_H
