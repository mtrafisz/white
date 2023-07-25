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
    // score
    sprintf(scoreText, " %d", score);
    DrawText(scoreText, kWindowDimensions / 2 - MeasureText(scoreText, 40) / 1.4f, kWindowBorder * 1.5f, 40, kColors[cScoreText]);
    // goal & timer (with description, aligned to the right)
    sprintf(scoreText, "Goal: %d", goal);
    DrawText(scoreText, kWindowDimensions - MeasureText(scoreText, 20) - kWindowBorder * 1.5f, kWindowBorder * 1.5f, 20, kColors[cScoreText]);
    sprintf(scoreText, "Time: %.1f", timeToGoalIncrement);
    DrawText(scoreText, kWindowDimensions - MeasureText(scoreText, 20) - kWindowBorder * 1.5f, kWindowBorder * 1.5f + 20, 20, kColors[cScoreText]);

}

void white::loop() {
    if (score >= goal) {
        goal += startGoal;
        startTimeToGoalIncrement *= difficultyIncrement;
        timeToGoalIncrement = startTimeToGoalIncrement;
    }

    timeToGoalIncrement -= GetFrameTime();
    if (timeToGoalIncrement <= 0.0f) {
        if (score < goal) {
            reset();    // TODO: new game / game over / something
        }
    }

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
    goal = startGoal;
    timeToGoalIncrement = startTimeToGoalIncrement;
}

int white::getScore() const {
    return score;
}
