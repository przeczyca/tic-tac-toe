#include <iostream>
#include <random>
#include <time.h>
using namespace std;

class Game{
	private:
		char board[3][3] = {    {' ',' ',' '},
	                                {' ',' ',' '},
        	                        {' ',' ',' '}};

	public:

		//return true if move made
		//false if move can't be made
		bool makeMove(int row, int col, char player){
			if(row > 2 || col > 2){
				return false;
			}
			if(row < 0 || col < 0){
				return false;
			}
			if(board[row][col] != ' '){
				return false;
			}

			board[row][col] = player;
			return true;
		}

		//returns true if game won by player
		//return false if game not won by player
		bool hasWinner(){
			//check rows
			for(int row = 0; row < 3; row++){
				if(board[row][0] != ' ' && board[row][0] == board[row][1] && board[row][1] == board[row][2]){
					return true;
				}
			}
			//check columns
			for(int col = 0; col < 3; col++){
				if(board[0][col] != ' ' && board[0][col] == board[1][col] && board[1][col] == board[2][col]){
					return true;
				}
			}
			//check diagonal
			if(board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]){
				return true;
			}
			if(board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]){
				return true;
			}

			return false;
		}

		//prints game board
		//	 X | O | O
		//	---+---+---
		//	 O | X | X
		//	---+---+---
		//	 X | X | O
		void printBoard(){
			for(int i = 0; i < 3; i++){
				cout << ' ';
				for(int j = 0; j < 3; j++){
					cout << board[i][j];
					if(j < 2){
						cout << " | ";
					}
				}

				cout << endl;
				if(i < 2){
					cout << "---+---+---" <<  endl;
				}
			}
		}
};

void twoPlayers(){
	Game game;

        char players[] = {'O', 'X'};
        bool Xturn = true;
        int turn = 0;

        while(!game.hasWinner() && turn < 9){
                cout << "#############################" << endl;
                game.printBoard();

                bool madeMove = false;
                while(!madeMove){
                        int row, col;
                        cout << "Player " << players[Xturn] << ", please enter row: ";
                        cin >> row;
                        cout << "Player " << players[Xturn] << ", please enter column: ";
                        cin >> col;

                        madeMove = game.makeMove(row, col, players[Xturn]);
                        if(!madeMove){
                                cout << "INVALID POSITION!" << endl;
                        }
                }


                Xturn = !Xturn;
                turn++;
        }

        if(game.hasWinner()){
                cout << "Player " << players[!Xturn] << " is the winner!" << endl;
        }
        else{
                cout << "Draw! No winner!" << endl;
        }

}

void easy(){
	mt19937 generator;
	generator.seed(time(0));

	uniform_int_distribution<uint32_t> range(0, 2);
	int random;

	Game game;
	char players[] = {'O', 'X'};
	int turn = 0;
	bool playerFirst, playerTurn;

	char ans;
	while(!(ans == 'y' || ans == 'n')){
		cout << "Do you want to go first? (y/n): ";
		cin >> ans;
	}

	switch(ans){
		case 'y':
			playerFirst = true;
			playerTurn = true;
			break;
		case 'n':
			playerFirst = false;
			playerTurn = false;
			break;
	}

	game.printBoard();
	while(!game.hasWinner() && turn < 9){
		cout << "#############################" << endl;

		bool madeMove = false;
		while(!madeMove){
			int row, col;
			if(playerTurn){
				cout << "Please enter row: ";
				cin >> row;
				cout << "Please enter column: ";
				cin >> col;

				madeMove = game.makeMove(row, col, players[playerFirst]);
				if(!madeMove){
					cout << "INVALID POSITION!" << endl;
				}
			}
			else{
				row = range(generator);
				col = range(generator);
				madeMove = game.makeMove(row, col, players[!playerFirst]);
			}
		}

		game.printBoard();
		turn++;
		playerTurn = !playerTurn;
		cout << "playerFirst = " << playerFirst << endl;
		cout << "playerTurn = " << playerTurn << endl;
	}

	if(game.hasWinner()){
		//bool playerWon = !playerTurn == playerFirst;
		//cout << "playerWon = " << playerWon << endl;
		if(!playerTurn){
			cout << "YOU WON!!!" << endl;
		}
		else{
			cout << "You lost! :(" << endl;
		}
	}
	else{
		cout << "Draw! No winner!" << endl;
	}
}

int main(){
	int option;
	cout << "Enter 1 to play against a bot or 2 to play with someone else: ";
	cin >> option;

	bool gameComplete = false;
	while(!gameComplete){
		switch(option){
			case 1:
				easy();
				gameComplete = true;
				break;
			case 2:
				twoPlayers();
				gameComplete = true;
				break;
			default:
				cout << "Invalid option!" << endl;
		}
	}

	return 0;
}





















