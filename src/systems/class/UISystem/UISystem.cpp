#include "UISystem.hpp"
#include "Launcher.hpp"

nx::UISystem::UISystem(nx::Launcher& root)
:
	SystemTpl(root, "ui"),
	_app(this->_root.getArgc(), this->_root.getArgv())
{

}

nx::UISystem::~UISystem()
{
}

void nx::UISystem::init()
{
}

int nx::UISystem::run() {
	return this->_app.exec();
}