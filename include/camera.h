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
    void update();
    void applyView() const;
private:
    float pitch;
    float yaw;
    sf::Vector2i windowCenter;
    bool isFirstMouseMovement;
    const float sensitivity = 0.1f;

    void processMouseMovement();
};

#endif //CAMERA_H
