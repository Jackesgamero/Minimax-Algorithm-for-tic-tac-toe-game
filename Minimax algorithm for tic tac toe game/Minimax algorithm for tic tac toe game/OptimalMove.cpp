//C++ program to find the next optimal move for a player

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

struct Move {
	int row, col;
};

const char player = 'X', opponent = 'O';

struct Box {
	bool marked;
	char symbol;
};

/*
This function returns true if there are moves remaining on the board.
It returns false if there are no moves left to play.
*/

bool noMovesLeft(const std::vector<std::vector<Box>> board) {
	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			if (!board[i][j].marked)
				return false;
		}
	}
	return true;
}

//Heuristic function
int heuristic(const std::vector<std::vector<Box>> b) {

	// Checking Rows for X or O victory. 
	for (size_t i = 0; i < 3; ++i){
		if (b[i][0].symbol == b[i][1].symbol &&
			b[i][1].symbol == b[i][2].symbol)
		{
			if (b[i][0].symbol == player)
				return +1;
			else if (b[i][0].symbol == opponent)
				return -1;
		}
	}

	// Checking Columns for X or O victory.
	for (size_t j = 0; j < 3; ++j){
		if (b[0][j].symbol == b[1][j].symbol &&
			b[1][j].symbol == b[2][j].symbol)
		{
			if (b[0][j].symbol == player)
				return +1;
			else if (b[0][j].symbol == opponent)
				return -1;
		}
	}

	// Checking Principal Diagonal for X or O victory. 
	if (b[0][0].symbol == b[1][1].symbol && b[1][1].symbol == b[2][2].symbol){
		if (b[0][0].symbol == player)
			return +1;
		else if (b[0][0].symbol == opponent)
			return -1;
	}

	//Checking Secundary Diagonal for X or O victory
	if (b[0][2].symbol == b[1][1].symbol && b[1][1].symbol == b[2][0].symbol){
		if (b[0][2].symbol == player)
			return +1;
		else if (b[0][2].symbol == opponent)
			return -1;
	}

	// If its a draw return 0
	return 0;
}


//Minimax Function
int minimax(std::vector<std::vector<Box>>& b, int depth, bool Max) {
	int score = heuristic(b);

	//If Maximizer has won the game return its score
	if (score == 1)
		return score;

	//If Minimizer has won the game return its score
	if (score == -1)
		return score;

	//If there are no moves left and no winner its a draw and we return 0
	if (noMovesLeft(b))
		return 0;

	//If its maximizer's move 
	if (Max) {
		int best = INT_MIN;

		//go through all cells
		for (size_t i = 0; i < 3; ++i){
			for (size_t j = 0; j < 3; ++j){
				if (!b[i][j].marked) {
					//Mark cell
					b[i][j].symbol = player;
					b[i][j].marked = true;

					//Recursive call
					best = std::max(best, minimax(b, depth + 1, false));

					//Unmarking cell
					b[i][j].symbol = ' ';
					b[i][j].marked = false;
				}
			}
		}
		return best;
	}

	//If its minimizers's move 
	else {
		int best = INT_MAX;

		//go through all cells
		for (size_t i = 0; i < 3; ++i) {
			for (size_t j = 0; j < 3; ++j) {
				if (!b[i][j].marked) {
					//Mark cell
					b[i][j].symbol = opponent;
					b[i][j].marked = true;

					//Recursive call
					best = std::min(best, minimax(b, depth + 1, true));

					//Unmarking cell
					b[i][j].symbol = ' ';
					b[i][j].marked = false;
				}
			}
		}
		return best;
	}
}

Move findBestMove(std::vector<std::vector<Box>>& b)
{
	int bestVal = INT_MIN;
	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;

	// Traverse all cells, evaluate minimax function for 
	// all empty cells. And return the cell with optimal 
	// value. 
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			// Check if cell is empty 
			if (!b[i][j].marked)
			{
				// Make the move 
				b[i][j].symbol = player;
				b[i][j].marked = true;

				// compute evaluation function for this 
				// move. 
				int moveVal = minimax(b, 0, false);

				// Undo the move
				b[i][j].marked = false;
				b[i][j].symbol = ' ';

				// If the value of the current move is 
				// more than the best value, then update 
				// best/ 
				if (moveVal > bestVal)
				{
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}

	std::cout << "The value of the best Move is : " << bestVal << "\n";

	return bestMove;
}


std::vector<std::vector<Box>> convertToVector(char board[3][3]) {
	std::vector<std::vector<Box>> b(3, std::vector<Box>(3));

	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			if (board[i][j] == player) {
				b[i][j].marked = true;
				b[i][j].symbol = player;
			}
			else if (board[i][j] == opponent) {
				b[i][j].marked = true;
				b[i][j].symbol = opponent;
			}
			else {
				b[i][j].marked = false;
				b[i][j].symbol = ' ';
			}
		}
	}
	return b;
}

int main()
{
	char board[3][3] =
	{
		{ 'X', 'O', 'X' },
		{ 'O', '_', 'O' },
		{ '_', 'X', '_' }
	};

	std::vector<std::vector<Box>> b(3, std::vector<Box>(3));
	b = convertToVector(board);

	Move bestMove = findBestMove(b);


	std::cout << "The Optimal Move is :\n" << "Row: " << bestMove.row << " Col: " << bestMove.col << '\n';

	return 0;
}