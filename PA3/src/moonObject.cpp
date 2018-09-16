#include"moonObject.h"

void MoonObject::Update(unsigned int dt,glm::mat4 position)
{
	angle += (dt * M_PI/2000);
  translate = glm::translate(position, glm::vec3(2.0f * cos(angle/3), 0.0f,2.0f * sin(angle/3)));
  model = glm::rotate(translate, (angle), glm::vec3(0.0, 1.0, 0.0));
}
