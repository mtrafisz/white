#include "white.hpp"

whiteMultiplierBar::whiteMultiplierBar(const Vector2& position, float width, float height) {
    this->position = position;
    this->width = width;
    this->height = height;
}

void whiteMultiplierBar::update(float multiplier) {
    val = multiplier;
}

void whiteMultiplierBar::draw() {
    // background rect:
    DrawRectangle(position.x, position.y, width, height, kColors[cMultiplierBarBackground]);

    // bar rect: FIXME: is a little funky when multiplier is to big
    Color tempColor = kColors[cMultiplierBarBar];
    if (val > maxVal) {
        float normalizedVal = (val - maxVal + 1.0f) / (maxVal);
        tempColor = colorLerp(tempColor, BLUE, normalizedVal);
        DrawRectangleV(position, { width, height }, tempColor);
    } else {
        DrawRectangleV(position, { width * (val - minVal) / (maxVal - minVal), height }, tempColor);
    }
}

void whiteMultiplierBar::reset() {
    val = 0.0f;
}
