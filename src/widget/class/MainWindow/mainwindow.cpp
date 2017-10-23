#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "UISystem.hpp"

MainWindow::MainWindow(QWidget *parent, nx::UISystem &uiSystem) :
    QMainWindow(parent),
    _ui(std::make_shared<Ui::MainWindow>()),
	_uiSystem(uiSystem)
{
    this->_ui->setupUi(this);
}

MainWindow::~MainWindow()
{

}
