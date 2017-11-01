#include "mainwindow.h"
#include "UISystem.hpp"
#include "GamesSystem.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, nx::UISystem &uiSystem) :
	QMainWindow(parent, Qt::FramelessWindowHint),
	_ui(std::make_shared<Ui::MainWindow>()),
	_uiSystem(uiSystem),
	_timer(std::make_shared<QTimer>(this)),
	_isClosing(false)
{
	this->_ui->setupUi(this);

	if (!this->_init())
	{
		// Throw an error;
	}

	QSizeGrip *grip = new QSizeGrip(this);

	this->statusBar()->hide();
	this->_ui->GameDataLayout->addWidget(grip, 0, Qt::AlignBottom | Qt::AlignRight);
	this->_ui->GamePlayButton->setStyleSheet(QString::fromStdString("QPushButton {background-color: " + nx::REDFLAT + "; color: white}"));
	this->_ui->GamePlayButton->setHidden(true);

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

	// Update every 1 second the GamesList
	this->_timer->start(1000);
	QObject::connect(this->_timer.get(), SIGNAL(timeout()), this, SLOT(UpdateGamesList()));

	// Signal functions call
	QObject::connect(this->_listWidgets["GamesLabel"].get(), SIGNAL(clicked()), this, SLOT(GamesLabelClicked()));
	QObject::connect(this->_listWidgets["GamesLabel"].get(), SIGNAL(entered()), this, SLOT(GamesLabelEntered()));
	QObject::connect(this->_listWidgets["GamesLabel"].get(), SIGNAL(left()), this, SLOT(GamesLabelLeft()));
	QObject::connect(this->_listWidgets["StoreLabel"].get(), SIGNAL(clicked()), this, SLOT(StoreLabelClicked()));
	QObject::connect(this->_listWidgets["StoreLabel"].get(), SIGNAL(entered()), this, SLOT(StoreLabelEntered()));
	QObject::connect(this->_listWidgets["StoreLabel"].get(), SIGNAL(left()), this, SLOT(StoreLabelLeft()));
	QObject::connect(this->_listWidgets["LogoClose"].get(), SIGNAL(clicked()), this, SLOT(QuitApplication()));

	QObject::connect(this->_ui->GamePlayButton, SIGNAL(clicked()), this, SLOT(GamePlayButtonClicked()));

	QObject::connect(this->_ui->GamesList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(ItemHasChanged(QListWidgetItem *, QListWidgetItem *)));
}

MainWindow::~MainWindow()
{

}

/********************\
|*  PUBLIC METHODS  *|
\********************/

// Add a NGameWidgetItem in the GamesList
bool MainWindow::addGameToGamesList(nx::GameInfos const& gameInfos)
{
	std::unordered_map<std::string, std::string> infos = gameInfos.getInfos();
	std::string path = gameInfos.getPath();

	if (this->_gameWidgetItemsList.find(path) == this->_gameWidgetItemsList.end())
	{
		this->_gameWidgetItemsList.insert({path, GameWidgetItemStruct(gameInfos.getPath(),
																		  std::make_shared<NGameWidgetItem>(this, infos["icon"], infos["title"]),
																		  std::make_shared<QListWidgetItem>(this->_ui->GamesList))});

		this->_ui->GamesList->addItem(this->_gameWidgetItemsList[path].qtItem.get());
		this->_gameWidgetItemsList[path].qtItem->setSizeHint(QSize(this->_gameWidgetItemsList[path].nxItem->sizeHint().width(), 140));
		this->_ui->GamesList->setItemWidget(this->_gameWidgetItemsList[path].qtItem.get(), this->_gameWidgetItemsList[path].nxItem.get());
		if (!this->_ui->GamesList->selectedItems().count())
		{
			this->_ui->GamesList->item(0)->setSelected(true);
			this->ItemHasChanged(this->_ui->GamesList->item(0), Q_NULLPTR);
		}
	}
	return (true);
}

// Clear the entire GamesList
bool MainWindow::clearGamesList()
{
	this->_gameWidgetItemsList.clear();
	return (true);
}

bool MainWindow::diffGamesListsData()
{
	for (auto it = this->_gameWidgetItemsList.begin(); it != this->_gameWidgetItemsList.end();)
	{
		bool missing = (std::find_if(this->_gamesFound.begin(), this->_gamesFound.end(), [&](auto i) {return i == it->second.gameInfos; }) == this->_gamesFound.end());
		if (missing)
			it = this->_gameWidgetItemsList.erase(it);
		else
			++it;
	}

	for (auto it = this->_gamesFound.begin(); it != this->_gamesFound.end(); ++it)
	{
		bool missing = (std::find_if(this->_gameWidgetItemsList.begin(), this->_gameWidgetItemsList.end(), [&](auto i) {return i.second.gameInfos == *it; }) == this->_gameWidgetItemsList.end());
		if (missing) {
			this->addGameToGamesList(*it);
		}
	}
	return (true);
}

