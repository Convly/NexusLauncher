#ifndef NEXUS_LAUNCHER_SYSTEM_UI_HPP_
# define NEXUS_LAUNCHER_SYSTEM_UI_HPP_

#include <QApplication>
#include "SystemTpl.hpp"

namespace nx {
	class UISystem : public nx::SystemTpl
	{
	public:
		UISystem(nx::Launcher&);
		~UISystem();

	public:
		virtual void				init(void);
		virtual int					run(void);

	private:
		QApplication                _app;	

	};
}

#endif // !NEXUS_LAUNCHER_SYSTEM_UI_HPP_
