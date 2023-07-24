#pragma once

#include "raylib.h"
#include <cstdint>
#include <vector>

inline uint8_t lerpf(uint8_t a, uint8_t b, float t) {
    return (uint8_t)(a + (b - a) * t);
}

inline Color colorFromHex(uint32_t hex) {
    return {
        static_cast<unsigned char>((hex >> 24) & 0xff),
        static_cast<unsigned char>((hex >> 16) & 0xff),
        static_cast<unsigned char>((hex >> 8)  & 0xff),
        static_cast<unsigned char>((hex >> 0)  & 0xff),
    };
}

inline Color colorLerp(Color a, Color b, float t) {
    return {
        (uint8_t)lerpf(a.r, b.r, t),
        (uint8_t)lerpf(a.g, b.g, t),
        (uint8_t)lerpf(a.b, b.b, t),
        (uint8_t)lerpf(a.a, b.a, t)
    };
}

const Color kColors[] = {
    /* clickable tiles */
    colorFromHex(0x011627ff),
    /* "white" tiles */
    colorFromHex(0xFDFFFC99),
    /* background color */
    colorFromHex(0x2EC4B6ff),
    /* score text color */
    colorFromHex(0xE71D36ff)
};

enum kColorIndex {
    cTiles,
    cDisabledTiles,
    cBackground,
    cScoreText
};
