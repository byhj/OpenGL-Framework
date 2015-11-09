#ifndef Audio_H
#define Audio_H

#include <iostream>
#include <string>

#include "irrKlang/irrKlang.h"

using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")

namespace byhj
{

	class Audio
	{
	public:
		Audio()  = default;
		~Audio() = default;

		void Init();
		void Play(std::string soundFile);
		void Shutdown();

	private:
		std::string folder = "../../media/sounds/";
		ISoundEngine *pSoundEngine = nullptr;
	};


}
#endif