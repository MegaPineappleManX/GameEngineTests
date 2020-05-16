#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>


#include <math.h>

#include "Window.h"
#include "Object.h"

float deltaTime = 0.0f;    // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
    
float lastX = 400;
float lastY = 300;

bool firstMouse = true;

Camera camera = Camera();

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
      {
          lastX = (float)xpos;
          lastY = (float)ypos;
          firstMouse = false;
      }

	  float xoffset = (float)xpos - lastX;
	  float yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top

      lastX = (float)xpos;
      lastY = (float)ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

int main() {
    Window window = Window();
    window.SetCurrentCamera(&camera);
    glfwSetCursorPosCallback(window.Get(), mouse_callback);

    
    Object obj = Object("basicLitFragmentShader.frag");
    Object light = Object("lightFragmentShader.frag");
    
    light.SetPosition(glm::vec3(2.0f, 2.0f, -5.0f));
    light.SetScale(glm::vec3(0.25f, 0.25f, 0.25f));
    
    obj.GetShader()->use();
    glm::vec3 objColor = glm::vec3(1.5f, 0.5f, 0.5f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    obj.GetShader()->setVec3("objectColor", objColor);
    obj.GetShader()->setVec3("lightColor", lightColor);
    obj.GetShader()->setVec3("lightPos", light.GetPosition());




    while (!glfwWindowShouldClose(window.Get()))
    {
        double currentFrame = glfwGetTime();
        deltaTime = (float)currentFrame - lastFrame;
        lastFrame = (float)currentFrame;
        
        window.Update(deltaTime);
        
        obj.Render(camera);
        light.Render(camera);
        
		window.LateUpdate(deltaTime);

        glfwSwapBuffers(window.Get());
        glfwPollEvents();
    }

    return 0;
}
