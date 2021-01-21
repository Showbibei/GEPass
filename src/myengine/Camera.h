#ifndef MYENGINE_CAMERA_H
#define MYENGINE_CAMERA_H
#include "Component.h"
#include <glm/geometric.hpp>
#include <rend/rend.h>

namespace myengine
{

	struct Camera : public Component
	{

		void onInitialize();
		//void onDestroy();
		void onTick();

		rend::mat4 getViewMat();
		std::shared_ptr<rend::RenderTexture> getRenderTexture();

		std::shared_ptr<rend::RenderTexture> addRenderTexture();
		//
		rend::mat4 persp;
		float fovy;
		float aspect;
		float near;
		float far;

		float yaw;
		float pitch;


		rend::vec3 direction;
		//
	private:
		std::shared_ptr<rend::RenderTexture> renderTexture;
	};

}

#endif