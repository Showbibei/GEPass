#include "Core.h"
#include "Entity.h"
#include "Exception.h"
#include "Transform.h"
#include "Keyboard.h"
#include "AssetManager.h"

namespace myengine
{

std::shared_ptr<Core> Core::initialize()
{
    std::shared_ptr<Core> rtn = std::make_shared<Core>();
    rtn->self = rtn;

    /////////////////////////INTIALIZE SDL///////////////////////
    rtn->window = SDL_CreateWindow("myengine",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 600,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!rtn->window)
    {
        throw Exception("Failed to create window");
    }


    rtn->glContext = SDL_GL_CreateContext(rtn->window);

    if (!rtn->glContext)
    {
        throw Exception("Failed to create OpenGL context");
    }
    /////////////////////////////////////////////////////////////

    /////////////////////////INITIALIZE OPENAL///////////////////
    rtn->device = alcOpenDevice(NULL);

    if (!rtn->device)
    {
        throw Exception("Failed to open default device");
    }

    rtn->ALcontext = alcCreateContext(rtn->device, NULL);
    if (!rtn->ALcontext)
    {
        alcCloseDevice(rtn->device);
        throw Exception("Failed to create context");
    }
    if (!alcMakeContextCurrent(rtn->ALcontext))
    {
        alcDestroyContext(rtn->ALcontext);
        alcCloseDevice(rtn->device);
        throw Exception("Failed to make contextcurrent");
    }
    /////////////////////////////////////////////////////////////

    rtn->context = rend::Context::initialize();
    rtn->keyboard = std::make_shared<Keyboard>();
    rtn->assetManager = std::make_shared<AssetManager>();
    rtn->getAssetManager()->core = rtn;

    return rtn;
}

std::shared_ptr<Keyboard> Core::getKeyboard()
{
  return keyboard;
}

std::shared_ptr<AssetManager> Core::getAssetManager()
{
  return assetManager;
}

std::shared_ptr<Camera> Core::getCamera()
{
  return currentCamera.lock();
}

#pragma region addEntity
std::shared_ptr<Entity> Core::addEntity()
{
    std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
    rtn->core = self;
    rtn->self = rtn;
    rtn->alive = true;

    rtn->name = "GameObject";
    rtn->tag = "";

    rtn->addComponent<Transform>();

    entities.push_back(rtn);

    return rtn;
}

std::shared_ptr<Entity> Core::addEntity(std::string _name)
{
    std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
    rtn->core = self;
    rtn->self = rtn;
    rtn->alive = true;
    rtn->name = _name;
    rtn->tag = "";

    rtn->addComponent<Transform>();

    entities.push_back(rtn);

    return rtn;
}

std::shared_ptr<Entity> Core::addEntity(std::string _name, std::string _tag)
{
    std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
    rtn->core = self;
    rtn->self = rtn;
    rtn->alive = true;
    rtn->name = _name;
    rtn->tag = _tag;

    rtn->addComponent<Transform>();

    entities.push_back(rtn);

    return rtn;
}
#pragma endregion addEntity

void Core::start()
{
  bool running = true;
  SDL_Event e = {0};

  while(running)
  {
    while(SDL_PollEvent(&e) != 0)
    {
      if(e.type == SDL_QUIT)
      {
        running = false;
      }
      else if(e.type == SDL_KEYDOWN)
      {
        keyboard->keys.push_back(e.key.keysym.sym);
        keyboard->downKeys.push_back(e.key.keysym.sym);
      }
      else if(e.type == SDL_KEYUP)
      {
        for(std::vector<int>::iterator it = keyboard->keys.begin();
          it != keyboard->keys.end();)
        {
          if(*it == e.key.keysym.sym) it = keyboard->keys.erase(it);
          else it++;
        }

        keyboard->upKeys.push_back(e.key.keysym.sym);
      }
    }

    for(size_t ei = 0; ei < entities.size(); ei++)
    {
      entities.at(ei)->tick();
    }
    for (size_t ei = 0; ei < entities.size(); ei++)
    {
        if (entities.at(ei)->alive == false)
        {
            entities.erase(entities.begin() + ei);
            ei--;
        }
    }

    glClearColor(0.50f, 0.60f, 0.60f, 1.0f); //background colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(size_t ci = 0; ci < cameras.size(); ci++)
    {
      currentCamera = cameras.at(ci);
      glClear(GL_DEPTH_BUFFER_BIT);

      for(size_t ei = 0; ei < entities.size(); ei++)
      {
        entities.at(ei)->render();
      }
    }

    SDL_GL_SwapWindow(window);

    keyboard->downKeys.clear();
    keyboard->upKeys.clear();
  }
}

}

