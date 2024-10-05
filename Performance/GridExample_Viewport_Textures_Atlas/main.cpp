#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include <vector>

Texture2D Atlas = { 0 };
std::vector<Rectangle> GridColors;

constexpr size_t MapHeight = 1000;
constexpr size_t MapWidth = 1000;
constexpr float GridSize = 16;

std::vector<int> MapGrid;

Camera2D View = { 0 };

Rectangle* GetMapValue(size_t x, size_t y)
{
    if (x < 0 || x >= MapWidth || y < 0 || y >= MapHeight)
        return nullptr;

    return &GridColors[MapGrid[y * MapWidth + x]];
}

int GetRandomColor()
{
    return GetRandomValue(0, GridColors.size() - 1);
}

void GameInit()
{
    Atlas = LoadTexture("resources/1.png");

    GridColors.push_back(Rectangle{ 0 * 128, 0, 128, 128 });
    GridColors.push_back(Rectangle{ 1 * 128, 0, 128, 128 });
    GridColors.push_back(Rectangle{ 2 * 128, 0, 128, 128 });
    GridColors.push_back(Rectangle{ 3 * 128, 0, 128, 128 });
    GridColors.push_back(Rectangle{ 4 * 128, 0, 128, 128 });
    GridColors.push_back(Rectangle{ 5 * 128, 0, 128, 128 });
    GridColors.push_back(Rectangle{ 6 * 128, 0, 128, 128 });
    GridColors.push_back(Rectangle{ 7 * 128, 0, 128, 128 });
    GridColors.push_back(Rectangle{ 8 * 128, 0, 128, 128 });

    MapGrid.resize(MapHeight * MapWidth);

    for (auto& grid : MapGrid)
        grid = GetRandomColor();

    View.zoom = 1;
}

void GameClose()
{
    UnloadTexture(Atlas);
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

    Vector2 windowStart = GetScreenToWorld2D(Vector2{ 0,0 }, View);
    Vector2 windowEnd = GetScreenToWorld2D(Vector2{ float(GetScreenWidth()), float(GetScreenHeight())}, View);

    BeginMode2D(View);

    for (auto y = int(windowStart.y/GridSize); y < int(windowEnd.y / GridSize) + 1; y++)
    {
        for (auto x = int(windowStart.x / GridSize); x < int(windowEnd.x / GridSize)+1; x++)
        {
            Rectangle* texture = GetMapValue(x, y);
            if (!texture)
                continue;

            DrawTexturePro(Atlas, *texture, Rectangle{x * GridSize, y * GridSize, GridSize, GridSize}, Vector2Zero(), 0, WHITE);
        }
    }

    EndMode2D();
    DrawRectangle(0, GetScreenHeight() - 25, 100, 25, BLACK);
    DrawFPS(0, GetScreenHeight() - 20);
    EndDrawing();
}

int main()
{
   // SetConfigFlags(FLAG_WINDOW_HIGHDPI);
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