#include "white.hpp"

white::white() {
    for (int i = 0; i < kTileResolution * kTileResolution; i++) {
        tiles[i] = whiteTile({ (float) (kWindowBorder + (i % kTileResolution) * (kTileDimensions + kTileBorder)), (float) (kWindowBorder + (i / kTileResolution) * (kTileDimensions + kTileBorder)) });
    }
    for (int i = 0; i < toClick; i++) {
        setRandomTileEnabled();
    }
}

void white::update(int i) {
    tiles[i].update();
}

void white::draw(int i) {
    tiles[i].draw();
}

void white::loop() {
    for (int i = 0; i < kTileResolution * kTileResolution; i++) {
        update(i);
        draw(i);
    }
}

void white::clickInput() {
    for (int i = 0; i < kTileResolution * kTileResolution; i++) {
        if (tiles[i].isClicked()) {
            if (tiles[i].isEnabled()) {
                tiles[i].disable();
                tiles[i].highlight();
                score++;
                setRandomTileEnabled();
            }
            else {
                reset(); //TODO: new game / game over / something
                // TODO: GameState enum?
            }
        }
    }
}

void white::setRandomTileEnabled() {
    int randomTile = GetRandomValue(0, kTileResolution * kTileResolution - 1);
    while (tiles[randomTile].isEnabled()) {
        randomTile = GetRandomValue(0, kTileResolution * kTileResolution - 1);
    }
    tiles[randomTile].enable();
}

void white::reset() {
    for (int i = 0; i < kTileResolution * kTileResolution; i++) {
        tiles[i].reset();
    }
    for (int i = 0; i < toClick; i++) {
        setRandomTileEnabled();
    }
    score = 0;
}

int white::getScore() const {
    return score;
}
