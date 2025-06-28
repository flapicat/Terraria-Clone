#include "trpch.h"
#include "NoiseGeneration.h"

#include <ctime>

void GenertateTerrain(int mapWidth, int mapHeight, std::vector<std::string>& MapMatrix)
{
    MapMatrix.resize(mapHeight, std::string(mapWidth, 'A'));
    int baseGroundY = mapHeight * 2 / 3; // Flat base height

    //TERRAIN
    int randomSeed = rand();
    FastNoiseLite horizontNoise;
    horizontNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    horizontNoise.SetFrequency(0.01f);
    horizontNoise.SetSeed(randomSeed);

    int HorizontY;

    for (int x = 0; x < mapWidth; ++x) {
        float noiseValue = horizontNoise.GetNoise((float)x, 0.0f);
        int variation = static_cast<int>(noiseValue * 10); // Range: [-10, 10]
        int HorizontY = baseGroundY + variation;
        HorizontY = std::clamp(HorizontY, 0, mapHeight - 1);

        for (int y = 0; y <= HorizontY; ++y) {  // Invert Y: bottom is mapHeight - 1
            char& tile = MapMatrix[mapHeight - 1 - y][x];
            if (y == HorizontY)
            {
                tile = 'G';
            }
            if (y < HorizontY && HorizontY > HorizontY - 5)
            {
                tile = 'X';
            }
            if (y < HorizontY - 10)
            {
                tile = 'S';
            }
        }
    }

    ////CAVES
    randomSeed = rand();
    FastNoiseLite caveNoise;
    caveNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    caveNoise.SetFrequency(0.05f);
    caveNoise.SetSeed(randomSeed);

    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            char& tile = MapMatrix[mapHeight - 1 - y][x];
            if (tile == 'S' && y < baseGroundY - 50)
            {
                float caveValue = caveNoise.GetNoise((float)x, (float)y);

                if (caveValue > 0.8f) {
                    tile = 'A';
                }
            }
        }
    }

    //PRINT ALL MAP
    //for (size_t i = 0; i < mapHeight; i++)
    //{
    //    LOG_INFO("{0}{1}",i, MapMatrix[i]);
    //}
}