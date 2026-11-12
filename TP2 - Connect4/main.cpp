#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

void WelcomeMessage();
void ChoosingFirstPlayer(bool& playerTurn);
bool GameOn();
void GameGrid(char grid[6][7]);
void ColumnChoice(bool& playerTurn, int& columnChoice);
void TokenPlacement(bool playerTurn, int& columnChoice, int& row, char grid[6][7]);
bool WinValidation(int& columnChoice, int& row, char grid[6][7], char token);
void GameEnd(bool playerTurn);

void main()
{
	GameOn();
}

/// <summary>
/// Start of the game until someone wins.
/// </summary>
/// <returns>The state of the game</returns>
bool GameOn()
{
	char grid[6][7] = { {'1', '2', '3', '4', '5', '6', '7'},
						{' ', ' ', ' ', ' ', ' ', ' ', ' '},
						{' ', ' ', ' ', ' ', ' ', ' ', ' '},
						{' ', ' ', ' ', ' ', ' ', ' ', ' '},
						{' ', ' ', ' ', ' ', ' ', ' ', ' '},
						{' ', ' ', ' ', ' ', ' ', ' ', ' '} };
	int columnChoice;
	int columnStack[7] = { 5, 5, 5, 5, 5, 5, 5 };
	bool playerTurn = true;
	

	WelcomeMessage();

	system("pause");
	system("cls");

	ChoosingFirstPlayer(playerTurn);

	system("pause");
	system("cls");

	GameGrid(grid);
	while (true)
	{
		do
		{
			ColumnChoice(playerTurn, columnChoice);
		} while (columnStack[columnChoice] == 0);
		
		int row = columnStack[columnChoice];
		TokenPlacement(playerTurn, columnChoice, columnStack[columnChoice], grid);

		GameGrid(grid);

		if (WinValidation(columnChoice, row, grid, playerTurn ? 'X' : 'O'))
		{
			GameEnd(playerTurn);
			return false;
		}

		playerTurn = !playerTurn;
	}
}

void WelcomeMessage()
{
	cout << "Bienvenue au jeu de Connect4 !" << endl;
	cout << "Le but du jeu est de faire une ligne, colonne ou diagonale de 4 jetons identiques." << endl;
	cout << "Tirons le premier joueur au hasard !" << endl;
}
/// <summary>
/// Random one or two to chose first player.
/// </summary>
/// <param name="playerTurn">player turn == true, CPU turn == false</param>
void ChoosingFirstPlayer(bool& playerTurn)
{
	srand(time(0));
	int firstPlayer = rand() % 2;

	if (firstPlayer == 0)
	{
		cout << "Vous jouez en premier !" << endl;
		playerTurn = true;
	}
	else
	{
		cout << "L'Ordi joue en premier ! " << endl;
		playerTurn = false;
	}
}

/// <summary>
/// The grid of the game with tokens inside.
/// </summary>
/// <param name="grid">grid[row][column]</param>
void GameGrid(char grid[6][7])
{
	system("cls");
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (j == 0)
			{
				cout << "| " << grid[i][j] << " | ";
			}				
			else if (j == 6)
			{
				cout << grid[i][j] << " |" << endl;
			}				
			else
			{
				cout << grid[i][j] << " | ";
			}
		}
		cout << "-----------------------------" << endl;
	}
}
/// <summary>
/// Choose a number between 1 and 7 (the column).
/// </summary>
/// <param name="playerTurn">player turn == true, CPU turn == false</param>
/// <param name="row">the row choice of the column stack grid</param>
/// <param name="columnChoice">choice of column</param>
void ColumnChoice(bool& playerTurn, int& columnChoice)
{
	if (playerTurn)
	{
		do
		{
			cout << "Entrez un choix de colonne entre 1 et 7: ";
			cin >> columnChoice;
			cout << endl;
		} while (columnChoice < 1 || columnChoice > 7);
	}
	else
	{
			columnChoice = rand() % 7 + 1;
	}

	columnChoice--;
}
/// <summary>
/// Place the token with X for player and O for CPU.
/// </summary>
/// <param name="playerTurn">player turn == true, CPU turn == false</param>
/// <param name="columnChoice">Choice of column</param>
/// <param name="row">the row choice of the column stack grid</param>
/// <param name="grid">grid[row][column]</param>
void TokenPlacement(bool playerTurn, int& columnChoice, int& row, char grid[6][7])
{
	grid[row][columnChoice] = playerTurn ? 'X' : 'O';
	row--;
}
/// <summary>
/// Check the validation of 4 of the same token for left, right, down, and the four diagonals.
/// </summary>
/// <param name="playerTurn">player turn == true, CPU turn == false</param>
/// <param name="columnChoice">Choice of column</param>
/// <param name="row">the row choice of the column stack grid</param>
/// <param name="grid">grid">grid[row][column]</param>
/// <returns>true for a win (4 in a row)</returns>
bool WinValidation(int& columnChoice, int& row, char grid[6][7], char token)
{	
	int tokenCount = 1;

	for (int i = row + 1; i <= 5; i++)
	{
		if (grid[i][columnChoice] == token)
		{
			tokenCount++;
		}
		else
		{
			break;
		}

		if (tokenCount == 4)
		{
			return true;
		}
	}

	tokenCount = 1;

	for (int i = columnChoice + 1; i <= 5; i++)
	{
		if (grid[row][i] == token)
		{
			tokenCount++;
		}
		else
		{
			break;
		}

		if (tokenCount == 4)
		{
			return true;
		}
	}
	for (int i = columnChoice - 1; i >= 0; i--)
	{
		if (grid[row][i] == token)
		{
			tokenCount++;
		}
		else
		{
			break;
		}

		if (tokenCount == 4)
		{
			return true;
		}
	}

	tokenCount = 1;
	/*Diagonal up, right*/
	for (int i = columnChoice + 1, j = row + 1; i <= 6 && j <= 5; i++, j++)
	{
		if (grid[j][i] == token)
		{
			tokenCount++;
		}
		else
		{
			break;
		}

		if (tokenCount == 4)
		{
			return true;
		}
	}
	/*Diagonal down, left*/
	for (int i = columnChoice - 1, j = row - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (grid[j][i] == token)
		{
			tokenCount++;
		}
		else
		{
			break;
		}

		if (tokenCount == 4)
		{
			return true;
		}
	}

	tokenCount = 1;
	/*Diagonal down, right*/
	for (int i = columnChoice + 1, j = row - 1; i <= 6 && j >= 0; i++, j--)
	{
		if (grid[j][i] == token)
		{
			tokenCount++;
		}
		else
		{
			break;
		}

		if (tokenCount == 4)
		{
			return true;
		}
	}
	/*Diagonal up, left*/
	for (int i = columnChoice - 1, j = row + 1; i >= 0 && j <= 5; i--, j++)
	{
		if (grid[j][i] == token)
		{
			tokenCount++;
		}
		else
		{
			break;
		}

		if (tokenCount == 4)
		{
			return true;
		}
	}

	return false;
}
/// <summary>
/// End message and winner.
/// </summary>
/// <param name="playerWin">playerWin == true, the player wins</param>
void GameEnd(bool playerTurn)
{
	if (playerTurn)
	{
		cout << "Felicitation ! Vous avez gagne !" << endl;
	}
	else
	{
		cout << "L'Ordi vous a vaincu..." << endl;
	}
	system("pause");
}