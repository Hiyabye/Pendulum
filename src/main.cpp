#include "shader.hpp"
#include "draw.hpp"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Pendulum class
class Pendulum {
public:
  vertex center;
  vertex start;
  float length;
  float angle;
  float velocity;
  float acceleration;
  float gravity;
  float damping;

  Pendulum() {
    center = {400.0, 300.0, 0.0};
    start = {400.0, 600.0, 0.0};
    length = 250.0;
    angle = M_PI_4;
    velocity = 0.0;
    acceleration = 0.0;
    gravity = 0.4;
    damping = 0.998;
  }

  void update() {
    acceleration = (-gravity / length) * sin(angle);
    velocity += acceleration;
    velocity *= damping;
    angle += velocity;
    center.x = start.x - length * sin(angle);
    center.y = start.y - length * cos(angle);
  }
};

// Resize window
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

// Close window when ESC is pressed
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

// Main function
int main(void) {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // Create a window
  GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pendulum", NULL, NULL);
  if (!window) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);

  // Create a shader
  Shader shader("vertex.glsl", "fragment.glsl");

  // Set up pendulum
  Pendulum p1;

  // Prepare FPS counter
  double previousSeconds = glfwGetTime();
  int frameCount = 0;

  // Render loop
  while(!glfwWindowShouldClose(window)) {
    // Clear screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Update and draw pendulum
    p1.update();
    glUseProgram(shader.ID);
    drawLine(p1.start, p1.center);
    drawCircle(p1.center, 30);
    
    // Calculate FPS
    double elapsedSeconds = glfwGetTime();
    double elapsedSecondsSinceLastUpdate = elapsedSeconds - previousSeconds;
    if (elapsedSecondsSinceLastUpdate > 0.25) {
      previousSeconds = elapsedSeconds;
      double fps = (double)frameCount / elapsedSecondsSinceLastUpdate;
      char tmp[128];
      snprintf(tmp, sizeof(tmp), "Pendulum @ fps: %.2f", fps);
      glfwSetWindowTitle(window, tmp);
      frameCount = 0;
    }
    frameCount++;

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}