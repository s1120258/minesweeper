#include "CustomButton.h"

CustomButton::CustomButton(QWidget* parent)
    : QPushButton(parent)
{
}

void CustomButton::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        emit rightClicked();
    }
    else
    {
        QPushButton::mousePressEvent(event);
    }
}