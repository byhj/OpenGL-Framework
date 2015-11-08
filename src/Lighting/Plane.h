#ifndef Plane_H
#define Plane_H

#include "ogl/Shader.h"
#include "ogl/TextureMgr.h"
#include "LightGUI.h"

namespace byhj
{

   class Plane
   {
   public:
	   Plane() = default;
	  ~Plane() = default;

	  void Init();
	  void Update();
	  void Render();
	  void Shutdown();

   private:
	   void init_buffer();
	   void init_vertexArray();
	   void init_shader();
	   void init_texture();

	   ogl::Shader m_PlaneShader;
	   ogl::TextureMgr m_TextureMgr;

	   LightGUI m_LightGUI;

	   struct UniformLoc
	   {
		   GLuint model;
		   GLuint view;
		   GLuint proj;
		   GLuint woodTex;
	   }uniform_loc;

	   GLuint program = 0;
	   GLuint vao = 0;
	   GLuint vbo = 0;
	   GLuint ibo = 0;
	   GLuint woodTex;

   };


}
#endif