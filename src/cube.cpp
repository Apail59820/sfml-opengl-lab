//
// Created by Amaury Paillard on 07/11/2024.
//

#include "../include/Cube.h"

#include <SFML/OpenGL.hpp>

Cube::Cube() : size(1.0f) {
    this->position = sf::Vector3f(3.0f, 0.0f, 0.0f);
}

Cube::~Cube() = default;

float Cube::getSize() const {
    return size;
}

void Cube::setSize(const float size) {
    Cube::size = size;
}

sf::Vector3f Cube::getPosition() const {
    return position;
}

void Cube::setPosition(const sf::Vector3f &newPosition) {
    this->position = newPosition;
}


void Cube::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);

    glBegin(GL_QUADS);
        glColor3f(size, 0.0f, 0.0f);
        glVertex3f(-size, -size,  size);
        glVertex3f( size, -size,  size);
        glVertex3f( size,  size,  size);
        glVertex3f(-size,  size,  size);

        glColor3f(0.0f, size, 0.0f);
        glVertex3f(-size, -size, -size);
        glVertex3f(-size,  size, -size);
        glVertex3f( size,  size, -size);
        glVertex3f( size, -size, -size);

        glColor3f(0.0f, 0.0f, size);
        glVertex3f(-size, -size, -size);
        glVertex3f(-size, -size,  size);
        glVertex3f(-size,  size,  size);
        glVertex3f(-size,  size, -size);

        glColor3f(size, size, 0.0f);
        glVertex3f( size, -size, -size);
        glVertex3f( size,  size, -size);
        glVertex3f( size,  size,  size);
        glVertex3f( size, -size,  size);

        glColor3f(size, 0.0f, size);
        glVertex3f(-size,  size, -size);
        glVertex3f(-size,  size,  size);
        glVertex3f( size,  size,  size);
        glVertex3f( size,  size, -size);

        glColor3f(0.0f, size, size);
        glVertex3f(-size, -size, -size);
        glVertex3f( size, -size, -size);
        glVertex3f( size, -size,  size);
        glVertex3f(-size, -size,  size);
    glEnd();

    glPopMatrix();
}
