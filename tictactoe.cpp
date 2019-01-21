#include <iostream>
#include <string>
#include "console.h"

const std::string title =
" _____ _        _____            _____          \n"
"|_   _(_)      |_   _|          |_   _|         \n"
"  | |  _  ___    | | __ _  ___    | | ___   ___ \n"
"  | | | |/ __|   | |/ _` |/ __|   | |/ _ \\ / _ \\ \n"
"  | | | | (__    | | (_| | (__    | | (_) |  __/ \n"
"  \\_/ |_|\\___|   \\_/\\____|\\___|   \\_/\\___/ \\___| \n";
const std::string menu = "\n1 - Start local game\n2 - Start multiplayer game\n3 - Help\n4 - Quit\n\n";

class TicTacToe {
private:
	char board[4][4] = {{ "   " }, { "   " }, { "   " }};
	int turn;
	bool running=true; // Menu loop variable
	bool gameOver; // Game loop variable
	int inp; // Input variable
	bool debug=false; // Debug flag
	char player1 = 'X';
	char player2 = 'O';
public:
	typedef enum { in_progress = -1, tie = 0, win = 1 } gameStatus;
	void startGame() {
		// Prepares variables for game
		running = true;
		gameOver = false;
		turn = 1;
		std::cin.ignore();
		debugMsg("Resetting board...");
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				board[i][j] = ' ';
			}
		}
	}
	void printBoard(bool clear = true, bool positions=true, int spaces=0) {
		if (clear == true) {
			Console::clear();
		}
		int pos = 1;
		bool first = true;
		for (int i = 0; i < 3; ++i) {
			// Rows
			for (int j = 0; j < 3; ++j) {
				// Columns
				if (positions) {
					if (first) {
						// Print above positions only once
						std::cout << std::string(spaces, ' ') << "0   1   2   3\n\n";
						first = false;
					}
					if (j == 0) {
						// Print position before every row
						std::cout << pos << "  ";
						++pos;
					}
				}
				std::cout << std::string(spaces, ' ') << " " << board[i][j];
				if (j < 2) {
					std::cout << " |";
				}
			}
			std::cout << "\n";
			if (i < 2) {
				std::cout << "   " << std::string(spaces, ' ') << std::string(11, '-');
				std::cout << "\n";
			}
		}
		std::cout << "\n";
	}
	void printMenu(const std::string &title, const std::string &menu) { std::cout << title << menu; }
	void input(char symbol='>') {
		char input;
		std::cout << symbol << ' ';
		std::cin >> inp;
	}
	bool move(int row, int column, char player) {
		--row;
		--column;
		if (board[row][column] == ' ') {
			// Valid move
			board[row][column] = player;
			return true;
		}
		else {
			// Invalid move
			std::cout << "\nInvalid move\n";
			return false;
		}
	}
	void debugMsg(std::string msg) {
		if (debug == true) {
			std::cout << "\nDEBUG: " << msg << "\n";
		}
		return;
	}
	gameStatus checkWin(char player) {
		// Checks win conditions, returns the player model of the winner
		debugMsg("Checking win...");
		
		// Horizontal win
		for (int i = 0; i < 3; ++i) {
			// Rows
			int x = 0;
			int y = i;
			if (board[y][x] == player && board[y][x + 1] == player && board[y][x + 2] == player) {
				debugMsg("HORIZONTAL WIN DETECTED");
				return win;
			}
		}
		// Vertical win
		for (int i = 0; i < 3; ++i) {
			// Rows
			int y = i;
			int x;
			for (int j = 0; j < 3; ++j) {
				x = j;
				if (board[y][x] == player && board[y - 1][x] == player && board[y - 2][x] == player) {
					debugMsg("VERTICAL WIN DETECTED");
					return win;
				}
			}
		}

		// Diagonal win
		for (int i = 0; i < 3; ++i) {
			// Rows
			int y = i;
			int x;
			for (int j = 0; j < 3; ++j) {
				x = j;
				if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[2][0] == player && board[1][1] == player && board[0][2] == player)) {
					debugMsg("DIAGONAL WIN DETECTED");
					return win;
				}
			}
		}

		// Tie
		if (turn >= 9) {
			return tie;
		}

		return in_progress;
	}
	char getPlayer(int playerNum) {
		// Returns player model
		if (playerNum == 1) { return player1; }
		else if (playerNum == 2) { return player2; }
		else { std::cout << "ERROR: Invalid player number in function \"getPlayer\""; return 'E'; }
	}
	void timer(std::string msg, int seconds) {
		while (seconds >= 0) {
			std::cout << "\r" << msg << seconds;
			Sleep(1000);
			if (--seconds <= 0) {
				std::cout << "\r\r" << std::string(std::size(msg)+1, ' ') << "\r";
			}
		}
	}
	void endGame(std::string title, std::string menu) {
		timer("Quitting in... ", 5);
		std::cout << "\n";
		Console::clear();
		printMenu(title, menu);
	}
	void nextTurn() { ++turn; }
	int getInput() { return inp; }
	int getTurn() { return turn; }
	bool isRunning() { return running; }
	bool isOver() { return gameOver; }
	bool getDebug() { return debug; }
};

int main(void) {
	TicTacToe game;
	game.printMenu(title, menu);
	while (game.isRunning()) {
		game.input();
		if (game.getInput() == 1) {
			// Start local game
			game.startGame();
			int pturn = 1;
			while (!game.isOver()) {
				game.printBoard(true);
				std::cout << "\nPlayer " << pturn << ", enter the number of the row and column (11-33):";
				game.input(' ');
				if (game.getInput() >= 11 && game.getInput() <= 33 && !std::cin.fail()) {
					// Valid input
					int row = game.getInput() / 10;
					int column = game.getInput() % 10;
					if (game.getDebug()) { std::cout << "ROW: " << row << " | COLUMN: " << column << "\n"; }
					char p;
					int pnum;
					if (game.getTurn() % 2 == 1) {
						// Player 1
						game.debugMsg("PLAYER 1'S TURN");
						p = 'X';
						pnum = 1;
						pturn = 2;
					}
					else if (game.getTurn() % 2 == 0) {
						// Player 2
						game.debugMsg("PLAYER 2'S TURN");
						p = 'O';
						pnum = 2;
						pturn = 1;
					}
					bool is_valid = game.move(row, column, p);
					if (is_valid == true) {
						// Move was valid
						game.debugMsg("VALID MOVE");
						TicTacToe::gameStatus status = game.checkWin(game.getPlayer(pnum));
						if (status == 0 || status == 1) {
							game.printBoard(true);
							if (status == 1) {
								// Player wins
								std::cout << "\nPLAYER " << pnum << " WINS!\n";
							}
							else if (status == 0) {
								// Tie
								std::cout << "TIE! NO ONE WINS!\n";
							}
							game.endGame(title, menu);
							break;
						}
						else {
							game.debugMsg("ADVANCING TO THE NEXT TURN...");
							game.nextTurn();
						}
					}
					else {
						// Move was invalid
						game.debugMsg("INVALID MOVE");
						continue;
					}
				}
				else {
					// Invalid input
					continue;
				}
			}
		}

		else if (game.getInput() == 2) {
			// Start multiplayer game
			game.startGame();
			std::cout << "\nComing soon...\n";
		}

		else if (game.getInput() == 3) {
			// Help
			Console::clear();
			game.printMenu("", menu);
		}

		else if (game.getInput() == 4) {
			// Quit
			break;
		}
	}
	std::cout << "\nPress any key to exit...";
	std::cin.ignore();
	std::cin.get();
	return 0;
}
