#ifndef MYENGINE_BOXCOLLIDER_H
#define MYENGINE_BOXCOLLIDER_H
#include <rend/rend.h>
#include "Component.h"

namespace myengine
{
	struct BoxCollider
	{
		rend::vec3 size;
		rend::vec3 center;

		BoxCollider()
		{
			size = rend::vec3(1, 1, 1); //Will always initialize BoxCollider size to a 1x1x1 cube
			center = rend::vec3(0);
		}
	};

}

#endif