#include "GameWindow.h"
#include "SubCanvas/SubCanvas.h"
//Static inits
sf::Font GameWindow::fontDefault = [] {
    sf::Font font;
    font.loadFromFile("../JdrSFML/assets/jai.TTF");
    return font;
}();

GameWindow::GameWindow(const std::string& name, int width, int height,bool resizable) {
    int style = sf::Style::Titlebar|sf::Style::Close;
    if(resizable){
        style |= sf::Style::Resize;
    }

    this->window = new sf::RenderWindow(sf::VideoMode(width,height),name,style);
    this->rootCanvas = new SubCanvas(0,0,this->window);
}

GameWindow::~GameWindow() {
    delete this->rootCanvas;
    delete this->window;
}


sf::Font const& GameWindow::getDefaultFont()  {
    return GameWindow::fontDefault;
}


void GameWindow::update(){
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
            std::exit(0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window->close();
            std::exit(0);
        }
    }

}
void GameWindow::startRenderingLoop(){
    while(this->window->isOpen()){
        this->update();
        this->render();
    }
}



void GameWindow::render() {
    window->clear(sf::Color(255,255,255,255));
    this->rootCanvas->renderOnSFML(*this->window,*this);
    window->display();
}

sf::RenderWindow *GameWindow::getWindow() const {
    return window;
}

SubCanvas& GameWindow::getRootCanvas() {
    return *this->rootCanvas;
}
