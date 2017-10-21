#ifndef NEXUS_LAUNCHER_SYSTEM_UI_HPP_
# define NEXUS_LAUNCHER_SYSTEM_UI_HPP_

#include "SystemTpl.hpp"

namespace nx {
	class UISystem : public nx::SystemTpl
	{
	public:
		UISystem();
		~UISystem();

	public:
		virtual void				init(void);

	};
}

#endif // !NEXUS_LAUNCHER_SYSTEM_UI_HPP_
