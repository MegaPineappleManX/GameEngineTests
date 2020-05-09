#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

#include <math.h>

#include "Shader.h"
    
// GLFW Callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// GLFW init

GLFWwindow* SetupGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Pine2D", NULL, NULL);
    
    if (window == NULL) {
        std::cout << "Failed to create GLFW window/n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

bool SetupGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD/n";
        return false;
    }

    return true;
}


int main() {
    
    std::ifstream file;
    file.open("Main.cpp");
    std::string line;
    std::getline(file, line);
    std::cout << line << std::endl;
    GLFWwindow* window = SetupGLFW();
    SetupGLAD();
    
    Shader ourShader("../../source/basicVertexShader.vert", "../../source/basicFragmentShader.frag");

    float vertices[] = {
     // positions               // colors
    -0.5f, -0.5f,  0.0f,        1.0f, 0.0f, 0.0f,   // bottom right
     0.5f, -0.5f,  0.0f,        0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f,  0.0f,        0.0f, 0.0f, 1.0f    // top
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        ProcessInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        ourShader.use();
        
        float timeValue = glfwGetTime();
        //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        float offset = (sin(timeValue) / 2.0f);
        ourShader.setFloat("xOffset", offset);
        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glfwPollEvents();
        glfwSwapBuffers(window);

    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
