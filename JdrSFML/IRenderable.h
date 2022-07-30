#pragma once


class GameWindow;
class SubCanvas;

class IRenderable {
protected:
    int zIndex;
public:

    explicit IRenderable(int zIndex);
    IRenderable();

    int getZIndex();

    virtual void render(SubCanvas& canvas,GameWindow& gameWindow) = 0;
    virtual ~IRenderable() = default;
};