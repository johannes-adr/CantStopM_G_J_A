#include "iostream"
#include "RenderableDice.h"
#include "ColorScheme.h"
RenderableDice::RenderableDice(const int dice, const int size) : dice(dice),size(size) {
}

void RenderableDice::render(SubCanvas &canvas, GameWindow &gameWindow) {
    Array<Array<int,3>,3> diceMatrix = Dice::VISUAL_MATRIX[dice-1];
    float size3 = size/3;
    sf::RectangleShape rec{};
    rec.setPosition(0,0);
    rec.setSize(sf::Vector2f(size,size));
    rec.setFillColor(ColumnColor::BACKGROUND);
    canvas.draw(rec);
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (diceMatrix[y][x] == 1) {
                sf::CircleShape circ;
                circ.setPosition(size3 * x, size3 * y);
                circ.setRadius(size3 / 2 * 0.95);
                circ.setFillColor(sf::Color(44, 62, 80));
                canvas.draw(circ);
            }
        }
    }

}
