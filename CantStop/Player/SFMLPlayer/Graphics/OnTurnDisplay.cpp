#include "OnTurnDisplay.h"

#include <utility>
#include "../../../Game/Game.h"
#include "ColorScheme.h"

void OnTurnDisplay::render(SubCanvas &canvas, GameWindow &gameWindow) {
    std::string txt; //Your/Other
    if(game->getCurrentPlayer() == player){
        txt = "Your";
    }else{
        txt = "Other";
    }


    sf::Text txtYourOther{txt, GameWindow::getDefaultFont(), 20};
    txtYourOther.setPosition(0, 0);
    txtYourOther.setOutlineColor(sf::Color::Black);
    txtYourOther.setOutlineThickness(1);
    txtYourOther.setFillColor(ColumnColor::PLAYER_CHECKPOINT[game->getPlayerId(*game->getCurrentPlayer())]);
    canvas.draw(txtYourOther);
    sf::Text txtTurn{" turn",GameWindow::getDefaultFont(),20};
    txtTurn.setPosition(txtYourOther.getGlobalBounds().width,0);
    txtTurn.setOutlineColor(sf::Color::Black);
    txtTurn.setOutlineThickness(1);
    txtTurn.setFillColor(ColumnColor::PLAYER_PROGRESS[game->getPlayerId(*game->getCurrentPlayer())]);
    canvas.draw(txtTurn);
}

OnTurnDisplay::OnTurnDisplay(std::shared_ptr<Game> game, IPlayer *player): game(std::move(game)), player(player) {}
