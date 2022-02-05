#pragma once


#include "../core/core.h"

#ifdef _WIN32
namespace Raylib {
	#include "raylib.h"
}
#else // linux support
#endif

#define FPS 30
#define WIDTH 800   
#define HEIGHT 450

class Graphics {

	Raylib::Camera3D camera;

	Vector3 basePosition = Vector3::zero();

public:
	Graphics() {};
	~Graphics() {};

	void init(int width = WIDTH, int height = HEIGHT) {
		Raylib::InitWindow(width, height, "window");

		this->camera = { 0 };
		this->camera.position = (Raylib::Vector3){ 10.0f, 10.0f, 10.0f };
		this->camera.target = (Raylib::Vector3){ 0.0f, 0.0f, 0.0f };
		this->camera.up = (Raylib::Vector3){ 0.0f, 1.0f, 0.0f };
		this->camera.fovy = 45.0f;                                // Camera field-of-view Y
		this->camera.projection = Raylib::CAMERA_PERSPECTIVE;
		Raylib::SetCameraMode(this->camera, Raylib::CAMERA_FREE);

		Raylib::SetTargetFPS(FPS);
	};


	void draw() {
		if (Raylib::WindowShouldClose()) {
			Raylib::CloseWindow();
			exit(1);
		}

		Raylib::UpdateCamera(&this->camera);
		Raylib::BeginDrawing();

		Raylib::ClearBackground(Raylib::RAYWHITE);

		Raylib::BeginMode3D(this->camera);


		Raylib::Vector3 position = (Raylib::Vector3){ this->basePosition.x, this->basePosition.y, this->basePosition.z };
		Raylib::DrawCube(position, 1.0f, 1.0f, 1.0f, Raylib::GRAY);
		Raylib::DrawCubeWires(position, 1.0f, 1.0f, 1.0f, Raylib::BLACK);

		Raylib::DrawGrid(5, 1.0f);

		Raylib::EndMode3D();

		Raylib::EndDrawing();
	}
};
