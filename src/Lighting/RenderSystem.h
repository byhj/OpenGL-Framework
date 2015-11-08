#ifndef RenderSystem_H
#define RenderSystem_H

#include "ogl/App.h"

namespace byhj
{
	class RenderSystem : public ogl::App
	{
	public:
		RenderSystem()  = default;
		~RenderSystem() = default;

		void v_InitInfo() override;
		void v_Init() override;
		void v_Update() override;
		void v_Render() override;
		void v_Shutdown() override;

	private:

	};
}

#endif
