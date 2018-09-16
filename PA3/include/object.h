#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
#include <SDL.h>

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt, int direction);
    void Render();
		void Scale();

    glm::mat4 GetModel();

    glm::mat4 model;
    glm::mat4 translate;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float angle;
    SDL_Event event;
};

#endif /* OBJECT_H */
