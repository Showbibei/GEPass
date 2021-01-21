#ifndef MYENGINE_TRANSFORM_H
#define MYENGINE_TRANSFORM_H
#include "Component.h"

#include <rend/rend.h>

namespace myengine
{

struct Transform : public Component
{
  void onInitialize();

  rend::mat4 getModel();
  void setPosition(rend::vec3 position);
  void setScale(rend::vec3 scale);
  void translate(float x, float y, float z);
  void rotate(float x, float y, float z);

  rend::vec3 position;
  rend::vec3 rotation;
  rend::vec3 scale;

};

}

#endif
