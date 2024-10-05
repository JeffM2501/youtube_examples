#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include <vector>


Camera View = { 0 };

std::vector<Vector3> Spheres;

Mesh SphereMesh = { 0 };
Material SphereMaterial;

void GameInit()
{
    rlSetClipPlanes(0.1, 3000);

    View.fovy = 45;
    View.up.y = 1;
    View.position.z = -800;
    View.position.y = 800;

    SphereMesh = GenMeshSphere(5, 16, 16);
    SphereMaterial = LoadMaterialDefault();
    SphereMaterial.maps[MATERIAL_MAP_ALBEDO].color = RED;

    int range = 500;

    for (int i = 0; i < 500; i++)
    {
        Spheres.push_back(Vector3{ float(GetRandomValue(-range,range)),float(GetRandomValue(-range,range)),float(GetRandomValue(-range,range)) });
    }
}

void GameClose()
{
    UnloadMesh(SphereMesh);
}

bool GameUpdate()
{
    UpdateCamera(&View, CAMERA_ORBITAL);

    return true;
}

void GameDraw()
{
    BeginDrawing();
    ClearBackground(DARKGRAY);

    BeginMode3D(View);
    DrawGrid(1000, 25);

    for (auto& sphere : Spheres)
        DrawMesh(SphereMesh, SphereMaterial, MatrixTranslate(sphere.x, sphere.y, sphere.z));

    EndMode3D();

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