#include "Camera.h"
#include "Monster.h"
#include "util.h"

#include <GL/glut.h>

#include <iostream>

std::shared_ptr<Camera> Camera::inst;

Camera::Camera()
{
  pos.y = 100;
  pos.x = 100;
}

void Camera::draw()
{
  pos.x = Monster::inst->getDistance() - glutGet(GLUT_WINDOW_WIDTH) / 2;
  pos.y = -100;
  //pos.x += 100 * util::delta_time;
}

glm::vec2 Camera::getOffset()
{
  return -pos;
}
