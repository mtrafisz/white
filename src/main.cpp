#include "white.hpp"
#include "color.hpp"

// osu gaming
const int MouseClickButtons[] = {
    MOUSE_LEFT_BUTTON,
    MOUSE_RIGHT_BUTTON,
};

const int keyboardClickButtons[] = {
    KEY_Z,
    KEY_X
};

int main() {
    // init
    InitWindow(kWindowDimensions, kWindowDimensions, "White");
    InitAudioDevice();
    SetTargetFPS(30);

    white game;
    char scoreText[32];

    Sound clickSound = LoadSound("../../assets/click.wav"); // assuming it's played directly from build folder
    // TODO: add multiple click sounds, move this out of main.cpp

    while (!WindowShouldClose()) {
        // input
        for (int i = 0; i < 2; i++) {
            if (IsMouseButtonPressed(MouseClickButtons[i])) {
                game.clickInput();
                PlaySound(clickSound);
            }
        }
        for (int i = 0; i < 2; i++) {
            if (IsKeyPressed(keyboardClickButtons[i])) {
                game.clickInput();
                PlaySound(clickSound);
            }
        }
        if (IsKeyPressed(KEY_R)) {
            game.reset();
        }

        // draw & update
        BeginDrawing();

            ClearBackground(kColors[cBackground]);
            game.loop();

        EndDrawing();
    }

    // cleanup
    UnloadSound(clickSound);

    CloseWindow();
    CloseAudioDevice();
    return 0;
}