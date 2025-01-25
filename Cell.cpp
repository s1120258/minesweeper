#include "Cell.h"

namespace {
	const QString MINE_TEXT = "X";
	const QString FLAG_TEXT = "F";
}

Cell::Cell() : isMine(false), numAdjacentMines(0), isRevealed(false), isFlagged(false)
{
}

Cell::~Cell()
{
}

void Cell::SetMine()
{
	isMine = true;
}

bool Cell::IsMine() const
{
	return isMine;
}

void Cell::SetNumAdjacentMines(int count)
{
	numAdjacentMines += count;
}

int Cell::GetNumAdjacentMines() const
{
	return numAdjacentMines;
}

void Cell::Reveal()
{
	isRevealed = true;
}

bool Cell::IsRevealed() const
{
	return isRevealed;
}

void Cell::ToggleFlag()
{
	isFlagged = !isFlagged;
}

bool Cell::IsFlagged() const
{
	return isFlagged;
}

QString Cell::GetStateText() const
{
	if (isRevealed)
	{
		return isMine ? MINE_TEXT : QString::number(numAdjacentMines);
	}
	return isFlagged ? FLAG_TEXT : QString();
}
