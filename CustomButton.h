#pragma once

#include <QPushButton>
#include <QMouseEvent>

class CustomButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CustomButton(QWidget* parent = nullptr);

signals:
    void rightClicked();

protected:
    void mousePressEvent(QMouseEvent* event) override;
};
