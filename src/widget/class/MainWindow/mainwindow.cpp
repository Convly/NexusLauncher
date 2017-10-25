#include "mainwindow.h"
#include "UISystem.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, nx::UISystem &uiSystem) :
	QMainWindow(parent, Qt::FramelessWindowHint),
	_ui(std::make_shared<Ui::MainWindow>()),
	_uiSystem(uiSystem)
{
	this->_ui->setupUi(this);

	if (!this->_init())
	{
		// Throw an error;
	}

	// Window background color
	this->setStyleSheet("background-color: rgb(5, 30, 56);");
	this->_ui->GamesList->setStyleSheet(QString::fromUtf8(
		"QScrollBar:vertical {"
		"	border: none;"
		"	width:10px;    "
		"	background: rgb(5, 30, 56);"
		"	margin: 0px 0px 0px 0px;"
		"}"
		"QScrollBar::handle:vertical {"
		"	background: rgba(200, 200, 200, 0.1);"
		"	min-height: 0px;"
		"}"
		"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical{"
		"	background: none;"
		"}"
		"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
		"    background: none;"
		"}"
	));

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

/********************\
|*  PUBLIC METHODS  *|
\********************/


bool MainWindow::addGameToGamesList(std::string const& picPath, std::string const& gameName)
{
	if (this->_gameWidgetItemsList.find(gameName) == this->_gameWidgetItemsList.end())
	{
		this->_gameWidgetItemsList[gameName] = GameWidgetItemStruct(std::make_shared<NGameWidgetItem>(this, picPath, gameName),
																	std::make_shared<QListWidgetItem>(this->_ui->GamesList));

		this->_ui->GamesList->addItem(this->_gameWidgetItemsList[gameName].qtItem.get());
		this->_gameWidgetItemsList[gameName].qtItem->setSizeHint(this->_gameWidgetItemsList[gameName].nxItem->sizeHint());
		this->_ui->GamesList->setItemWidget(this->_gameWidgetItemsList[gameName].qtItem.get(), this->_gameWidgetItemsList[gameName].nxItem.get());
	}

	return (true);
}

bool MainWindow::removeGameFromGamesList(std::string const& gameName)
{
	// TODO: Removing an item from the list
	return (true);
}

bool MainWindow::clearGamesList()
{
	// TODO: Clearing all items from the list
	return (true);
}

void MainWindow::mousePressEvent(QMouseEvent *evt)
{
	if (evt->localPos().y() <= 35)
		this->_oldMovingPos = evt->globalPos();
	else
		this->_oldMovingPos = QPointF(-1, -1);
}

void MainWindow::mouseMoveEvent(QMouseEvent *evt)
{
	if (this->_oldMovingPos.x() != -1 && this->_oldMovingPos.y() != -1)
	{
		const QPointF delta = evt->globalPos() - this->_oldMovingPos;

		this->move(this->x() + delta.x(), this->y() + delta.y());
		this->_oldMovingPos = evt->globalPos();
	}
}

/*************\
|*  SIGNALS  *|
\*************/


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

/*********************\
|*  PRIVATE METHODS  *|
\*********************/


bool MainWindow::_init()
{
	this->_initListWidgets();
	this->_initAnimators();
	if (!this->_displayNexusLogo() || !this->_displayInteractiveLabels())
		return (false);
	this->_loadGamesList();
	this->show();
	return (true);
}

// Initializing Navbar Widgets
bool MainWindow::_initListWidgets()
{
	this->_listWidgets = {
		{ "LogoLabel", std::make_shared<QLabel>(this->_ui->NavBarFrame) },
		{ "GamesLabel", std::make_shared<InteractiveLabel>(this->_ui->NavBarFrame, "GAMES", 12) },
		{ "StoreLabel", std::make_shared<InteractiveLabel>(this->_ui->NavBarFrame, "STORE", 12) }
	};
	return (true);
}

// Initializing Animators
bool MainWindow::_initAnimators()
{
	this->_gamesLabelAnim = std::make_shared<QPropertyAnimation>(this->_listWidgets["GamesLabel"].get(), "color");
	this->_storeLabelAnim = std::make_shared<QPropertyAnimation>(this->_listWidgets["StoreLabel"].get(), "color");
	return (true);
}

// Adding the Nexus logo
bool MainWindow::_displayNexusLogo()
{
	QLabel *logo = dynamic_cast<QLabel *>(this->_listWidgets["LogoLabel"].get());

	if (!logo)
		return (false);

	QPixmap img("../ressources/images/icons/nexuslogo.png");

	logo->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	logo->setPixmap(img.scaled(160, 90, Qt::KeepAspectRatio));
	logo->setGeometry(8, 0, 160, 90);
	return (true);
}

// Adding InteractiveLabels into the Navbar
bool MainWindow::_displayInteractiveLabels()
{
	InteractiveLabel *gamesLabel = dynamic_cast<InteractiveLabel *>(this->_listWidgets["GamesLabel"].get());
	InteractiveLabel *storeLabel = dynamic_cast<InteractiveLabel *>(this->_listWidgets["StoreLabel"].get());

	if (!gamesLabel || !storeLabel)
		return (false);

	this->_listWidgets["GamesLabel"]->setGeometry(230, 35, 60, 26);
	gamesLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	gamesLabel->setColor(QColor(255, 255, 255, 140));
	this->_listWidgets["StoreLabel"]->setGeometry(320, 35, 60, 26);
	storeLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	storeLabel->setColor(QColor(255, 255, 255, 140));
	return (true);
}

// Load items in the GamesList
bool MainWindow::_loadGamesList()
{
	// When crawling the games directory, call this function for each game that was found :
	this->addGameToGamesList("../ressources/images/icons/rtype.png", "R-Type");
	this->addGameToGamesList("../ressources/images/icons/rtype.png", "R-Type 2");
	this->addGameToGamesList("../ressources/images/icons/rtype.png", "R-Type 3");
	this->addGameToGamesList("../ressources/images/icons/rtype.png", "R-Type 4");
	this->addGameToGamesList("../ressources/images/icons/rtype.png", "R-Type 5");
	this->addGameToGamesList("../ressources/images/icons/rtype.png", "R-Type 6");
	this->addGameToGamesList("../ressources/images/icons/rtype.png", "R-Type 7");
	return (true);
}