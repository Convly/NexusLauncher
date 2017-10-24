#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "UISystem.hpp"

MainWindow::MainWindow(QWidget *parent, nx::UISystem &uiSystem) :
	QMainWindow(parent),
	_ui(std::make_shared<Ui::MainWindow>()),
	_uiSystem(uiSystem)
{
	this->_ui->setupUi(this);

	// Initializing Navbar Widgets
	this->_listWidgets = {
		{ "LogoLabel", std::make_shared<QLabel>(this->_ui->NavBarFrame) },
		{ "GamesLabel", std::make_shared<InteractiveLabel>(this->_ui->NavBarFrame, "GAMES", 12) },
		{ "StoreLabel", std::make_shared<InteractiveLabel>(this->_ui->NavBarFrame, "STORE", 12) }
	};

	// Initializing Animators
	this->_gamesLabelAnim = std::make_shared<QPropertyAnimation>(this->_listWidgets["GamesLabel"].get(), "color");
	this->_storeLabelAnim = std::make_shared<QPropertyAnimation>(this->_listWidgets["StoreLabel"].get(), "color");

	// Window background color
	this->setStyleSheet("background-color: rgb(5, 30, 56);");

	// Adding the Nexus logo
	dynamic_cast<QLabel *>(this->_listWidgets["LogoLabel"].get())->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	QPixmap img("../images/nexuslogo.png");
	dynamic_cast<QLabel *>(this->_listWidgets["LogoLabel"].get())->setPixmap(img.scaled(160, 90, Qt::KeepAspectRatio));
	this->_listWidgets["LogoLabel"]->setGeometry(20, 0, 160, 90);

	// Adding InteractiveLabels into the Navbar
	this->_listWidgets["GamesLabel"]->setGeometry(230, 35, 60, 26);
	dynamic_cast<QLabel *>(this->_listWidgets["GamesLabel"].get())->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	dynamic_cast<InteractiveLabel *>(this->_listWidgets["GamesLabel"].get())->setColor(QColor(255, 255, 255, 140));
	this->_listWidgets["StoreLabel"]->setGeometry(320, 35, 60, 26);
	dynamic_cast<QLabel *>(this->_listWidgets["StoreLabel"].get())->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	dynamic_cast<InteractiveLabel *>(this->_listWidgets["StoreLabel"].get())->setColor(QColor(255, 255, 255, 140));

	// TEMP: Adding Rtype item label
	this->_ui->GamesList->addItem("rtype");
	this->_ui->GamesList->item(0)->setForeground(Qt::white);

	// Signal functions call
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

// Triggered when the GAMES label is clicked
void MainWindow::GamesLabelClicked()
{

}

// Triggered when the STORE label is clicked
void MainWindow::StoreLabelClicked()
{

}

// Triggered when the mouse is entering the GAMES label
void MainWindow::GamesLabelEntered()
{
	this->_gamesLabelAnim->setDuration(250);
	this->_gamesLabelAnim->setStartValue(QColor(255, 255, 255, 140));
	this->_gamesLabelAnim->setEndValue(QColor(255, 255, 255, 255));
	this->_gamesLabelAnim->start();
	this->_listWidgets["GamesLabel"]->setCursor(Qt::PointingHandCursor);
}

// Triggered when the mouse is entering the STORE label
void MainWindow::StoreLabelEntered()
{
	this->_storeLabelAnim->setDuration(250);
	this->_storeLabelAnim->setStartValue(QColor(255, 255, 255, 140));
	this->_storeLabelAnim->setEndValue(QColor(255, 255, 255, 255));
	this->_storeLabelAnim->start();
	this->_listWidgets["StoreLabel"]->setCursor(Qt::PointingHandCursor);
}

// Triggered when the mouse is leaving the GAMES label
void MainWindow::GamesLabelLeft()
{
	this->_gamesLabelAnim->setDuration(0);
	this->_gamesLabelAnim->setStartValue(QColor(255, 255, 255, 140));
	this->_gamesLabelAnim->setEndValue(QColor(255, 255, 255, 140));
	this->_gamesLabelAnim->start();
	this->_listWidgets["GamesLabel"]->setCursor(Qt::ArrowCursor);
}

// Triggered when the mouse is leaving the STORE label
void MainWindow::StoreLabelLeft()
{
	this->_storeLabelAnim->setDuration(0);
	this->_storeLabelAnim->setStartValue(QColor(255, 255, 255, 140));
	this->_storeLabelAnim->setEndValue(QColor(255, 255, 255, 140));
	this->_storeLabelAnim->start();
	this->_listWidgets["StoreLabel"]->setCursor(Qt::ArrowCursor);
}