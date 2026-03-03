#include <raylib.h>

const int camera_speed = 10;

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

        float scroll = GetMouseWheelMove();
        if (scroll) {
            float scroll_k = scroll > 0 ? 2 : .5;
            camera.position.y *= scroll_k;
            camera.position.z *= scroll_k;
        }

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
