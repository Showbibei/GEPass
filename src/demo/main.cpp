#include <myengine/myengine.h>
#include <algorithm>

struct Controller : public Component
{
    void MovePosition(rend::vec3 velocity)
    {
        getEntity()->getComponent<RigidBody>()->MovePosition(velocity);
    }
  
    void Movement()
    {
        float speed = 0.25;
        rend::vec3 velocity = rend::vec3(0, 0, 0);
        rend::vec3 direction = getCore()->getCamera()->direction;

        if (getCore()->getKeyboard()->getKey('w'))
        {
            velocity += speed * direction;
        }

        if (getCore()->getKeyboard()->getKey('s'))
        {
            velocity -= speed * direction;
        }

        if (getCore()->getKeyboard()->getKey('a'))
        {
            velocity -= rend::cross(direction, rend::vec3(0, 1, 0)) * speed;
        }

        if (getCore()->getKeyboard()->getKey('d'))
        {
            velocity += rend::cross(direction, rend::vec3(0, 1, 0)) * speed;
        }

        velocity.y = 0;
        MovePosition(velocity);
    }

    void onTick()
    {
        if (getCore()->getCamera() == nullptr) return;

        Movement();

        if (getCore()->getKeyboard()->getKey('e'))
        {
            getTransform()->rotate(1, 0, 0);
        }

        if (getCore()->getKeyboard()->getKey('q'))
        {
            getTransform()->rotate(-1, 0, 0);
        }
    }
};

struct Coin : public Component
{
    void onInitialize()
    {
        ShaderMaterial coinMaterial;
        coinMaterial.SetMaterial(rend::vec3(1, 1, 0), 0.0f, 0.3f, 0.0f);
        std::shared_ptr<Renderer> r = getEntity()->addComponent<Renderer>(coinMaterial);
        std::shared_ptr<Model> m = getCore()->getAssetManager()->load<Model>("../assets/coin");
        r->setModel(m);
    }
};

struct Floor : public Component
{
    void onInitialize()
    {
        ShaderMaterial cubeMaterial;
        cubeMaterial.SetMaterial(rend::vec3(0.5, 0.5, 0.5), 0.1f, 0.1f, 0.1f);
        std::shared_ptr<Renderer> r = getEntity()->addComponent<Renderer>(cubeMaterial);
        std::shared_ptr<Model> m = getCore()->getAssetManager()->load<Model>("../assets/cube");
        r->setModel(m);
    }
};

struct Curuthers : public Component
{
    void onInitialize()
    {
        std::shared_ptr<Renderer> r = getEntity()->addComponent<Renderer>();
        std::shared_ptr<Model> m = getCore()->getAssetManager()->load<Model>("../assets/curuthers/curuthers");
        r->setModel(m);
    }
};

struct Playerbody : RigidBody
{
    void onCollisionEnter(std::shared_ptr<RigidBody> other)
    {
        if (other->getEntity()->tag == "")
        {
            std::cout << "Enter" << std::endl;
            std::shared_ptr<Entity> audio = getCore()->addEntity();
            std::shared_ptr<AudioSource> a = audio->addComponent<AudioSource>(getCore()->getAssetManager()->load<Audio>("../assets/yeah"));
            //other->getEntity()->destroy();
        }
        
    }
};

struct Destroyer : public Component
{
    void onTick()
    {
        if (getCore()->getKeyboard()->getKey('p'))
        {
            std::cout << "bye" << std::endl;
            getEntity()->destroy();
        }
    }
};


int main()
{
  std::shared_ptr<Core> core = Core::initialize(); //Create an instance of Core and initialize. Initializes SDL, AL and glew for use. 
  
  /*
  To create an entity use std::shared_ptr<Entity> entity = core->AddEntity()
  This creates an entity and adds it to the list of entities stored in Core

  To add a component, use entity->addComponent<Component>

  Current list of Components: Controller | Coin | Floor | Curuthers | Playerbody | Destroyer | Camera | Renderer
  See individual components for their use
  
  User can also create their own components 
  */

  
  for (int i = 0; i < 10; i++) //Simple for loop to create 10 coins at 'random' locations within a set space
  {
      int randX = rand() % 50;
      int randY = rand() % 50;
      int offset = 20;
      std::shared_ptr<Entity> coin = core->addEntity();
      coin->addComponent<Coin>();
      coin->getTransform()->setPosition(rend::vec3(randX - offset, 0, randY - offset));
      coin->getTransform()->setScale(rend::vec3(0.01, 0.01, 0.01));
      coin->addComponent<RigidBody>();
  }


  std::shared_ptr<Entity> curuthers = core->addEntity("curuthers", "a cat"); 
  curuthers->addComponent<Curuthers>();
  curuthers->getTransform()->setPosition(rend::vec3(-10, 0, -20));           //Curuthers the cat
  curuthers->getTransform()->setScale(rend::vec3(1, 1, 1));
  curuthers->addComponent<Destroyer>();
  curuthers->addComponent<RigidBody>();
  

  std::shared_ptr<Entity> floor = core->addEntity();
  floor->addComponent<Floor>();
  floor->getTransform()->setScale(rend::vec3(100, 1, 100));
  floor->getTransform()->setPosition(rend::vec3(10, -3, 0)); 
  floor->addComponent<RigidBody>();

  std::shared_ptr<Entity> player = core->addEntity();
  player->addComponent<Camera>();
  player->addComponent<Controller>();
  player->addComponent<Playerbody>();
  player->getTransform()->setPosition(rend::vec3(10, 0, 0));

  core->start(); //Starting the main loop 

  return 0;
}
