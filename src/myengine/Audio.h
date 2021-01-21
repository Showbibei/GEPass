#ifndef MYENGINE_AUDIO_H
#define MYENGINE_AUDIO_H
#include <AL/al.h>
#include <AL/alc.h>


#include <rend/rend.h>
#include "Asset.h"
#include "Component.h"

#include <memory>
#include <string>

namespace myengine
{
	struct AudioSource;

	struct Audio : public Asset
	{
		friend struct AudioSource;

		void onLoad();
		void loadOgg(const std::string& fileName, std::vector<char>& buffer, ALenum& format, ALsizei& freq);
		void onCollide();

	private:
		ALuint id;
	};
}
#endif