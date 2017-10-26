#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <unordered_map>
#include <string>
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QTimer>
#include "ui_mainwindow.h"
#include "InteractiveLabel.hpp"
#include "ngamewidgetitem.h"

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
		GameWidgetItemStruct(std::shared_ptr<NGameWidgetItem> nItem, std::shared_ptr<QListWidgetItem> qItem) :
			nxItem(nItem), qtItem(qItem) {}
		~GameWidgetItemStruct() {}

		std::shared_ptr<NGameWidgetItem>	nxItem;
		std::shared_ptr<QListWidgetItem>	qtItem;
	};

public:
    explicit MainWindow(QWidget *parent, nx::UISystem &uiSystem);
    ~MainWindow();

	bool addGameToGamesList(std::string const& picPath, std::string const& gameName);
	bool removeGameFromGamesList(std::string const& gameName);
	bool clearGamesList();

	void mousePressEvent(QMouseEvent * evt);
	void mouseMoveEvent(QMouseEvent * evt);

private:
	bool _initListWidgets();
	bool _initAnimators();
	bool _displayNexusLogo();
	bool _displayCloseIcon();
	bool _displayInteractiveLabels();
	bool _loadGamesList();

	bool _init();

public slots:
	void UpdateGamesList();
	void GamesLabelEntered();
	void GamesLabelClicked();
	void GamesLabelLeft();
	void StoreLabelClicked();
	void StoreLabelEntered();
	void StoreLabelLeft();

private:
	std::shared_ptr<Ui::MainWindow>										_ui;
	nx::UISystem														&_uiSystem;
	std::unordered_map<std::string, std::shared_ptr<QWidget>>			_listWidgets;
	std::shared_ptr<QPropertyAnimation>									_gamesLabelAnim;
	std::shared_ptr<QPropertyAnimation>									_storeLabelAnim;
	std::unordered_map<std::string, GameWidgetItemStruct>				_gameWidgetItemsList;

	QPointF																_oldMovingPos;
	std::shared_ptr<QTimer>												_timer;
};

#endif // MAINWINDOW_H
