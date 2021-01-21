#ifndef MYENGINE_MODEL_H
#define MYENGINE_MODEL_H
#include "Asset.h"
#include "Exception.h"

#include <rend/rend.h>

#include <string>
#include <memory>

namespace myengine
{
struct Renderer;

struct Model : public Asset
{
  void onLoad();

private:
  friend struct myengine::Renderer;

  std::shared_ptr<rend::Mesh> mesh;

};

}
#endif