// Moving mouse event to move the MainWindow
void MainWindow::mousePressEvent(QMouseEvent *evt)
{
	this->_oldMovingPos = (evt->localPos().y() <= 35) ? evt->globalPos() : QPointF(-1, -1);
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

const MainWindow::GameWidgetItemStruct& MainWindow::getSelectedWidget()
{
	auto selectedItem = this->_ui->GamesList->selectedItems().at(0);
	for (const auto& it : this->_gameWidgetItemsList) {
		if (it.second.qtItem.get() == selectedItem) {
			return it.second;
		}
	}
}

/***********\
|*  SLOTS  *|
\***********/

// Triggered every second
void MainWindow::UpdateGamesList()
{
	this->_gamesFound = this->_uiSystem.getGameSystem()->update();
	this->diffGamesListsData();
}

// Triggered when the GAMES label is clicked
void MainWindow::GamesLabelClicked()
{

}

// Triggered when the mouse is entering the GAMES label
void MainWindow::GamesLabelEntered()
{
	this->_gamesLabelAnim->setDuration(250);
	this->_gamesLabelAnim->setStartValue(QColor(255, 255, 255, 140));
	this->_gamesLabelAnim->setEndValue(QColor(QString::fromStdString(nx::REDFLAT)));
	this->_gamesLabelAnim->start();
	this->_listWidgets["GamesLabel"]->setCursor(Qt::PointingHandCursor);
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

// Triggered when the STORE label is clicked
void MainWindow::StoreLabelClicked()
{

}

// Triggered when the mouse is entering the STORE label
void MainWindow::StoreLabelEntered()
{
	this->_storeLabelAnim->setDuration(250);
	this->_storeLabelAnim->setStartValue(QColor(255, 255, 255, 140));
	this->_storeLabelAnim->setEndValue(QColor(QString::fromStdString(nx::REDFLAT)));
	this->_storeLabelAnim->start();
	this->_listWidgets["StoreLabel"]->setCursor(Qt::PointingHandCursor);
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

// Triggered when the play button is clicked
void MainWindow::GamePlayButtonClicked()
{
	auto& item = this->getSelectedWidget();

	QString cmd(QString::fromStdString(fs::path(item.gameInfos.getPath()).parent_path().string() + "/" + item.gameInfos.getInfos().at("command") + BINARY_EXTENSION));

	std::shared_ptr<QProcess> pc = std::make_shared<QProcess>(this);
    pc->startDetached(cmd);
}


void MainWindow::ItemHasChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
	if (this->_isClosing)
		return;
	for (auto it : this->_gameWidgetItemsList)
	{
		if (it.second.qtItem.get() == current)
		{
			std::unordered_map<std::string, std::string> infos = it.second.gameInfos.getInfos();

			this->_ui->GameTitleLabel->setText(QString::fromStdString(infos["title"]));
			this->_ui->GameAuthorLabel->setText(this->_createAuthorLabelData(infos["author"]));
			QFont font(this->_ui->GameTitleLabel->font());
			font.setCapitalization(QFont::AllUppercase);
			font.setLetterSpacing(QFont::AbsoluteSpacing, 2);
			this->_ui->GameTitleLabel->setFont(font);
			this->_ui->GameUrlLabel->setText((infos["url"] != "none") ? (this->_createUrlLabelData(infos["url"])) : (QString::fromStdString("")));
			this->_ui->GameHeaderDescriptionLabel->setText(QString::fromStdString("Description:"));
			this->_ui->GameDescriptionLabel->setText(QString::fromStdString(infos["description"]));
			this->_ui->GamePlayButton->setHidden(false);
			this->_ui->GameVersionLabel->setText(QString::fromStdString("Version " + infos["version"]));
			if (QImageReader::imageFormat(QString::fromStdString(infos["cover"])).isEmpty())
				this->_ui->GameDataWidget->setStyleSheet(QString::fromStdString("#GameDataWidget {background-image: none;}"));
			else
				this->_ui->GameDataWidget->setStyleSheet(QString::fromStdString(
					"#GameDataWidget {border-image: url(" + infos["cover"] + ") 0 0 0 0 stretch stretch;}"
					"#GameDataOverlay {background-color: rgba(0, 0, 0, 0.5);}"
					"#GameDataOverlay * {background-color: rgba(0, 0, 0, 0);}"
			));
		}
	}
}

void MainWindow::QuitApplication()
{
	this->_isClosing = true;
	QApplication::quit();
}

/*********************\
|*  PRIVATE METHODS  *|
\*********************/

// Initialize everything in the MainWindow
bool MainWindow::_init()
{
	this->_initListWidgets();
	this->_initAnimators();
	if (!this->_displayNexusLogo() || !this->_displayCloseIcon() || !this->_displayInteractiveLabels())
		return (false);
	this->show();
	return (true);
}

// Initializing Navbar Widgets
bool MainWindow::_initListWidgets()
{
	this->_listWidgets = {
		{ "LogoLabel", std::make_shared<QLabel>(this->_ui->NavBarFrame) },
		{ "GamesLabel", std::make_shared<InteractiveLabel>(this->_ui->NavBarFrame, "GAMES", 12) },
		{ "StoreLabel", std::make_shared<InteractiveLabel>(this->_ui->NavBarFrame, "STORE", 12) },
		{ "LogoClose", std::make_shared<InteractiveLabel>(this) }
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
	logo->setGeometry(15, 0, 160, 90);
	return (true);
}

// Adding the Close icon
bool MainWindow::_displayCloseIcon()
{
	InteractiveLabel *logo = dynamic_cast<InteractiveLabel *>(this->_listWidgets["LogoClose"].get());

	if (!logo)
		return (false);

	QPixmap img("../ressources/images/icons/closeicon.png");

	logo->setContentsMargins(0, 10, 10, 0);
	logo->setPixmap(img);
	logo->setFixedSize(26, 100);
	logo->setAlignment(Qt::AlignRight | Qt::AlignTop);

	this->_ui->CloseLogoLayout->addWidget(logo);
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


QString	MainWindow::_createUrlLabelData(std::string const& url)
{
	return (QString::fromStdString("<html><head/><body><p>More informations on <a href=\"" + url +
								   "\"><span style=\" text-decoration: underline; color:#007af4;\">" + url +
								   "</span></a></p></body></html>"));
}

QString MainWindow::_createAuthorLabelData(std::string const& author)
{
	return (QString::fromStdString("<html><head/><body><p>By <span style=\"font-weight:600;color:#e74c3c;\">" +
									author + "</span></p></body></html>"));
}