#pragma once

#include <cstddef>
#define FPS 30
#define WIDTH 800   
#define HEIGHT 450

#include "../core/core.h"
#include "../io/io.h"

#include <GLFW/glfw3.h>

#ifdef _WIN32

#else
#include "../draw/debug_draw.hpp"

#endif

#define DEBUG_DRAW_IMPLEMENTATION
using namespace dd;


class GL {
    public:
        GLFWwindow* window;

        GL() {};

        void init() {
            if (!glfwInit()) {
                Console::error("Failed to initalize graphics (fatal)");
                exit(3);
            }
            this->window = glfwCreateWindow(WIDTH, HEIGHT, "BALListic Simulator", NULL, NULL);
            if (!window)
            {
                glfwTerminate();
                Console::error("Failed to initalize window (fatal)");
                exit(3);
            }
            glfwMakeContextCurrent(window);
            Console::print("Done!");

            glfwTerminate();
        };

        //draws a singular frame
        void draw() {

            glClear(GL_COLOR_BUFFER_BIT);
            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            /* Poll for and process events */
            glfwPollEvents();
        };

        void end() {
            glfwTerminate();
        };
};

class DebugRenderInterface : RenderInterface {
public:
    GL* graphics;
    DebugRenderInterface() {
        this->graphics = new GL();
    }

    void beginDraw() override {
        this->graphics->init();
    };

    void endDraw() override {
        this->graphics->end();
    };

    void drawPointList(const DrawVertex * points, int count, bool depthEnabled) override {
        if(points == nullptr && count <= 0 && count > DEBUG_DRAW_VERTEX_BUFFER_SIZE) {
            return;
        }
        

    };
    void drawLineList(const DrawVertex * lines, int count, bool depthEnabled) override;
};