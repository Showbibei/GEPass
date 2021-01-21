#ifndef MYENGINE_CORE_H
#define MYENGINE_CORE_H
#include <SDL2/SDL.h>
#include <rend/rend.h>
#include <AL/alc.h>
#include <memory>
#include <vector>
#include <iostream>

namespace myengine
{

struct Renderer;
struct Entity;
struct Keyboard;
struct Camera;
struct AssetManager; //Foreward declaring structs 
struct RigidBody;
struct Model;
struct Audio;

struct Core
{
  static std::shared_ptr<Core> initialize();
  /*
  addEntity has 3 overloads. Provides option for initialising an entity
  with a name and tag. Using tags can provide functionality for collisions

  For instance, User may want to collide with entities containing a floor or wall tag
  */

  std::shared_ptr<Entity> addEntity();
  std::shared_ptr<Entity> addEntity(std::string _name);						
  std::shared_ptr<Entity> addEntity(std::string _name, std::string _tag);	

  std::shared_ptr<Keyboard> getKeyboard();
  std::shared_ptr<Camera> getCamera();
  std::shared_ptr<AssetManager> getAssetManager();
  //std::shared_ptr<Audio> getAudio();

  void start();

  std::vector<std::shared_ptr<RigidBody>> rigidbodies;



private:
	friend struct myengine::Camera;
	friend struct myengine::RigidBody;
	friend struct myengine::Renderer;
	friend struct myengine::Model;
	friend struct myengine::Audio;

	std::vector<std::shared_ptr<Entity> > entities;
	std::weak_ptr<Core> self;
	SDL_Window* window;
	SDL_GLContext glContext;
	ALCdevice* device;
	ALCcontext* ALcontext;
	std::shared_ptr<rend::Context> context;
	std::shared_ptr<Keyboard> keyboard;
	std::shared_ptr<AssetManager> assetManager;
	std::shared_ptr<rend::Shader> shader;

	std::weak_ptr<Camera> currentCamera;
	std::vector<std::weak_ptr<Camera>> cameras;

};

}
#endif