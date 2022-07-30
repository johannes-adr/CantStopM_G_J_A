#pragma once
#include "SFML/Graphics.hpp"
typedef sf::Color C;
namespace GeneralColor{
    static C BACKGROUND {254,250,224};
    static C TEXT_COLOR = sf::Color::Black;
}

namespace ColumnColor{
    static C BACKGROUND {254-50,250-50,224-50};
    static C PLAYER_PROGRESS[2] {{96,108,56},{221,161,94}};
    static C PLAYER_CHECKPOINT[2] {{40,54,24},{188,108,37}};
}
