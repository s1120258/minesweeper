#pragma once

#include <QString>

class Cell
{
public:
	Cell();
	~Cell();

	void SetMine();
	bool IsMine() const;

	void SetNumAdjacentMines(int count);
	int GetNumAdjacentMines() const;

	void Reveal();
	bool IsRevealed() const;

	void ToggleFlag();
	bool IsFlagged() const;

	QString GetStateText() const;

private:
	bool isMine;
	int numAdjacentMines;

	bool isRevealed;
	bool isFlagged;
};

