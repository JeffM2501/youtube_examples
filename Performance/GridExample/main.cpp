#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include <vector>

std::vector<Color> GridColors;

constexpr size_t MapHeight = 1000;
constexpr size_t MapWidth = 1000;
constexpr float GridSize = 64;

std::vector<Color> MapGrid;

Camera2D View = { 0 };

Color GetMapValue(size_t x, size_t y)
{
    return MapGrid[y * MapWidth + x];
}

Color GetRandomColor()
{
    return GridColors[GetRandomValue(0, GridColors.size() - 1)];
}

void GameInit()
{
    GridColors.push_back(DARKGRAY);
    GridColors.push_back(DARKBROWN);
    GridColors.push_back(DARKBLUE);
    GridColors.push_back(DARKGREEN);
    GridColors.push_back(DARKPURPLE);
    GridColors.push_back(GRAY);

    MapGrid.resize(MapHeight * MapWidth);

    for (auto& grid : MapGrid)
        grid = GetRandomColor();

    View.zoom = 1;
}

void GameClose()
{
}

bool GameUpdate()
{
    float speed = 500 * GetFrameTime();

    if (IsKeyDown(KEY_W))
        View.target.y -= speed;
    if (IsKeyDown(KEY_S))
        View.target.y += speed;

    if (IsKeyDown(KEY_A))
        View.target.x -= speed;
    if (IsKeyDown(KEY_D))
        View.target.x += speed;

    return true;
}

void GameDraw()
{
    BeginDrawing();
    ClearBackground(DARKGRAY);

    BeginMode2D(View);

    for (auto y = 0; y < MapHeight; y++)
    {
        for (auto x = 0; x < MapHeight; x++)
        {
            DrawRectangle(x * GridSize, y * GridSize, GridSize, GridSize, GetMapValue(x, y));
        }
    }

    EndMode2D();
    DrawRectangle(0, GetScreenHeight() - 25, 100, 25, BLACK);
    DrawFPS(0, GetScreenHeight() - 20);
    EndDrawing();
}

int main()
{
    InitWindow(1280, 800, "Video Example");

    GameInit();

    while (!WindowShouldClose())
    {
        if (!GameUpdate())
            break;

        GameDraw();
    }

    GameClose();

    CloseWindow();
    return 0;
}