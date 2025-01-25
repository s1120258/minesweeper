#pragma once

#include <QObject>
#include <QString>
#include <vector>

class Cell;

enum class GameState
{
	kInProgress,
	kGameOver,
	kCompleted
};

class GameBoard : public QObject
{
	Q_OBJECT

public:
	GameBoard(QWidget* parent = nullptr);
	~GameBoard();

	void Initialize(int rows, int cols, int mines);

	void FlipCell(int row, int col);
	void ToggleFlag(int row, int col);
	QString GetCellText(int row, int col) const;

	int GetNumRows() const { return numRows; }
	int GetNumCols() const { return numCols; }
	int GetNumMines() const { return numMines; }
	GameState GetGameState() const { return gameState; }

private:
	std::vector<std::vector<Cell>> cells;
	int numRows;
	int numCols;
	int numMines;
	int numRevealed;
	GameState gameState;

	void PlaceMines();
	void CalculateAdjacentMines();

	void RevealAllCells();
};

