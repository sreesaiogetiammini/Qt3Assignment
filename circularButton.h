#ifndef CIRCULARBUTTON_H
#define CIRCULARBUTTON_H
#include<QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QRectF>
#include <QWidget>

class CircleButton : public QPushButton
{
public:
    CircleButton(QWidget* parent = nullptr) : QPushButton(parent) {}

protected:
    void paintEvent(QPaintEvent* event) override
    {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        // Draw the circle
        QRect circleRect = QRect(0, 0, width() - 1, height() - 1);
        painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
        painter.setPen(QPen(Qt::black, 2));
        painter.drawEllipse(circleRect);

        // Draw the button inside the circle
        painter.setPen(Qt::NoPen);
        QIcon buttonIcon = QIcon(icon());
        QPixmap buttonPixmap = buttonIcon.pixmap(circleRect.size());
        painter.drawPixmap(circleRect.adjusted(10, 10, -10, -10), buttonPixmap);
    }
};

#endif // CIRCULARBUTTON_H
