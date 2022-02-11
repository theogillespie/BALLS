#pragma once


#include "../core/core.h"

namespace Raylib {
#ifdef _WIN32
	#include "raylib.h"
	#include "rlgl.h"
#else // linux support
#include "../raylib/src/raylib.h"
#endif
}

#define FPS 30
#define WIDTH 800   
#define HEIGHT 450

class GraphicsDrawer {
public:
	virtual void draw3d();
	virtual void draw2d();
	virtual void end();
};

class Graphics {

	Raylib::Camera3D camera;

	Vector3 basePosition = Vector3::zero();

public:

	Graphics() {};
	~Graphics() {};

	vector<GraphicsDrawer> drawers;

	void init(int width = WIDTH, int height = HEIGHT) {
		Raylib::InitWindow(width, height, "window");

		this->camera = { 0 };
		this->camera.position = { 0, 10, 0 };
		this->camera.target = { 0.0f, 0.0f, 0.0f };
		this->camera.up = { 0.0f, 1.0f, 0.0f };
		this->camera.fovy = 45.0f;                                // Camera field-of-view Y
		this->camera.projection = Raylib::CAMERA_PERSPECTIVE;
		Raylib::SetCameraMode(this->camera, Raylib::CAMERA_FREE);

		Raylib::SetTargetFPS(FPS);
	};


	void addDrawer(GraphicsDrawer drawer) {
		this->drawers.push_back(drawer);
	}


	void draw() {
		if (Raylib::WindowShouldClose()) {
			Raylib::CloseWindow();
			exit(1);
		}

		Raylib::UpdateCamera(&this->camera);
		Raylib::BeginDrawing();
		Raylib::ClearBackground(Raylib::RAYWHITE);

		Raylib::BeginMode3D(this->camera);
		/*
		for (int i = 0; i < this->drawers.size(); i++) {
			this->drawers[i].draw3d();
			this->drawers[i].draw2d();
		}*/
		Raylib::Vector3 position = { 0, 0, 0 };
		Raylib::DrawCube(position, 1.0f, 1.0f, 1.0f, Raylib::GRAY);
		Raylib::DrawCubeWires(position, 1.0f, 1.0f, 1.0f, Raylib::BLACK);
		Raylib::DrawGrid(5, 1.0f);

		Raylib::EndMode3D();
		Raylib::EndDrawing();
	}
};


class ProjectileVisualizer: GraphicsDrawer {
public:
	Projectile* projectile;

	ProjectileVisualizer(Projectile* proj) {
		this->projectile = proj;
	};

	void draw3d() override {
		Raylib::Vector3 position = { 0, 0, 0 };
		Raylib::DrawCube(position, 1.0f, 1.0f, 1.0f, Raylib::GRAY);
		Raylib::DrawCubeWires(position, 1.0f, 1.0f, 1.0f, Raylib::BLACK);
		Raylib::DrawGrid(5, 1.0f);
	};

	void draw2d() override {

	};
};
