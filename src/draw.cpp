#include "draw.hpp"

// Convert screen coordinates to OpenGL coordinates
vertex convertCoord(int x, int y) {
  vertex v = {(float)x/SCREEN_WIDTH*2-1, (float)y/SCREEN_HEIGHT*2-1, 0.0};
  return v;
}

// Draw a circle
void drawCircle(vertex c, int radius) {
  float vertices[360*3];
  for (int i=0; i<360; i++) {
    vertex v = convertCoord(c.x+radius*cos(i*M_PI/180), c.y+radius*sin(i*M_PI/180));
    vertices[i*3] = v.x;
    vertices[i*3+1] = v.y;
    vertices[i*3+2] = v.z;
  }
  unsigned int VBO, VAO;
  
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 360);
}

// Draw a line
void drawLine(vertex a, vertex b) {
  vertex v1 = convertCoord(a.x, a.y);
  vertex v2 = convertCoord(b.x, b.y);
  float vertices[] = {
    v1.x, v1.y, v1.z,
    v2.x, v2.y, v2.z
  };
  unsigned int VBO, VAO;
  
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glDrawArrays(GL_LINES, 0, 2);
}