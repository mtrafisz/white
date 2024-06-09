#include "white.hpp"
#include <math.h>

whiteTile::whiteTile(const Vector2& position) : position(position) {}

void whiteTile::highlight() {
    highlighted = true;
    highlightTimer = kHighlightDuration;
}

bool whiteTile::isHighlighted() const {
    return highlighted;
}

bool whiteTile::isClicked() const {
    return (CheckCollisionPointRec(GetMousePosition(), { position.x, position.y, (float)kTileDimensions, (float)kTileDimensions }));
}

void whiteTile::update() {
    if (highlighted) {
        highlightTimer -= GetFrameTime();
        if (highlightTimer <= 0.0f) {
            highlighted = false;
        }
    }
}

void whiteTile::draw() {
    Color tempColor = kColors[disabled ? cDisabledTiles : cTiles];

    if (highlighted) tempColor = colorLerp(tempColor, kColors[cTiles], 1.0f - powf(1.0f - highlightTimer / kHighlightDuration, 2.0f));

    DrawRectangle(position.x, position.y, kTileDimensions, kTileDimensions, tempColor);
}

void whiteTile::reset() {
    disabled = true;
    highlighted = false;
    highlightTimer = 0.0f;
}

bool whiteTile::isEnabled() const {
    return !disabled;
}

void whiteTile::enable() {
    disabled = false;
}

void whiteTile::disable() {
    disabled = true;
}
