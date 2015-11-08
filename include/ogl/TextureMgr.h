#ifndef __TextureMgr_H_
#define __TextureMgr_H_

#include "SOIL.h"
#include <string>
#include <unordered_map>
#include <gl/glew.h>
#include <vector>
#include <iostream>

namespace byhj
{
	namespace ogl
	{
		class TextureMgr
		{
		public:
			TextureMgr() = default;
			~TextureMgr() = default;

			void Init(std::string folder = "../../media/textures/");
			bool LoadTexture(const std::string &fileName);
			bool LoadTexture(const std::string &fileName, GLboolean alpha);
			bool LoadTexture(const std::vector<std::string> &faces);
			bool UnLoadTexture(const std::string &fileName);
			GLuint GetTexID(const std::string &name) const
			{
				return m_TexID[name];
			}
		private:
			std::unordered_map<std::string, GLuint> m_TexID;
			std::string folder;
		};
	}
}
#endif
