#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

void PrintTitle();
void PrintBoard(std::vector<char>);
void PlayGame();
void PlayAgainstAI();

bool CalculateWinner(std::vector<char>, int, bool);

int GetRandomNumberInt(int);
int DoAiLogic(std::vector<char>, int);

int main()
{
	srand(static_cast<unsigned int> (time(nullptr)));
	bool playing = true;
	char playerChoice = ' ';
	bool invalidChoice = false;

	// Loops until the player chooses to quit the game
	do
	{
		PrintTitle();
		std::cin >> playerChoice;
		std::cout << std::endl;

		switch (playerChoice)
		{
		case '1':
			// Starts player vs player
			PlayGame();
			invalidChoice = false;
			break;
		case '2':
			// Starts player vs ai
			PlayAgainstAI();
			invalidChoice = false;
			break;
		case '3':
			// Exits the loop
			playing = false;
			invalidChoice = false;
			break;
		default:
			std::cout << "Invalid choice... try again" << std::endl;
			invalidChoice = true;
			break;
		}

		if (invalidChoice == false && playing == true)
		{
			// Asks player if he/she wants to continue to play, loops until it gets a valid choice
			do
			{
				std::cout << "Do you want to play again? (y for yes n for no). ";
				std::cin >> playerChoice;

				switch (tolower(playerChoice))
				{
				case 'y':
					playing = true;
					invalidChoice = false;
					break;
				case 'n':
					playing = false;
					invalidChoice = false;
					break;
				default:
					std::cout << "Invalid input... try again." << std::endl;
					invalidChoice = true;
					break;
				}
				std::cout << std::endl;
			} while (invalidChoice == true);
		}
	} while (playing);
}

