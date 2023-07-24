#pragma once

#include "color.hpp"
#include <array>

const float kScale = 1.0f;
const uint8_t kTileResolution = 4;
const uint8_t toClick = kTileResolution - 1;    // Chosen randomly, might change later

const unsigned kTileBorder = (unsigned)((float) 4 * kScale),
               kTileDimensions = (unsigned)((float) 100 * kScale),
               kWindowBorder = (unsigned)((float) 20 * kScale),
               kWindowDimensions = kWindowBorder * 2 + kTileDimensions * kTileResolution + kTileBorder * (kTileResolution - 1);

class whiteTile {
private:
    Vector2 position = { 0.0f, 0.0f };

    bool highlighted = false;
    float highlightTimer = 0.0f;
    const float kHighlightDuration = 0.2f;

    bool disabled = true;

public:
    whiteTile() = default;
    whiteTile(const Vector2& position);

    void highlight();
    bool isHighlighted() const;

    bool isClicked() const;

    void update();
    void draw();

    void reset();

    bool isEnabled() const;
    void enable();
    void disable();

    whiteTile operator=(const whiteTile& other) {
        position = other.position;
        highlighted = other.highlighted;
        highlightTimer = other.highlightTimer;
        return *this;
    }
};

class white {
private:
    whiteTile tiles[kTileResolution * kTileResolution];

    void update(int i);
    void draw(int i);
    void setRandomTileEnabled();

    int score = 0;

    int goal = 25;
    float timeToGoalIncrement = 5.0f;
    
public:
    white();
    
    void loop();

    void clickInput();

    void reset();

    int getScore() const;
};
