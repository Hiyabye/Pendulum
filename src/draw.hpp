#ifndef __DRAW_HPP__
#define __DRAW_HPP__

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Vertex struct
typedef struct vertex {
  float x, y, z;
} vertex;

vertex convertCoord(int x, int y);
void drawTriangle(vertex v1, vertex v2, vertex v3);
void drawCircle(vertex c, int radius);
void drawLine(vertex v1, vertex v2);

#endif