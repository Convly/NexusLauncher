#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <unordered_map>
#include <string>
#include <QPropertyAnimation>
#include "InteractiveLabel.hpp"

namespace Ui {
	class MainWindow;
}

namespace nx {
	class UISystem;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent, nx::UISystem &uiSystem);
    ~MainWindow();

public slots:
	void GamesLabelClicked();
	void StoreLabelClicked();
	void GamesLabelEntered();
	void StoreLabelEntered();
	void GamesLabelLeft();
	void StoreLabelLeft();

private:
	std::shared_ptr<Ui::MainWindow>								_ui;
	std::unordered_map<std::string, std::shared_ptr<QWidget>>	_listWidgets;
	nx::UISystem												&_uiSystem;
	std::shared_ptr<QPropertyAnimation>							_gamesLabelAnim;
	std::shared_ptr<QPropertyAnimation>							_storeLabelAnim;
};

#endif // MAINWINDOW_H
