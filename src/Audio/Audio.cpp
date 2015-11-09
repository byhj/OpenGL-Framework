#include "Audio.h"

namespace byhj
{
	void Audio::Init()
	{
		pSoundEngine = createIrrKlangDevice();

		if (pSoundEngine == nullptr)
		{
			std::cout << "Count not Startup engine" << std::endl;
		}
	}

	void Audio::Play(std::string soundFile)
	{
		std::cout << "Play Sound: " << soundFile << std::endl;
		//Loop the music
		pSoundEngine->play2D( (folder + soundFile).c_str(), true);
	}

	void Audio::Shutdown()
	{
		pSoundEngine->drop();
	}
}