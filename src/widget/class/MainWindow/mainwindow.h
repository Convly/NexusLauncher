#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <unordered_map>
#include <string>
#include <experimental/filesystem>
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QTimer>
#include <QListWidget>
#include <QSizeGrip>
#include <QProcess>
#include <QImageReader>
#include <QFontDatabase>
#include "GameInfos.hpp"
#include "ui_mainwindow.h"
#include "InteractiveLabel.hpp"
#include "ngamewidgetitem.h"

#include "NoSelectedWidgetException.hpp"

namespace fs = std::experimental::filesystem;

#if defined(__GNUC__) || defined(__GNUG__)
	static const std::string BINARY_EXTENSION = "";
#elif defined(_MSC_VER)
	static const std::string BINARY_EXTENSION = ".exe";
#endif

namespace Ui {
	class MainWindow;
}

namespace nx {
	class UISystem;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

	struct GameWidgetItemStruct
	{
		GameWidgetItemStruct() : nxItem(nullptr), qtItem(nullptr) {}
		GameWidgetItemStruct(std::string const& cfgPath) : gameInfos(cfgPath), nxItem(nullptr), qtItem(nullptr) {}
		GameWidgetItemStruct(std::string const& cfgPath, std::shared_ptr<NGameWidgetItem> nItem, std::shared_ptr<QListWidgetItem> qItem)
		: gameInfos(cfgPath), nxItem(nItem), qtItem(qItem) {}
		~GameWidgetItemStruct() {}

		nx::GameInfos						gameInfos;
		std::shared_ptr<NGameWidgetItem>	nxItem;
		std::shared_ptr<QListWidgetItem>	qtItem;
	};

public:
    explicit MainWindow(QWidget *parent, nx::UISystem &uiSystem);
    ~MainWindow();

	bool addGameToGamesList(nx::GameInfos const& gameInfos);
	bool clearGamesList();
	bool diffGamesListsData();

	void mousePressEvent(QMouseEvent * evt);
	void mouseMoveEvent(QMouseEvent * evt);
	const MainWindow::GameWidgetItemStruct& getSelectedWidget(void);
	void updateGameData(const std::unordered_map<std::string, std::string>& infos);	
	
private:
	bool	_initListWidgets();
	bool	_initAnimators();
	bool	_displayNexusLogo();
	bool	_displayCloseIcon();
	bool	_displayInteractiveLabels();

	bool	_init();

	QString	_createUrlLabelData(std::string const& url);
	QString	_createAuthorLabelData(std::string const& author);

public slots:
	void UpdateGamesList();
	void GamesLabelEntered();
	void GamesLabelClicked();
	void GamesLabelLeft();
	void StoreLabelClicked();
	void StoreLabelEntered();
	void StoreLabelLeft();
	void CloseLabelEntered();
	void CloseLabelLeft();
	void ItemHasChanged(QListWidgetItem *current, QListWidgetItem *previous);
	void QuitApplication();
	void GamePlayButtonClicked();

private:
	std::shared_ptr<Ui::MainWindow>										_ui;
	nx::UISystem														&_uiSystem;
	std::unordered_map<std::string, std::shared_ptr<QWidget>>			_listWidgets;
	std::shared_ptr<QPropertyAnimation>									_gamesLabelAnim;
	std::shared_ptr<QPropertyAnimation>									_storeLabelAnim;
	std::shared_ptr<QPropertyAnimation>									_closeLabelAnim;
	std::unordered_map<std::string, GameWidgetItemStruct>				_gameWidgetItemsList;
	std::vector<nx::GameInfos>											_gamesFound;

	QPointF																_oldMovingPos;
	std::shared_ptr<QTimer>												_timer;
	bool																_isClosing;
};

#endif // MAINWINDOW_H
