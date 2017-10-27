#include "ngamewidgetitem.h"
#include "ui_ngamewidgetitem.h"

NGameWidgetItem::NGameWidgetItem(QWidget *parent, std::string const& picPath, std::string const& gameName) :
    QWidget(parent),
	_ui(std::make_shared<Ui::NGameWidgetItem>())
{
    this->_ui->setupUi(this);

	this->_ui->GamePicture->setStyleSheet("QLabel {background-color: rgba(0, 0, 0, 0);}");
	this->_ui->GameName->setStyleSheet("QLabel {background-color: rgba(0, 0, 0, 0); color: rgb(255, 255, 255)}");

	QPixmap img(QString::fromStdString(picPath));
	if (img.isNull())
		img.load(QString::fromStdString("../ressources/images/icons/defaultgamelogo.png"));
	this->_ui->GamePicture->setPixmap(img.scaled(100, 100, Qt::KeepAspectRatio));

	this->_ui->GameName->setText(QString::fromStdString(gameName));
}

NGameWidgetItem::~NGameWidgetItem()
{

}