#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "SubCanvas/SubCanvas.h"

class GameWindow {
private:
    static sf::Font fontDefault;
    //Member
    sf::RenderWindow* window;
    SubCanvas* rootCanvas;
public:
    sf::RenderWindow *getWindow() const;


    static sf::Font const& getDefaultFont();
    //Member

    void render();
    void startRenderingLoop();
    SubCanvas& getRootCanvas();
    GameWindow(const std::string& name, int width, int height, bool resizable);
    ~GameWindow();


protected:
    void update();


};


