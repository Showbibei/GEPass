#ifndef MYENGINE_COMPONENT_H
#define MYENGINE_COMPONENT_H

#include <memory>

namespace myengine
{

struct Entity;
struct Core;
struct Transform;


struct Component
{
  friend struct myengine::Entity;

  virtual void onInitialize();

  void tick();
  virtual void onTick();

  void render();
  virtual void onRender();

  void destroy();
  virtual void onDestroy();

  std::shared_ptr<Entity> getEntity();
  std::shared_ptr<Core> getCore();
  std::shared_ptr<Transform> getTransform();

private:
  std::weak_ptr<Entity> entity;
};

}

#endif
