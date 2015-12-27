#ifndef ShaderMgr_H
#define ShaderMgr_H

#include <memory>

namespace byhj
{
	namespace ogl
	{
		class ShaderMgr
		{
		public:
			ShaderMgr() = default;
			~ShaderMgr() = default;

			std::shared_ptr<ShaderMgr> getInstance()
			{
				static std::shared_ptr<ShaderMgr> pInstance = std::make_shared<ShaderMgr>();
				return pInstance;
			}
		};

	}
}

#endif