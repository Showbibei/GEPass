#include "Rigidbody.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include <iostream>
#include <algorithm>
#include <iterator>

namespace myengine
{
	void RigidBody::onInitialize()
	{
		std::shared_ptr<RigidBody> self = getEntity()->getComponent<RigidBody>();
		getCore()->rigidbodies.push_back(self);

		std::shared_ptr<BoxCollider> boxCollider = std::make_shared<BoxCollider>();
		id = rand() % 500000;

		collider = boxCollider;

		velocity = rend::vec3(0);

		collisions = std::vector<std::shared_ptr<RigidBody>>();
	}

	void RigidBody::onCollisionEnter(std::shared_ptr<RigidBody> other)
	{

	}
	void RigidBody::onCollisionStay(std::shared_ptr<RigidBody> other)
	{

	}
	void RigidBody::onCollisionLeave(std::shared_ptr<RigidBody> other)
	{

	}

	void RigidBody::MovePosition(rend::vec3 position)
	{
		if (!CheckCollision(position))
		{
			getEntity()->getTransform()->position += position;
		}
	}

	bool RigidBody::CheckCollision(rend::vec3 position)
	{
		bool collision = false;

		rend::vec3 m_position = getEntity()->getTransform()->position + position + collider->center;

		rend::vec2 m_xrange = rend::vec2(m_position.x - (collider->size.x / 2), m_position.x + (collider->size.x / 2));
		rend::vec2 m_yrange = rend::vec2(m_position.y - (collider->size.y / 2), m_position.y + (collider->size.y / 2));
		rend::vec2 m_zrange = rend::vec2(m_position.z - (collider->size.z / 2), m_position.z + (collider->size.z / 2));

		std::vector<std::shared_ptr<RigidBody>> newCollisions = std::vector<std::shared_ptr<RigidBody>>();

		for (int i = 0; i < getCore()->rigidbodies.size(); i++)
		{
			std::shared_ptr<RigidBody> rb = getCore()->rigidbodies[i];

			if (rb->id != id)
			{
				rend::vec3 o_position = rb->getTransform()->position + rb->collider->center;

				rend::vec2 o_xrange = rend::vec2(o_position.x - (rb->collider->size.x / 2), o_position.x + (rb->collider->size.x / 2));
				rend::vec2 o_yrange = rend::vec2(o_position.y - (rb->collider->size.y / 2), o_position.y + (rb->collider->size.y / 2));
				rend::vec2 o_zrange = rend::vec2(o_position.z - (rb->collider->size.z / 2), o_position.z + (rb->collider->size.z / 2));

				if (m_xrange.y > o_xrange.x &&
					m_xrange.x < o_xrange.y &&
					m_yrange.y > o_yrange.x &&
					m_yrange.x < o_yrange.y &&
					m_zrange.y > o_zrange.x &&
					m_zrange.x < o_zrange.y)
				{
					newCollisions.push_back(rb);
					collision = true;
				}
			}
		}

		for (int i = 0; i < newCollisions.size(); i++)
		{
			if (std::find(collisions.begin(), collisions.end(), newCollisions[i]) != collisions.end())
			{
				// onCollisionStay
				onCollisionStay(newCollisions[i]);
			}
			else
			{
				// onCollisionEnter
				onCollisionEnter(newCollisions[i]);
				collisions.push_back(newCollisions[i]);
			}
		}

		//std::vector<std::shared_ptr<RigidBody>> finalCollisions = std::vector<std::shared_ptr<RigidBody>>();
		//std::vector<std::shared_ptr<RigidBody>>::iterator it = collisions.begin();

		//for (int i = 0; i < collisions.size(); i++)
		//{
		//	if (std::find(newCollisions.begin(), newCollisions.end(), collisions[i]) != newCollisions.end())
		//	{
		//		finalCollisions.push_back(collisions[i]);
		//	}
		//	else
		//	{
		//		// onCollisionLeave
		//		onCollisionLeave(newCollisions[i]);
		//	}
		//}

		//collisions = finalCollisions;

		return collision;
	}


}