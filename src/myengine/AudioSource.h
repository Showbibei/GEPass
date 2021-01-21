#ifndef MYENGINE_AUDIOSOURCE_H
#define MYENGINE_AUDIOSOURCE_H
#include <AL/al.h>
#include <AL/alc.h>
#include "Component.h"

namespace myengine
{
	struct Audio;
	struct AudioSource : public Component
	{
		void onInitialize(std::shared_ptr<Audio> audio);
		void onTick();
		void onDestroy();
	private:
		ALuint aid;

	};
}
#endif