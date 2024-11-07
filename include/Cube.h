//
// Created by Amaury Paillard on 07/11/2024.
//

#ifndef CUBE_H
#define CUBE_H
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/System/Vector3.hpp"

class Cube final : public sf::Drawable {

public:

    Cube();
    ~Cube() override;

    [[nodiscard]] float getSize() const;
    void setSize(float size);

    void setPosition(const sf::Vector3f& newPosition);
    [[nodiscard]] sf::Vector3f getPosition() const;

private:

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Vector3f position;
    float size{};

};
#endif //CUBE_H
