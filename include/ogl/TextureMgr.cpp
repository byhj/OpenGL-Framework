#include "TextureMgr.h"

namespace byhj
{
	namespace ogl
	{
		TextureMgr * getInstance()
		{
			static TextureMgr *pInstance = new TextureMgr;
			return pInstance;
		}

		void TextureMgr::Init(std::string folder)
		{
			this->folder = folder;
		}

		
		GLuint TextureMgr::LoadTexture(const std::string &fileName)
		{
			std::string textureFile = folder + fileName;
			int width, height;
			unsigned char*image = SOIL_load_image( textureFile.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
			if (!image)
				std::cout << "Fail to load the texture file:" << fileName << std::endl;
			else
				std::cout << "Load the texture file:" << fileName << std::endl;

			GLuint tex = -1;

			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);

			m_TexID[fileName] = tex;

			SOIL_free_image_data(image);
			glBindTexture(GL_TEXTURE_2D, 0);

			return tex;
		}
		GLuint TextureMgr::LoadDDS(const std::string &fileName)
		{
			std::string textureFile = folder + fileName;
			GLuint tex = -1;
			tex = SOIL_load_OGL_texture(textureFile.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
				   SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

			glBindTexture(GL_TEXTURE_2D, tex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    	glGenerateMipmap(GL_TEXTURE_2D);

			m_TexID[fileName] = tex;

			glBindTexture(GL_TEXTURE_2D, 0);

			return tex;
		}
		GLuint TextureMgr::LoadTexture(const std::string &fileName, GLboolean alpha)
		{
			std::string textureFile = folder + fileName;
			int width, height;
			unsigned char*image = SOIL_load_image(textureFile.c_str(), &width, &height, 0, alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
			if (!image)
				std::cout << "Fail to load the texture file:" << fileName << std::endl;
			else
				std::cout << "Load the texture file:" << fileName << std::endl;

			GLuint tex = -1;

			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);
			glTexImage2D(GL_TEXTURE_2D, 0, alpha ? GL_RGBA : GL_RGB, width, height, 0, alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);

			// Parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);	// Use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes value from next repeat 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			m_TexID[fileName] = tex;

			SOIL_free_image_data(image);
			glBindTexture(GL_TEXTURE_2D, 0);

			return tex;
		}

		GLuint TextureMgr::LoadTexture(const std::vector<std::string> &faces)
		{

			int width, height;
			unsigned char *image;


			GLuint tex = SOIL_load_OGL_cubemap
				(
					(folder + faces[0]).c_str(),
					(folder + faces[1]).c_str(),
					(folder + faces[2]).c_str(),
					(folder + faces[3]).c_str(),
					(folder + faces[4]).c_str(),
					(folder + faces[5]).c_str(),
					SOIL_LOAD_RGBA,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS
					);
			

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			
			m_TexID[faces[0]] = tex;

			return tex;
		}

		GLuint TextureMgr::LoadTextureGamma(GLchar* fileName, bool gammaCorrection)
		{
			// Generate texture ID and load texture data 
			GLuint textureID;
			glGenTextures(1, &textureID);
			int width, height;

			std::string textureFile = folder + fileName;
			unsigned char* image = SOIL_load_image(textureFile.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
			// Assign texture to ID
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, gammaCorrection ? GL_SRGB : GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);

			// Parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);
			SOIL_free_image_data(image);
			return textureID;
		}
		void TextureMgr::UnLoadTexture(const std::string &fileName)
		{
			auto iter = m_TexID.find(fileName);
			if (iter != m_TexID.end())
			{
				m_TexID.erase(fileName);
			}

		}
	}
}