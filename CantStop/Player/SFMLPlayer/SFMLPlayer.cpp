#include "SFMLPlayer.h"
#include "thread"
#include "Graphics/RenderableBoardColumn.h"
#include "Graphics/GameBackground.h"
#include "Graphics/ColorScheme.h"
#include <chrono>
#include <thread>
#include "iostream"
#include "Graphics/OnTurnDisplay.h"
#include "Graphics/RenderableDice.h"

constexpr int DICE_SIZE = 50;

SelectedColumns SFMLPlayer::selectColumns(DiceCombination &combs, Game &game) {
    currentDices.clear();
    for (int diceNum: combs.dices) {
        this->currentDices.push_back(RenderableDice(diceNum, DICE_SIZE));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    for (const Vec<int> &comb: combs.combinations) {
        std::string lbl;
        for (int n: comb)lbl += std::to_string(n) + "&";
        lbl.pop_back();

        chooseDiceButtons.push_back(std::pair(Button(lbl),comb));
        auto& b = chooseDiceButtons[chooseDiceButtons.size()-1];
        if (chooseDiceButtons.size() > 1) {
            b.first.setPosition(0, chooseDiceButtons[chooseDiceButtons.size() - 2].first.getBox().getSize().y * 1.2);
        }
        b.first.setBgColor(sf::Color::Black);

    }

    while (!btnSkip->gotPressed()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        for(auto& btn : chooseDiceButtons){
            if(btn.first.gotPressed()){
                auto second = btn.second;
                chooseDiceButtons.clear();
                return second;
            }
        }
    }
    chooseDiceButtons.clear();
    return {};
}

SFMLPlayer::SFMLPlayer(const std::shared_ptr<Game> &game) {
    this->game = game;
    this->win = new GameWindow("Can't stop by Marvin G. and Johannes A.", 1000, 800, false);

    this->btnSkip = new Button("Skip");
    btnSkip->setBgColor(sf::Color::Black)
            .setPosition(0, 40);

    SubCanvas &root = win->getRootCanvas();
    root.addRenderable(new GameBackground());
    SubCanvas &control = root.newSubCanvas((Game::COLUMNS_AMOUNT + 1.5) * RenderableBoardColumn::COL_WIDTH * 1.1, 0);
    control.addRenderable(new OnTurnDisplay(game, this));
    control.addRenderable(btnSkip);
    int maxHeight = -1;
    auto collumns = game->getColumnsCopy();
    float fheight = RenderableBoardColumn::FIELD_HEIGHT;
    for (auto &col: collumns) {
        if (col.height > maxHeight)maxHeight = col.height;
    }

    SubCanvas &dices = control.newSubCanvas(0, 100);
    dices.addRenderable(new LambdaRenderable([this](SubCanvas &canv, GameWindow &win) {
        int i = 0;
        for (auto &dice: currentDices) {
            auto subcanv = canv.disconnectedSubCanvas(DICE_SIZE * i * 1.2, 0);
            dice.render(subcanv, win);
            i++;
        }
    }));


    SubCanvas &diceBtns = dices.newSubCanvas(0, 200);
    diceBtns.addRenderable(new LambdaRenderable([this](SubCanvas &canv, GameWindow &win) {
        for (auto &btn: this->chooseDiceButtons)btn.first.render(canv, win);
    }));

    SubCanvas &board = root.newSubCanvas(50, win->getWindow()->getSize().y / 2 - fheight * maxHeight / 2);

    for (int i = 0; i < game->COLUMNS_AMOUNT; i++) {
        auto &col = collumns[i];

        float y = maxHeight * fheight / 2 - col.height * fheight / 2;
        SubCanvas &colcanvas = board.newSubCanvas(i * RenderableBoardColumn::COL_WIDTH * 1.1, y);
        colcanvas.addRenderable(new RenderableBoardColumn(game, i));
    }


}

void SFMLPlayer::start() {
    this->win->startRenderingLoop();
}

SFMLPlayer::~SFMLPlayer() {
    this->win->getWindow()->close();
    delete this->win;
}
