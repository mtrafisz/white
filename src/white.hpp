#pragma once

#include "color.hpp"
#include <array>

const float kScale = 1.4f;
const uint8_t kTileResolution = 4;  // x * x tiles
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

class whiteMultiplierBar {
private:
    Vector2 position = { 0.0f, 0.0f };
    float width = 0.0f;
    float height = 0.0f;

    const float maxVal = 2.0f;
    const float minVal = 1.0f;

    float val = 0.0f;

public:
    whiteMultiplierBar() = default;
    whiteMultiplierBar(const Vector2& position, float width, float height);

    void update(float multiplier);
    void draw();

    void reset();
};

class white {
private:
    whiteTile tiles[kTileResolution * kTileResolution];
    
    // bar on the bottom border:
    whiteMultiplierBar multiplierBar = whiteMultiplierBar({ (float) kWindowBorder + kTileBorder, (float) (kWindowBorder + kTileDimensions * kTileResolution + kTileBorder * kTileResolution) }, (float) (kTileDimensions * kTileResolution), (float) (kWindowBorder * 0.5f));

    void update(int i);
    void draw(int i);
    void setRandomTileEnabled();

    int score = 0;
    char scoreText[32];

    // goal stuff
    const int startGoal = 40;
    float startTimeToGoalIncrement = 10.0f;
    const float difficultyIncrement = 0.95f; 

    int goal = startGoal;
    float timeToGoalIncrement = startTimeToGoalIncrement;

    char goalText[32];
    char timeToGoalText[32];

    // multiplier stuff
    int ffloor(float f) const;

    float multiplier = 1.0f;
    const float dischargeRate = 0.2f;
    const float multiplierIncrement = dischargeRate / 3.9f;
    //const float multiplierIncrement = dischargeRate / 2.0f;
    
public:
    white();
    
    void loop();

    void clickInput();

    void reset();

};
