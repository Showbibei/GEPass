#ifndef MYENGINE_RIGIDBODY_H
#define MYENGINE_RIGIDBODY_H

#include "Component.h"
#include "BoxCollider.h"
#include <rend/rend.h>

namespace myengine
{
	


struct RigidBody : public Component
{
	void onInitialize();
	bool CheckCollision(rend::vec3 position);
	void MovePosition(rend::vec3 position);
	std::shared_ptr<BoxCollider> collider;

	int id;

	rend::vec3 velocity;

	std::vector<std::shared_ptr<RigidBody>> collisions;

	virtual void onCollisionEnter(std::shared_ptr<RigidBody> other);
	virtual void onCollisionStay(std::shared_ptr<RigidBody> other);
	virtual void onCollisionLeave(std::shared_ptr<RigidBody> other);
	
};


}

#endif