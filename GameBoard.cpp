#include "GameBoard.h"
#include "Cell.h"
#include <QDebug>

GameBoard::GameBoard(QWidget* parent) : numRows(0), numCols(0), numMines(0), numRevealed(0), gameState(GameState::kInProgress)
{
    std::srand(std::time(nullptr)); // Seed the random number generator
}

GameBoard::~GameBoard()
{
}

void GameBoard::Initialize(int rows, int cols, int mines)
{
	numRows = rows;
	numCols = cols;
	numMines = mines;
	numRevealed = 0;
	gameState = GameState::kInProgress;

	cells.clear();
	cells.resize(rows, std::vector<Cell>(cols));

	PlaceMines();
	CalculateAdjacentMines();
}

void GameBoard::FlipCell(int row, int col)
{
	if (cells[row][col].IsMine())
	{
		qDebug() << "Game over!";
		gameState = GameState::kGameOver;
		RevealAllCells();
	}
	else
	{
		cells[row][col].Reveal();
		++numRevealed;
		if (numRevealed == numRows * numCols - numMines)
		{
			qDebug() << "Game completed!";
			gameState = GameState::kCompleted;
			RevealAllCells();
		}
	}
}

void GameBoard::ToggleFlag(int row, int col)
{
	cells[row][col].ToggleFlag();
}

QString GameBoard::GetCellText(int row, int col) const
{
    return cells[row][col].GetStateText();
}

void GameBoard::PlaceMines()
{
    int placedMines = 0;
    while (placedMines < numMines)
    {
        int row = std::rand() % numRows;
        int col = std::rand() % numCols;

        if (!cells[row][col].IsMine())
        {
            cells[row][col].SetMine();
            placedMines++;
        }
    }
}

void GameBoard::CalculateAdjacentMines()
{
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            if (cells[row][col].IsMine())
            {
                continue;
            }

            int mineCount = 0;
            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    int newRow = row + i;
                    int newCol = col + j;

                    if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols && cells[newRow][newCol].IsMine())
                    {
                        ++mineCount;
                    }
                }
            }
            cells[row][col].SetNumAdjacentMines(mineCount);
        }
    }
}

void GameBoard::RevealAllCells()
{
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            cells[row][col].Reveal();
        }
    }
}
