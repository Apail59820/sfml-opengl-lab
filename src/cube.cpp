//
// Created by Amaury Paillard on 07/11/2024.
//

#include "../include/cube.h"

#include <SFML/OpenGL.hpp>

cube::cube() : size(1.0f) {
    this->position = sf::Vector3f(0.0f, 0.0f, 0.0f);
}

cube::~cube() = default;

float cube::getSize() const {
    return size;
}

void cube::setSize(const float size) {
    cube::size = size;
}

sf::Vector3f cube::getPosition() const {
    return position;
}

void cube::setPosition(const sf::Vector3f &newPosition) {
    this->position = newPosition;
}


void cube::draw(sf::RenderTarget &target, sf::RenderStates states) const {
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
