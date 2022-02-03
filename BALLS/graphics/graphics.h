#pragma once

#define FPS 30
#define WIDTH 800   
#define HEIGHT 450

#include "raylib.h"

class Graphics {
    public:
        Camera3D camera = {0};

        Graphics() {};

        void init() {
            InitWindow(WIDTH, HEIGHT, "BALListic Simulator");
            camera.position = (Vector3){0,0,0}
        }
}