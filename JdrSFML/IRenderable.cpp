#include "IRenderable.h"
IRenderable::IRenderable(int zIndex): zIndex(zIndex) {}

IRenderable::IRenderable(): zIndex(0) {}

int IRenderable::getZIndex() {
    return this->zIndex;
}
