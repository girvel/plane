#include <raylib.h>

const int camera_speed = 10;

int main(void)
{
    InitWindow(800, 600, "Plane");

    Camera3D camera = {0};
    camera.position = (Vector3) { 0.0f, 10.0f, 10.0f };
    camera.target = (Vector3) { 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3) { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 zero = { 0.0f, 0.0f, 0.0f };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = 1. / GetFPS();

        if (IsKeyDown(KEY_W)) {
            camera.position.z += -camera_speed * dt;
            camera.target.z += -camera_speed * dt;
        }

        if (IsKeyDown(KEY_S)) {
            camera.position.z += camera_speed * dt;
            camera.target.z += camera_speed * dt;
        }

        if (IsKeyDown(KEY_A)) {
            camera.position.x += -camera_speed * dt;
            camera.target.x += -camera_speed * dt;
        }

        if (IsKeyDown(KEY_D)) {
            camera.position.x += camera_speed * dt;
            camera.target.x += camera_speed * dt;
        }

        BeginDrawing();
            ClearBackground(DARKGRAY);
            BeginMode3D(camera);
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
