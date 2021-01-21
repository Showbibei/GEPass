#include "AudioSource.h"
#include "Audio.h"
#include <iostream>

namespace myengine
{
	void AudioSource::onInitialize(std::shared_ptr<Audio> audio)
	{
		alGenSources(1, &aid);
		alSourcei(aid, AL_BUFFER, audio->id);
		alSourcePlay(aid);
		std::cout << "i played something" << std::endl;
	}

	void AudioSource::onTick()
	{
		ALint state = 0;
		alGetSourcei(aid, AL_SOURCE_STATE, &state);

		if (state == AL_STOPPED)
		{
			//destroy();
		}
	}

	void AudioSource::onDestroy()
	{
		alDeleteSources(1, &aid);
	}
}