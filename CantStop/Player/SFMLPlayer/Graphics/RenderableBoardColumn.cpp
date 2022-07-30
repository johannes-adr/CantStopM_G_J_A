#include "RenderableBoardColumn.h"
#include "../../../Game/Game.h"
#include "../../../../JdrSFML/JdrSFML.h"
#include "ColorScheme.h"
RenderableBoardColumn::RenderableBoardColumn(std::shared_ptr<Game> game, int col): game(std::move(game)),col(col) {

}

void RenderableBoardColumn::render(SubCanvas &canvas, GameWindow &gameWindow) {
    auto columns = game->getColumnsCopy();
    int col = this->col;
    auto& column = columns[col];
    float backgroundHeight = FIELD_HEIGHT * (float)column.height;
    sf::RectangleShape background{};
    background.setSize(sf::Vector2f(COL_WIDTH,backgroundHeight));
    background.setFillColor(ColumnColor::BACKGROUND);
    canvas.draw(background);

    auto renderPlayer = [&canvas,column,backgroundHeight](int playerId){
        float x = playerId * COL_WIDTH2;


        auto progress = column.playerProgress[playerId];
        if(progress.fieldProgress == 0)return;


        sf::RectangleShape checkPointRect{};
        int checkPointRectHeight = progress.checkPoint * FIELD_HEIGHT;
        checkPointRect.setFillColor(ColumnColor::PLAYER_CHECKPOINT[playerId]);

        checkPointRect.setPosition(x, backgroundHeight-checkPointRectHeight);
        checkPointRect.setSize(sf::Vector2f(COL_WIDTH2, checkPointRectHeight));
        canvas.draw(checkPointRect);


        sf::RectangleShape progressRect{};
        int progressRectHeight = (progress.fieldProgress - progress.checkPoint) * FIELD_HEIGHT;
        progressRect.setFillColor(ColumnColor::PLAYER_PROGRESS[playerId]);
        progressRect.setPosition(x,backgroundHeight-checkPointRectHeight-progressRectHeight);
        progressRect.setSize(sf::Vector2f(COL_WIDTH2,progressRectHeight));
        canvas.draw(progressRect);
    };

    renderPlayer(0);
    renderPlayer(1);

    sf::Text t{};
    t.setFont(GameWindow::getDefaultFont());
    t.setString(std::to_string(col+2));
    t.setFillColor(GeneralColor::TEXT_COLOR);
    t.setPosition(COL_WIDTH2 - t.getGlobalBounds().width / 2,backgroundHeight + 10);
    canvas.draw(t);
}
