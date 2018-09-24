#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
#include<fstream>

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt);
    void Render();
		bool loadOBJ(std::string objF,std::string mtlF);
    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    glm::mat4 translate;
		// Can use struct of vertices and indices to load multiple object types
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float angle;
};

#endif /* OBJECT_H */
