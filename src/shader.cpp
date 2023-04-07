#include "shader.hpp"

Shader createShader(const char* vertexPath, const char* fragmentPath) {
  Shader shader(vertexPath, fragmentPath);
  return shader;
}