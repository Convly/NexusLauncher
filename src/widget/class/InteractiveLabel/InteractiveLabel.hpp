#ifndef INTERACTIVELABEL_HPP
#define INTERACTIVELABEL_HPP

#include <QLabel>
#include <QString>
#include <QFont>
#include <QColor>

class InteractiveLabel : public QLabel {
	Q_OBJECT
	Q_PROPERTY(QColor color READ getColor WRITE setColor)

public:
	InteractiveLabel(QWidget *parent, std::string const& label, int const fontSize);
	~InteractiveLabel();

	void	setColor(QColor color);
	QColor	getColor();

signals:
	void	clicked();
	void	entered();
	void	left();

protected:
	void	mousePressEvent(QMouseEvent *);
	void	enterEvent(QEvent *);
	void	leaveEvent(QEvent *);

};

#endif // INTERACTIVELABEL_HPP