#ifndef OGLDEBUG_H
#define OGLDEBUG_H

#include <GL/glew.h>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define INVALID_UNIFORM_LOCATION 0xffffffff
#define INVALID_OGL_VALUE 0xffffffff
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

#define GLCheckError() (glGetError() == GL_NO_ERROR)

#define GLExitIfError                                                          \
{                                                                               \
    GLenum Error = glGetError();                                                \
                                                                                \
    if (Error != GL_NO_ERROR) {                                                 \
        printf("OpenGL error in %s:%d: 0x%x\n", __FILE__, __LINE__, Error);     \
        exit(0);                                                                \
    }                                                                           \
}

namespace byhj
{

namespace ogl
{

	class Debug
	{
	public:
		Debug() 	 = default;
		~Debug()	 = default;

		void Init();
		void DebugOutputToFile(unsigned int source, unsigned int type, unsigned int id,
			unsigned int severity, const char* message);
		void CheckDebugLog();
		void DebugOutput(unsigned int source, unsigned int type, unsigned int id,
			             unsigned int severity, const char* message);
		void EmitGLError(unsigned int id, char* message, int length);

		void CALLBACK Debug::DebugCallback(unsigned int source, unsigned int type,
			unsigned int id, unsigned int severity,
			int length, const char* message, const void* userParam);

	private:


	};


}
}

#endif
