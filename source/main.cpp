#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <math.h>

#include "Window.h"
#include "Object.h"



glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

float deltaTime = 0.0f;    // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
    
float lastX = 400;
float lastY = 300;

bool firstMouse = true;

Camera camera = Camera();

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
      {
          lastX = xpos;
          lastY = ypos;
          firstMouse = false;
      }

      float xoffset = xpos - lastX;
      float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

      lastX = xpos;
      lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

bool SetupGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD/n";
        return false;
    }

    return true;
}


int main() {
    Window window = Window();
    window.SetCurrentCamera(&camera);
    glfwSetCursorPosCallback(window.Get(), mouse_callback);

    SetupGLAD();
    
    Object obj = Object();
    
    while (!glfwWindowShouldClose(window.Get()))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        window.Update(deltaTime);
        
        

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        obj.Render(camera);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window.Get());
        glfwPollEvents();
    }


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    return 0;
}
