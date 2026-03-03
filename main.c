#include <raylib.h>
#include <stdio.h>

const float camera_speed = 10;
const float zoom_speed = 10;

int main(void)
{
    InitWindow(800, 600, "Plane");

    Camera3D camera = {
        .position = (Vector3) { 0.0f, 100.0f, 100.0f },
        .target = (Vector3) { 0.0f, 0.0f, 0.0f },
        .up = (Vector3) { 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE,
    };

    Vector3 zero = { 0.0f, 0.0f, 0.0f };

    Model tree = LoadModel("assets/tree/o2100.obj");
    Vector3 tree_position = { 0.0f, 0.0f, 3.0f };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = 1. / 60;

        Vector3 movement = {
            .x = (float)(IsKeyDown(KEY_W) - IsKeyDown(KEY_S)),
            .y = (float)(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)),
        };

        movement.x *= camera_speed * dt;
        movement.y *= camera_speed * dt;

        UpdateCameraPro(&camera, movement, zero, -GetMouseWheelMove() * zoom_speed);

        BeginDrawing();
            ClearBackground(DARKGRAY);
            BeginMode3D(camera);
                DrawModel(tree, tree_position, 1.0f, WHITE);
                DrawCube(zero, 1, 1, 1, WHITE);
                DrawCubeWires(zero, 1, 1, 1, BLACK);
                DrawGrid(10, 1.0f);
            EndMode3D();
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
