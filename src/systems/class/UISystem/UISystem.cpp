#include "UISystem.hpp"
#include "Launcher.hpp"

nx::UISystem::UISystem(nx::Launcher& root)
:
	SystemTpl(root, "ui"),
	_app(this->_root.getArgc(), this->_root.getArgv()),
	_windowList({
		{ "MainWindow", std::make_shared<MainWindow>(nullptr, *this) }
	})
{

}

nx::UISystem::~UISystem()
{

}

int const										nx::UISystem::showWindow(std::string const& windowName)
{
	if (this->_windowList.find(windowName) == this->_windowList.end())
		return (1);
	this->_windowList[windowName]->show();
	return (0);
}

int const										nx::UISystem::hideWindow(std::string const& windowName)
{
	if (this->_windowList.find(windowName) == this->_windowList.end())
		return (1);
	this->_windowList[windowName]->hide();
	return (0);
}

void nx::UISystem::init()
{
}

int nx::UISystem::run() {
	this->showWindow("MainWindow");
	return (this->_app.exec());
}