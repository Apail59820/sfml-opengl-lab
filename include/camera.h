//
// Created by Amaury Paillard on 07/11/2024.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "SFML/Graphics/RenderWindow.hpp"

class Player;

class Camera {
public:
    explicit Camera(Player *player);

    void update();

    void applyView() const;

    void processMouseMovement();

    [[nodiscard]] float getYaw() const { return yaw; }

private:
    Player *player;
    float pitch;
    float yaw;
    sf::Vector2i windowCenter;
    bool isFirstMouseMovement;
    const float sensitivity = 0.1f;

    void initializeCenter(const sf::RenderWindow &window);
};

#endif //CAMERA_H
