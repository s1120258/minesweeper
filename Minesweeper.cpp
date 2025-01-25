#include "Minesweeper.h"
#include "ui_Minesweeper.h"
#include "GameBoard.h"
#include "CustomButton.h"
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

namespace
{
	const int NUM_ROWS = 10;
	const int NUM_COLS = 10;
	const int NUM_MINES = 10;
	const int BUTTON_SIZE = 30;
	const int CONTENT_MARGIN = 20;
}

Minesweeper::Minesweeper(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MinesweeperClass())
    , gameBoard(new GameBoard(this))
    , gridLayout(new QGridLayout)
{
    ui->setupUi(this);
    SetupGameBoard();
}

Minesweeper::~Minesweeper()
{
    delete ui;
	delete gameBoard;
	delete gridLayout;
}

void Minesweeper::SetupGameBoard()
{   
	gridLayout->setContentsMargins(CONTENT_MARGIN, CONTENT_MARGIN, CONTENT_MARGIN, CONTENT_MARGIN);
    gridLayout->setSpacing(0);

	gameBoard->Initialize(NUM_ROWS, NUM_COLS, NUM_MINES);

    for (int row = 0; row < gameBoard->GetNumRows(); ++row)
    {
        for (int col = 0; col < gameBoard->GetNumRows(); ++col)
        {
            CustomButton* cellBtn = new CustomButton(this);
            cellBtn->setFixedSize(BUTTON_SIZE, BUTTON_SIZE);
            gridLayout->addWidget(cellBtn, row, col);

            // Connect button click signal to a slot for handling cell clicks
            connect(cellBtn, &QPushButton::clicked, this, [this, row, col]() { handleCellClick(row, col); });
			connect(cellBtn, &CustomButton::rightClicked, this, [this, row, col]() { handleCellRightClick(row, col); });
        }
    }

    // Create a layout for the reset button
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    QPushButton* resetBtn = new QPushButton("Reset", this);
    buttonLayout->addStretch();
    buttonLayout->addWidget(resetBtn);
    buttonLayout->addStretch();

    connect(resetBtn, &QPushButton::clicked, this, &Minesweeper::handleResetButtonClick);

    // Create a main layout to stack the game board and the reset button
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(buttonLayout);

	ui->centralWidget->setLayout(mainLayout);
	setCentralWidget(ui->centralWidget);

    int windowWidth = gameBoard->GetNumCols() * BUTTON_SIZE + 2 * CONTENT_MARGIN;
    int windowHeight = gameBoard->GetNumRows() * BUTTON_SIZE + resetBtn->height() + 2 * CONTENT_MARGIN;
    setFixedSize(windowWidth, windowHeight);
}

void Minesweeper::handleCellClick(int row, int col)
{
    qDebug() << "Cell clicked at" << row << col;
    gameBoard->FlipCell(row, col);
    UpdateCellText(row, col, gameBoard->GetCellText(row, col));
    if (gameBoard->GetGameState() != GameState::kInProgress) {
		UpdateAllText();
		QString message = gameBoard->GetGameState() == GameState::kGameOver ? "Game Over!" : "You Win!";
		QMessageBox::information(this, "Minesweeper", message);
    }
}

void Minesweeper::handleCellRightClick(int row, int col)
{
	qDebug() << "Cell right clicked at" << row << col;
	gameBoard->ToggleFlag(row, col);
    UpdateCellText(row, col, gameBoard->GetCellText(row, col));
}

void Minesweeper::UpdateCellText(int row, int col, const QString& text)
{
	QPushButton* cellBtn = qobject_cast<QPushButton*>(gridLayout->itemAtPosition(row, col)->widget());
	cellBtn->setText(QString(text));
}

void Minesweeper::UpdateAllText()
{
	for (int row = 0; row < gameBoard->GetNumRows(); ++row)
	{
		for (int col = 0; col < gameBoard->GetNumCols(); ++col)
		{
			UpdateCellText(row, col, gameBoard->GetCellText(row, col));
		}
	}
}

void Minesweeper::handleResetButtonClick()
{
    qDebug() << "Refresh button clicked";
    ResetGame();
}

void Minesweeper::ResetGame()
{
    gameBoard->Initialize(NUM_ROWS, NUM_COLS, NUM_MINES);
	UpdateAllText();
}
