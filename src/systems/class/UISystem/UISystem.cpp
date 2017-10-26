#include "UISystem.hpp"
#include "GamesSystem.hpp"
#include "Launcher.hpp"

nx::UISystem::UISystem(nx::Launcher& root)
:
	SystemTpl(root, "ui"),
	_app(this->_root.getArgc(), this->_root.getArgv()),
	_widgetList({
		{ "MainWindow", std::make_shared<MainWindow>(nullptr, *this) }
	})
{

}

nx::UISystem::~UISystem()
{

}

// Showing widget by its name
int const										nx::UISystem::showWidget(std::string const& widgetName)
{
	if (this->_widgetList.find(widgetName) == this->_widgetList.end())
		return (1);
	this->_widgetList[widgetName]->show();
	return (0);
}

// Hiding widget by its name
int const										nx::UISystem::hideWidget(std::string const& widgetName)
{
	if (this->_widgetList.find(widgetName) == this->_widgetList.end())
		return (1);
	this->_widgetList[widgetName]->hide();
	return (0);
}

// Get GamesSystem object
nx::GamesSystem* nx::UISystem::getGameSystem()
{
	return dynamic_cast<nx::GamesSystem*>(this->getRoot().getSystemByName("games").get());
}

// Initialize all widgets
void nx::UISystem::init()
{

}

int nx::UISystem::run()
{
	return (this->_app.exec());
}