#ifndef __TextureMgr_H_
#define __TextureMgr_H_

#include "SOIL.h"
#include <string>
#include <unordered_map>
#include <gl/glew.h>
#include <vector>
#include <iostream>
#include <memory>

namespace byhj
{
	namespace ogl
	{
		class TextureMgr
		{
		public:
			TextureMgr() = default;
			~TextureMgr() = default;

			std::shared_ptr<TextureMgr> getInstance()
			{
				static std::shared_ptr<TextureMgr> pInstance = std::make_shared<TextureMgr>();
				return pInstance;
			}

			void Init(std::string folder = "../../media/textures/");
			GLuint LoadTexture(const std::string &fileName);
			GLuint LoadDDS(const std::string &fileName);
			GLuint LoadTexture(const std::string &fileName, GLboolean alpha);
			GLuint LoadTexture(const std::vector<std::string> &faces);
			GLuint LoadTextureGamma(GLchar* path, bool gammaCorrection);

			void UnLoadTexture(const std::string &fileName);
			GLuint GetTexID(const std::string &name) 
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
