#include <raylib.h>
#include <stddef.h>
#include "nob.h"

const float camera_speed = 10;
const float zoom_speed = 10;

#define ARRAY(TYPE) struct { \
    TYPE *items; \
    size_t count, capacity; \
}

typedef struct {
    Model *model;
    Vector3 position;
} Entity;

typedef ARRAY(Entity) Entities;

int main(void)
{
    InitWindow(800, 600, "Plane");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    Camera3D camera = {
        .position = (Vector3) { 0.0f, 100.0f, 100.0f },
        .target = (Vector3) { 0.0f, 0.0f, 0.0f },
        .up = (Vector3) { 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE,
    };

    Vector3 zero = { 0.0f, 0.0f, 0.0f };
    Model tree_model = LoadModel("assets/tree/o2100.obj");

    Entities entities = {0};
    Entity first_tree = {
        .model = &tree_model,
        .position.z = 3.0f,
    };
    nob_da_append(&entities, first_tree);

    while (!WindowShouldClose()) {
        float dt = 1. / 60;

        Vector3 movement = {
            .x = (float)(IsKeyDown(KEY_W) - IsKeyDown(KEY_S)),
            .y = (float)(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)),
        };

        movement.x *= camera_speed * dt;
        movement.y *= camera_speed * dt;

        UpdateCameraPro(&camera, movement, zero, -GetMouseWheelMove() * zoom_speed);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Ray ray = GetScreenToWorldRay(GetMousePosition(), camera);
            float k = -ray.position.y/ray.direction.y;
            Entity tree = {
                .model = &tree_model,
                .position.x = ray.position.x + k * ray.direction.x,
                .position.z = ray.position.z + k * ray.direction.z,
            };
            nob_da_append(&entities, tree);
        }

        BeginDrawing();
            ClearBackground(DARKGRAY);
            BeginMode3D(camera);
                DrawGrid(100, 1.0f);
                nob_da_foreach(Entity, e, &entities) {
                    DrawModel(*e->model, e->position, 1.0f, WHITE);
                }
            EndMode3D();
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
