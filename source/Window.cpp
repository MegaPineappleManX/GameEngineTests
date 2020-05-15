#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>

#include "Camera.h"
#include "Window.h"

Window::Window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Pine2D", NULL, NULL);
    
    if (window == NULL) {
        std::cout << "Failed to create GLFW window/n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // TODO figure out if I can set these to be non-static
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    
}

void FrameBufferSizeCallback(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, w, h);
}

void Window::ProcessInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
}

Window::~Window () {
    glfwTerminate();
}
