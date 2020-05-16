#pragma once
struct GLFWwindow;
class Camera;

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void MouseCallback(GLFWwindow* window, double xpos, double ypos);
class Window {
public:
    Window();
    ~Window();
    
	void Update(float dt);
	void LateUpdate(float dt);
    
    GLFWwindow* Get() { return window; }
    
    int GetHeight() const { return height; }
    int GetWidth() const { return width; }
    
    void SetCurrentCamera (Camera* cam) { camera = cam; };
    
private:
    void ProcessInput();
    
    GLFWwindow* window = nullptr;
    Camera* camera = nullptr;
    
    float deltaTime = 0.0f;
    unsigned int width = 800;
    unsigned int height = 600;
    
    //float lastX = 800 / 2.0f;
    //float lastY = 600 / 2.0f;
  
    //bool firstMouse = true;


};