// Game loop for player vs player, loops until someone wins or it's a draw
void PlayGame()
{
	bool gameWon = false;
	std::vector<char> tiles{ '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	int playerInput = ' ';
	int turn = 0;
	bool validInput = true;

	do
	{
		PrintBoard(tiles);
		std::cout << "Player " << (turn % 2) + 1 << " - Write a number from 1 to 9: ";
		std::cin >> playerInput;

		if (tiles.at(playerInput - 1) != 'X' && tiles.at(playerInput - 1) != 'O')
		{
			if ((turn % 2) + 1 == 1)
			{
				tiles.at(playerInput - 1) = 'X';
				validInput = true;
			}
			else
			{
				tiles.at(playerInput - 1) = 'O';
				validInput = true;
			}
		}
		else
		{
			std::cout << "A player has already set a piece there." << std::endl;
			validInput = false;
		}

		gameWon = CalculateWinner(tiles, turn, true);

		std::cout << std::endl;

		if(validInput)
			turn++;
	} while (gameWon == false);
}

// Game loop for player vs ai, loops until someone wins or it's a draw
void PlayAgainstAI()
{
	bool gameWon = false;
	std::vector<char> tiles{ '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	int playerInput = ' ';
	int turn = 0;
	bool validInput = true;
	int aiChoice = 0;

	do
	{
		PrintBoard(tiles);

		// Every other turn is the players turn
		if (turn % 2 == 0)
		{
			std::cout << "Player turn - Write a number from 1 to 9: ";
			std::cin >> playerInput;

			// If tile is not already taken, take it
			if (tiles.at(playerInput - 1) != 'X' && tiles.at(playerInput - 1) != 'O')
			{
				tiles.at(playerInput - 1) = 'X';
				validInput = true;
			}
			else
			{
				std::cout << "A player has already set a piece there." << std::endl;
				validInput = false;
			}
		}
		else
		{
			// Starts the ai logic, checking for it's next move
			aiChoice = DoAiLogic(tiles, turn);
			std::cout << "The AI chooses " << tiles.at(aiChoice) << std::endl;
			tiles[aiChoice] = 'O';
		}

		gameWon = CalculateWinner(tiles, turn, false);

		std::cout << std::endl;

		if (validInput)
			turn++;
	} while (gameWon == false);
}

// Checks if ai or player has combinations where the 'O' (check below) would lead to a win for either the player or ai
int DoAiLogic(std::vector<char> tiles, int turn)
{
	int choice = 0;
	bool validInput = false;
	// O X X
	// X X #
	// X # X
	if ((tiles.at(1) == 'O' && tiles.at(2) == 'O' && tiles.at(0) != 'O' && tiles.at(0) != 'X') || (tiles.at(4) == 'O' && tiles.at(8) == 'O' && tiles.at(0) != 'O' && tiles.at(0) != 'X')
		|| (tiles.at(3) == 'O' && tiles.at(6) == 'O' && tiles.at(0) != 'O' && tiles.at(0) != 'X') || (tiles.at(1) == 'X' && tiles.at(2) == 'X' && tiles.at(0) != 'O' && tiles.at(0) != 'X')
		|| (tiles.at(4) == 'X' && tiles.at(8) == 'X' && tiles.at(0) != 'O' && tiles.at(0) != 'X') ||  (tiles.at(3) == 'X' && tiles.at(6) == 'X' && tiles.at(0) != 'O' && tiles.at(0) != 'X'))
	{
		validInput = true;
		choice = 0;
	}
	// X O X
	// # X #
	// # X #
	else if ((tiles.at(0) == 'O' && tiles.at(2) == 'O' && tiles.at(1) != 'O' && tiles.at(1) != 'X') || (tiles.at(4) == 'O' && tiles.at(7) == 'O' && tiles.at(1) != 'O' && tiles.at(1) != 'X')
		|| (tiles.at(0) == 'X' && tiles.at(2) == 'X' && tiles.at(1) != 'O' && tiles.at(1) != 'X') || (tiles.at(4) == 'X' && tiles.at(7) == 'X' && tiles.at(1) != 'O' && tiles.at(1) != 'X'))
	{
		validInput = true;
		choice = 1;
	}
	// X X O
	// # X X
	// X # X
	else if ((tiles.at(0) == 'O' && tiles.at(1) == 'O' && tiles.at(2) != 'O' && tiles.at(2) != 'X') || (tiles.at(5) == 'O' && tiles.at(8) == 'O' && tiles.at(2) != 'O' && tiles.at(2) != 'X')
		|| (tiles.at(6) == 'O' && tiles.at(4) == 'O' && tiles.at(2) != 'O' && tiles.at(2) != 'X') || (tiles.at(0) == 'X' && tiles.at(1) == 'X' && tiles.at(2) != 'O' && tiles.at(2) != 'X')
		|| (tiles.at(5) == 'X' && tiles.at(8) == 'X' && tiles.at(2) != 'O' && tiles.at(2) != 'X') || (tiles.at(6) == 'X' && tiles.at(4) == 'X' && tiles.at(2) != 'O' && tiles.at(2) != 'X'))
	{
		validInput = true;
		choice = 2;
	}
	// X # #
	// O X X
	// X # #
	else if ((tiles.at(0) == 'O' && tiles.at(6) == 'O' && tiles.at(3) != 'O' && tiles.at(3) != 'X') || (tiles.at(4) == 'O' && tiles.at(5) == 'O' && tiles.at(3) != 'O' && tiles.at(3) != 'X')
		||(tiles.at(0) == 'X' && tiles.at(6) == 'X' && tiles.at(3) != 'O' && tiles.at(3) != 'X') || (tiles.at(4) == 'X' && tiles.at(5) == 'X' && tiles.at(3) != 'O' && tiles.at(3) != 'X'))
	{
		validInput = true;
		choice = 3;
	}
	// X X X
	// X O X
	// X X X
	else if ((tiles.at(0) == 'O' && tiles.at(8) == 'O' && tiles.at(4) != 'O' && tiles.at(4) != 'X') || (tiles.at(1) == 'O' && tiles.at(7) == 'O' && tiles.at(4) != 'O' && tiles.at(4) != 'X')
		|| (tiles.at(2) == 'O' && tiles.at(6) == 'O' && tiles.at(4) != 'O' && tiles.at(4) != 'X') || (tiles.at(3) == 'O' && tiles.at(5) == 'O' && tiles.at(4) != 'O' && tiles.at(4) != 'X')
		|| (tiles.at(0) == 'X' && tiles.at(8) == 'X' && tiles.at(4) != 'O' && tiles.at(4) != 'X') || (tiles.at(1) == 'X' && tiles.at(7) == 'X' && tiles.at(4) != 'O' && tiles.at(4) != 'X')
		|| (tiles.at(2) == 'X' && tiles.at(6) == 'X' && tiles.at(4) != 'O' && tiles.at(4) != 'X') || (tiles.at(3) == 'X' && tiles.at(5) == 'X' && tiles.at(4) != 'O' && tiles.at(4) != 'X'))
	{
		validInput = true;
		choice = 4;
	}
	// # # X
	// X X O
	// # # X
	else if ((tiles.at(2) == 'O' && tiles.at(8) == 'O' && tiles.at(5) != 'O' && tiles.at(5) != 'X') || (tiles.at(3) == 'O' && tiles.at(4) == 'O' && tiles.at(5) != 'O' && tiles.at(5) != 'X')
		|| (tiles.at(2) == 'X' && tiles.at(8) == 'X' && tiles.at(5) != 'O' && tiles.at(5) != 'X') || (tiles.at(3) == 'X' && tiles.at(4) == 'X' && tiles.at(5) != 'O' && tiles.at(5) != 'X'))
	{
		validInput = true;
		choice = 5;
	}
	// X # X
	// X X #
	// O X X
	else if ((tiles.at(0) == 'O' && tiles.at(3) == 'O' && tiles.at(6) != 'O' && tiles.at(6) != 'X') || (tiles.at(2) == 'O' && tiles.at(4) == 'O' && tiles.at(6) != 'O' && tiles.at(6) != 'X')
		|| (tiles.at(7) == 'O' && tiles.at(8) == 'O' && tiles.at(6) != 'O' && tiles.at(6) != 'X') || (tiles.at(0) == 'X' && tiles.at(3) == 'X' && tiles.at(6) != 'O' && tiles.at(6) != 'X')
		|| (tiles.at(2) == 'X' && tiles.at(4) == 'X' && tiles.at(6) != 'O' && tiles.at(6) != 'X') || (tiles.at(7) == 'X' && tiles.at(8) == 'X' && tiles.at(6) != 'O' && tiles.at(6) != 'X'))
	{
		validInput = true;
		choice = 6;
	}
	// # X #
	// # X #
	// X O X
	else if ((tiles.at(1) == 'O' && tiles.at(4) == 'O' && tiles.at(7) != 'O' && tiles.at(7) != 'X') || (tiles.at(6) == 'O' && tiles.at(8) == 'O' && tiles.at(7) != 'O' && tiles.at(7) != 'X')
		|| (tiles.at(1) == 'X' && tiles.at(4) == 'X' && tiles.at(7) != 'O' && tiles.at(7) != 'X') || (tiles.at(6) == 'X' && tiles.at(8) == 'X' && tiles.at(7) != 'O' && tiles.at(7) != 'X'))
	{
		validInput = true;
		choice = 7;
	}
	// X # X
	// # X X
	// X X O
	else if ((tiles.at(0) == 'O' && tiles.at(4) == 'O' && tiles.at(8) != 'O' && tiles.at(8) != 'X') || (tiles.at(2) == 'O' && tiles.at(5) == 'O' && tiles.at(8) != 'O' && tiles.at(8) != 'X')
		|| (tiles.at(6) == 'O' && tiles.at(7) == 'O' && tiles.at(8) != 'O' && tiles.at(8) != 'X') || (tiles.at(0) == 'X' && tiles.at(4) == 'X' && tiles.at(8) != 'O' && tiles.at(8) != 'X')
		|| (tiles.at(2) == 'X' && tiles.at(5) == 'X' && tiles.at(8) != 'O' && tiles.at(8) != 'X') || (tiles.at(6) == 'X' && tiles.at(7) == 'X' && tiles.at(8) != 'O' && tiles.at(8) != 'X'))
	{
		validInput = true;
		choice = 8;
	}
	else
	{
		do
		{
			// If center tile is taken
			if (tiles.at(4) == 'X' || tiles.at(4) == 'O')
			{
				// If first turn, take a corner tile (rand 0 = 0, rand 1 = 2, rand 2 = 4, rand 3 = 6, rand 4 = 8)
				if (turn == 1)
				{
					choice = GetRandomNumberInt(4) * 2;
				}
				// If not first turn and nothing else is possible, take a random number
				else
				{
					choice = GetRandomNumberInt(8);
				}
			}
			// If center tile is open take it
			else
			{
				choice = 4;
			}
			// Checks if the tile is already taken, if so loop til you find one that isn't taken.
			if (tiles.at(choice) != 'X' && tiles.at(choice) != 'O')
			{
				validInput = true;
			}
			else
			{
				validInput = false;
			}
		} while (validInput == false);
	}

	return choice;
}

// Checks if a player or ai has gotten one of all winning conditions or if it ends in a draw
// returns if someone has won or not, who's turn it is decides who wins
bool CalculateWinner(std::vector<char> tiles, int turn, bool mp)
{
	bool isWon = false;
	// X X X
	// # # #
	// # # #
	if (tiles.at(0) == tiles.at(1) && tiles.at(1) == tiles.at(2))
	{
		std::cout << std::endl;
		PrintBoard(tiles);
		// Checks if it is a player vs player or player vs ai
		if (mp == true)
			// if it's not ai check who's turn it was
			// (every other turn is player 1 and player 2 so I just use (turn % 2) + 1)
			// (the plus 1 is to make it 1 and 2 instead of 0 and 1)
			std::cout << "Player " << (turn % 2) + 1 << " won!" << std::endl;
		else if ((turn % 2) + 1 == 1)
			std::cout << "The player won!" << std::endl;
		else
			std::cout << "The AI won!" << std::endl;
		isWon = true;
	}
	// # # #
	// X X X
	// # # #
	else if (tiles.at(3) == tiles.at(4) && tiles.at(4) == tiles.at(5))
	{
		std::cout << std::endl;
		PrintBoard(tiles);
		// Checks if it is a player vs player or player vs ai
		if (mp == true)
			std::cout << "Player " << (turn % 2) + 1 << " won!" << std::endl;
		else if ((turn % 2) + 1 == 1)
			std::cout << "The player won!" << std::endl;
		else
			std::cout << "The AI won!" << std::endl;
		isWon = true;
	}
	// # # #
	// # # #
	// X X X
	else if (tiles.at(6) == tiles.at(7) && tiles.at(7) == tiles.at(8))
	{
		std::cout << std::endl;
		PrintBoard(tiles);
		// Checks if it is a player vs player or player vs ai
		if (mp == true)
			std::cout << "Player " << (turn % 2) + 1 << " won!" << std::endl;
		else if ((turn % 2) + 1 == 1)
			std::cout << "The player won!" << std::endl;
		else
			std::cout << "The AI won!" << std::endl;
		isWon = true;
	}
	// X # #
	// # X #
	// # # X
	else if (tiles.at(0) == tiles.at(4) && tiles.at(4) == tiles.at(8))
	{
		std::cout << std::endl;
		PrintBoard(tiles);
		// Checks if it is a player vs player or player vs ai
		if (mp == true)
			std::cout << "Player " << (turn % 2) + 1 << " won!" << std::endl;
		else if ((turn % 2) + 1 == 1)
			std::cout << "The player won!" << std::endl;
		else
			std::cout << "The AI won!" << std::endl;
		isWon = true;
	}
	// # # X
	// # X #
	// X # #
	else if (tiles.at(2) == tiles.at(4) && tiles.at(4) == tiles.at(6))
	{
		std::cout << std::endl;
		PrintBoard(tiles);
		// Checks if it is a player vs player or player vs ai
		if (mp == true)
			std::cout << "Player " << (turn % 2) + 1 << " won!" << std::endl;
		else if ((turn % 2) + 1 == 1)
			std::cout << "The player won!" << std::endl;
		else
			std::cout << "The AI won!" << std::endl;
		isWon = true;
	}
	// X # #
	// X # #
	// X # #
	else if (tiles.at(0) == tiles.at(3) && tiles.at(3) == tiles.at(6))
	{
		std::cout << std::endl;
		PrintBoard(tiles);
		// Checks if it is a player vs player or player vs ai
		if (mp == true)
			std::cout << "Player " << (turn % 2) + 1 << " won!" << std::endl;
		else if ((turn % 2) + 1 == 1)
			std::cout << "The player won!" << std::endl;
		else
			std::cout << "The AI won!" << std::endl;
		isWon = true;
	}
	// # X #
	// # X #
	// # X #
	else if (tiles.at(1) == tiles.at(4) && tiles.at(4) == tiles.at(7))
	{
		std::cout << std::endl;
		PrintBoard(tiles);
		// Checks if it is a player vs player or player vs ai
		if (mp == true)
			std::cout << "Player " << (turn % 2) + 1 << " won!" << std::endl;
		else if ((turn % 2) + 1 == 1)
			std::cout << "The player won!" << std::endl;
		else
			std::cout << "The AI won!" << std::endl;
		isWon = true;
	}
	// # # X
	// # # X
	// # # X
	else if (tiles.at(2) == tiles.at(5) && tiles.at(5) == tiles.at(8))
	{
		std::cout << std::endl;
		PrintBoard(tiles);
		// Checks if it is a player vs player or player vs ai
		if (mp == true)
			std::cout << "Player " << (turn % 2) + 1 << " won!" << std::endl;
		else if ((turn % 2) + 1 == 1)
			std::cout << "The player won!" << std::endl;
		else
			std::cout << "The AI won!" << std::endl;
		isWon = true;
	}
	else if (tiles.at(0) != '1' && tiles.at(1) != '2' && tiles.at(2) != '3' &&
			 tiles.at(3) != '4' && tiles.at(4) != '5' && tiles.at(5) != '6' &&
			 tiles.at(6) != '7' && tiles.at(7) != '8' && tiles.at(8) != '9')
	{
	std::cout << std::endl;
	PrintBoard(tiles);
		std::cout << "It's a draw!" << std::endl;
		isWon = true;
	}
	else
	{
		isWon = false;
	}


	return isWon;
}

void PrintTitle()
{
	std::cout << "***** Welcome to Tic Tac Toe! *****" << std::endl << std::endl;

	std::cout << "Do you want to play against the AI or against yourself?" << std::endl;
	std::cout << " 1. Play against your self" << std::endl;
	std::cout << " 2. Play against AI" << std::endl;
	std::cout << " 3. Quit game" << std::endl;
}

void PrintBoard(std::vector<char> tile)
{
	for (int i = 0; i < tile.size(); i++)
	{
		std::cout << " | " << tile.at(i);
		if (i % 3 == 2)
			std::cout << " |" << std::endl;
	}
	std::cout << std::endl;
}

int GetRandomNumberInt(int max)
{
	int randomNumber = rand() % max + 1;
	return randomNumber;
}