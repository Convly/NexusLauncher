#ifndef NGAMEWIDGETITEM_H
#define NGAMEWIDGETITEM_H

#include <QWidget>
#include <memory>

namespace Ui {
	class NGameWidgetItem;
}

namespace nx {
	class UISystem;
}

class NGameWidgetItem : public QWidget
{
    Q_OBJECT

public:
	explicit NGameWidgetItem(QWidget *parent, std::string const& picPath, std::string const& gameName);
	~NGameWidgetItem();

private:
	std::shared_ptr<Ui::NGameWidgetItem>		_ui;
};

#endif // NGAMEWIDGETITEM_H
