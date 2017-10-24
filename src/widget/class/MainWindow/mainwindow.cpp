#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "UISystem.hpp"

MainWindow::MainWindow(QWidget *parent, nx::UISystem &uiSystem) :
	QMainWindow(parent),
	_ui(std::make_shared<Ui::MainWindow>()),
	_listWidgets({
		{ "GamesLabel", std::make_shared<InteractiveLabel>(this, "GAMES", 12) },
		{ "StoreLabel", std::make_shared<InteractiveLabel>(this, "STORE", 12) }
	}),
	_uiSystem(uiSystem),
	_gamesLabelAnim(std::make_shared<QPropertyAnimation>(this->_listWidgets["GamesLabel"].get(), "color")),
	_storeLabelAnim(std::make_shared<QPropertyAnimation>(this->_listWidgets["StoreLabel"].get(), "color"))
{
	this->_ui->setupUi(this);

	this->_listWidgets["GamesLabel"]->setMaximumSize(60, 26);
	dynamic_cast<QLabel *>(this->_listWidgets["GamesLabel"].get())->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	dynamic_cast<InteractiveLabel *>(this->_listWidgets["GamesLabel"].get())->setColor(QColor(255, 255, 255, 140));
	this->_listWidgets["StoreLabel"]->setMaximumSize(60, 26);
	dynamic_cast<QLabel *>(this->_listWidgets["StoreLabel"].get())->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	dynamic_cast<InteractiveLabel *>(this->_listWidgets["StoreLabel"].get())->setColor(QColor(255, 255, 255, 140));

	this->_ui->SecondCell->addWidget(this->_listWidgets["GamesLabel"].get());
	this->_ui->ThirdCell->addWidget(this->_listWidgets["StoreLabel"].get());

	/*this->_listWidgets["GamesLabel"]->setStyleSheet("\
			QLabel { \
				background-color: white; \
				color: black; \
				transition: all 0.4s; \
			} \
			QLabel:hover { \
				color: white; \
				background-color: black; \
			} \
		");*/
	//this->_listWidgets["GamesLabel"]->setStyleSheet("QLabel:hover {color: white}");

	/*this->_listWidgets["GamesLabel"]->setStyleSheet("color: rgb(%1, %2, %3);");
	this->_listWidgets["StoreLabel"]->setStyleSheet("color: rgb(%1, %2, %3);");*/

	this->setStyleSheet("background-color: rgb(5, 30, 56);");

	QObject::connect(this->_listWidgets["GamesLabel"].get(), SIGNAL(clicked()), this, SLOT(GamesLabelClicked()));
	QObject::connect(this->_listWidgets["StoreLabel"].get(), SIGNAL(clicked()), this, SLOT(StoreLabelClicked()));
	QObject::connect(this->_listWidgets["GamesLabel"].get(), SIGNAL(entered()), this, SLOT(GamesLabelEntered()));
	QObject::connect(this->_listWidgets["StoreLabel"].get(), SIGNAL(entered()), this, SLOT(StoreLabelEntered()));
	QObject::connect(this->_listWidgets["GamesLabel"].get(), SIGNAL(left()), this, SLOT(GamesLabelLeft()));
	QObject::connect(this->_listWidgets["StoreLabel"].get(), SIGNAL(left()), this, SLOT(StoreLabelLeft()));
}

MainWindow::~MainWindow()
{

}

#include <iostream>

void MainWindow::GamesLabelClicked()
{
	std::cout << "GamesLabel is clicked" << std::endl;
	std::cout << this->_listWidgets["GamesLabel"]->styleSheet().toStdString() << std::endl;
}

void MainWindow::StoreLabelClicked()
{
	std::cout << "StoreLabel is clicked" << std::endl;
	std::cout << this->_listWidgets["StoreLabel"]->styleSheet().toStdString() << std::endl;
}

void MainWindow::GamesLabelEntered()
{
	this->_gamesLabelAnim->setDuration(250);
	this->_gamesLabelAnim->setStartValue(QColor(255, 255, 255, 140));
	this->_gamesLabelAnim->setEndValue(QColor(255, 255, 255, 255));
	this->_gamesLabelAnim->start();

	this->_listWidgets["GamesLabel"]->setCursor(Qt::PointingHandCursor);
	std::cout << "GamesLabel is entered" << std::endl;
	std::cout << this->_listWidgets["GamesLabel"]->styleSheet().toStdString() << std::endl;
}

void MainWindow::StoreLabelEntered()
{
	this->_storeLabelAnim->setDuration(250);
	this->_storeLabelAnim->setStartValue(QColor(255, 255, 255, 140));
	this->_storeLabelAnim->setEndValue(QColor(255, 255, 255, 255));
	this->_storeLabelAnim->start();

	this->_listWidgets["StoreLabel"]->setCursor(Qt::PointingHandCursor);
	std::cout << "StoreLabel is entered" << std::endl;
	std::cout << this->_listWidgets["StoreLabel"]->styleSheet().toStdString() << std::endl;
}

void MainWindow::GamesLabelLeft()
{
	this->_gamesLabelAnim->setDuration(0);
	this->_gamesLabelAnim->setStartValue(QColor(255, 255, 255, 140));
	this->_gamesLabelAnim->setEndValue(QColor(255, 255, 255, 140));
	this->_gamesLabelAnim->start();

	this->_listWidgets["GamesLabel"]->setCursor(Qt::ArrowCursor);
	std::cout << "GamesLabel is left" << std::endl;
	std::cout << this->_listWidgets["GamesLabel"]->styleSheet().toStdString() << std::endl;
}

void MainWindow::StoreLabelLeft()
{
	this->_storeLabelAnim->setDuration(0);
	this->_storeLabelAnim->setStartValue(QColor(255, 255, 255, 140));
	this->_storeLabelAnim->setEndValue(QColor(255, 255, 255, 140));
	this->_storeLabelAnim->start();

	this->_listWidgets["StoreLabel"]->setCursor(Qt::ArrowCursor);
	std::cout << "StoreLabel is left" << std::endl;
	std::cout << this->_listWidgets["StoreLabel"]->styleSheet().toStdString() << std::endl;
}