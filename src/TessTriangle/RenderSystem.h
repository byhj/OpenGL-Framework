#ifndef __RenderSystem_H_
#define __RenderSystem_H_

#include "ogl/App.h"
#include "TessTriangle.h"

namespace byhj
{
	class RenderSystem : public ogl::App
	{
	public:
		RenderSystem() = default; 
		~RenderSystem() = default;

	public:
		void v_InitInfo() override;
		void v_Init()   override;
		void v_Update() override;
		void v_Render() override;
		void v_Shutdown() override;

	private:
		TessTriangle m_TessTriangle;

	};

}
#endif