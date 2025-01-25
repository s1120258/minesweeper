#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <QString>

class ui_Minesweeper;
class GameBoard;

QT_BEGIN_NAMESPACE
namespace Ui { class MinesweeperClass; };
QT_END_NAMESPACE

class Minesweeper : public QMainWindow
{
    Q_OBJECT

public:
    Minesweeper(QWidget *parent = nullptr);
    ~Minesweeper();

private slots:
    void handleCellClick(int row, int col);
    void handleCellRightClick(int row, int col);
	void handleResetButtonClick();

private:
    Ui::MinesweeperClass *ui;
	GameBoard* gameBoard;
	QGridLayout* gridLayout;

	void SetupGameBoard();
    void UpdateCellText(int row, int col, const QString& text);
    void UpdateAllText();
	void ResetGame();
};
