#ifndef NEXUS_LAUNCHER_SYSTEM_UI_HPP_
# define NEXUS_LAUNCHER_SYSTEM_UI_HPP_

#include <QApplication>
#include <unordered_map>
#include "SystemTpl.hpp"
#include "mainwindow.h"

namespace nx {
	class UISystem : public nx::SystemTpl
	{
	public:
		UISystem(nx::Launcher&);
		~UISystem();

	public:
		virtual void				init(void);
		virtual int					run(void);

		int const					showWindow(std::string const& windowName);
		int const					hideWindow(std::string const& windowName);

	private:
		QApplication												_app;
		std::unordered_map<std::string, std::shared_ptr<QWidget>>   _windowList;

	};
}

#endif // !NEXUS_LAUNCHER_SYSTEM_UI_HPP_
