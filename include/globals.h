//
// Created by Amaury Paillard on 07/11/2024.
//

#ifndef GLOBALS_H
#define GLOBALS_H
#include <memory>

#include "SFML/Graphics/RenderWindow.hpp"

namespace Globals {
    inline std::unique_ptr<sf::RenderWindow> window;
}
#endif //GLOBALS_H
