#pragma once
#include <array>

const float textureWidth = 0.01f;
const float textureHeight = 0.125f;
const int maxCol = 72;
const int maxRow = 8;

struct UV {
    float u, v;
};

inline std::array<UV, 4> getTileUVs(int col, int row) {
    if (col > maxCol || row > 8 || col < 1 || row < 1)
    {
        LOG_WARN("Texture BitMap Position out of range! COL: {0}, ROW: {1}",col,row);
    }
    float u_min = textureWidth * col - textureWidth;
    float u_max = textureWidth * col;
    float v_min = (1 - textureHeight * row);
    float v_max = (1 - textureHeight * row) + textureHeight;

    return {
        UV{u_max, v_max}, // top-right
        UV{u_max, v_min}, // bottom-right
        UV{u_min, v_min}, // bottom-left
        UV{u_min, v_max}  // top-left
    };
}