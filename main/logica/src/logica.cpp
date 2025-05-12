#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cmath>
using namespace std;

#define hole 'O'
#define rabbit 'R'
#define mushroom 'M'
#define fox 'F'
#define empty '_'
#define rabbit_in_hole '*'


char board[5][5];

int foxesNumber;

struct position {
	int row, column;
};

position randomPosition() {
	position pos;
	pos.row = rand() % 5;
	pos.column = rand() % 5;
	return pos;
}

void placeRabbits(int count) {

	int rabbits = 0;
	while (rabbits < count) {
		position pos = randomPosition();

		if (board[pos.row][pos.column] == empty) {
			board[pos.row][pos.column] = rabbit;
			++rabbits;
		}

		else if (board[pos.row][pos.column] == hole) {
			board[pos.row][pos.column] = rabbit_in_hole;
			++rabbits;
		}
	}
}

void placeMushrooms(int count) {
	int mushrooms = 0;
	while (mushrooms < count) {
		position pos = randomPosition();

		if (board[pos.row][pos.column] == empty) {
			board[pos.row][pos.column] = mushroom;
			++mushrooms;
		}
	}
}
bool validPosition(int row, int column) {
	return (row >= 0 && row < 5 && column >= 0 && column < 5);
}

struct foxPosition {
	position start, end;
	char orientation;
};

foxPosition Fox[5];
foxPosition possibleFoxMoves[100];

void placeFoxes(int count) {
	int foxes = 0;
	while (foxes < count) {
		position pos = randomPosition();

		if (board[pos.row][pos.column] == empty) {
			int num = rand();

			if (num % 2 == 0)
				Fox[foxes].orientation = 'v';
			else
				Fox[foxes].orientation = 'h';

			if (Fox[foxes].orientation == 'v') {
				if (pos.column % 2 == 1) {
					if (validPosition(pos.row + 1, pos.column) == true) {
						if (board[pos.row + 1][pos.column] == empty) {
							board[pos.row][pos.column] = board[pos.row + 1][pos.column] = fox;
							Fox[foxes].start = { pos.row, pos.column };
							Fox[foxes].end = { pos.row + 1, pos.column };
							++foxes;
						}
					}
					else if (board[pos.row - 1][pos.column] == empty) {
						board[pos.row][pos.column] = board[pos.row - 1][pos.column] = fox;
						Fox[foxes].start = { pos.row - 1, pos.column };
						Fox[foxes].end = { pos.row, pos.column };
						++foxes;
					}
				}
			}
			else {
				if (pos.row % 2 == 1) {
					if (validPosition(pos.row, pos.column - 1) == true) {
						if (board[pos.row][pos.column - 1] == empty) {
							board[pos.row][pos.column] = board[pos.row][pos.column - 1] = fox;
							Fox[foxes].start = { pos.row, pos.column - 1 };
							Fox[foxes].end = { pos.row, pos.column };
							++foxes;
						}
					}
					else if (board[pos.row][pos.column + 1] == empty) {
						board[pos.row][pos.column] = board[pos.row][pos.column + 1] = fox;
						Fox[foxes].start = { pos.row, pos.column };
						Fox[foxes].end = { pos.row , pos.column + 1 };
						++foxes;
					}
				}
			}
		}
	}
}

int foxMovements(foxPosition Fox[5]) {
	int moveCount = 0;
	for (int i = 0; i < foxesNumber; ++i) {
		if (Fox[i].orientation == 'v') {
			// Mutare în sus
			for (int r = Fox[i].end.row; r >= 1; --r) {
				if (validPosition(r - 1, Fox[i].start.column)) {
					possibleFoxMoves[moveCount++] = { {r - 1, Fox[i].start.column}, {r, Fox[i].start.column}, 'v' };
				}
				if (board[r - 2][Fox[i].start.column] != empty)
					break;
			}
			// Mutare în jos
			for (int r = Fox[i].start.row; r < 4; ++r) {
				if (validPosition(r + 1, Fox[i].end.column)) {
					possibleFoxMoves[moveCount++] = { {r, Fox[i].start.column}, {r + 1, Fox[i].start.column}, 'v' };
				}
				if (board[r + 2][Fox[i].end.column] != empty)
					break;
			}
		}

		else if (Fox[i].orientation == 'h') {
			// Mutare spre stânga
			for (int c = Fox[i].end.column; c >= 1; --c) {
				if (validPosition(Fox[i].start.row, c - 1)) {
					possibleFoxMoves[moveCount++] = { {Fox[i].start.row, c - 1}, {Fox[i].start.row, c}, 'h' };
				}
				if (board[Fox[i].start.row][c - 2] != empty)
					break;
			}
			// Mutare spre dreapta
			for (int c = Fox[i].start.column; c < 4; ++c) {
				if (validPosition(Fox[i].end.row, c + 1)) {
					possibleFoxMoves[moveCount++] = { {Fox[i].start.row, c}, {Fox[i].start.row, c + 1}, 'h' };
				}
				if (board[Fox[i].end.row][c + 2] != empty)
					break;
			}
		}
	}
	return moveCount;
}


// bool canBeSolved(board[5][5]) { }

void randomBoard() {
	srand(time(0));
	// do {
	for (int r = 0; r < 5; ++r)
		for (int c = 0; c < 5; ++c)
			board[r][c] = empty;
	board[0][0] = board[0][4] = board[4][0] = board[4][4] = board[2][2] = hole;
	int rabbitsNumber = rand() % 4;
	while (rabbitsNumber == 0)
		rabbitsNumber = rand() % 4;
	placeRabbits(rabbitsNumber);
	placeMushrooms(3);
	foxesNumber = rand() % 3;
	while (foxesNumber == 0)
		foxesNumber = rand() % 3;
	placeFoxes(foxesNumber);

	/*
		// } while (!canBeSolved(board));
		for (int r = 0; r < 5; ++r) {
			for (int c = 0; c < 5; ++c)
				cout << board[r][c] << ' ';
			cout << '\n';
		}
		*/
}







void printBoard() {
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			cout << board[i][j] << ' ';
		}
		cout << '\n';
	}
}

bool moveFox(int index, char direction, int positions) {
	int maxMoves = foxMovements(Fox);
	/*
	cout << maxMoves << '\n';
	for (int i = 0; i < maxMoves; ++i) {
		cout << possibleFoxMoves[i].start.row << ' ' << possibleFoxMoves[i].start.column << ' ' << possibleFoxMoves[i].end.row << ' ' << possibleFoxMoves[i].end.column << '\n';
	}
	*/
	bool ok = false;
	if (Fox[index].orientation == 'v') {
		if (direction == 'w') {
			for (int i = 1; i <= maxMoves; ++i) {
				if (possibleFoxMoves[i].start.row == Fox[index].start.row - positions &&
					possibleFoxMoves[i].end.row == Fox[index].end.row - positions &&
					board[Fox[index].start.row - positions][Fox[index].start.column] != rabbit &&
					board[Fox[index].end.row - positions][Fox[index].start.column] != rabbit) {
					board[Fox[index].start.row][Fox[index].start.column] = empty;
					board[Fox[index].end.row][Fox[index].end.column] = empty;
					board[Fox[index].start.row - positions][Fox[index].start.column] = fox;
					board[Fox[index].end.row - positions][Fox[index].start.column] = fox;
					Fox[index].start.row -= positions;
					Fox[index].end.row -= positions;
					ok = true;
					break;
				}
			}
		}
		else if (direction == 's') {
			for (int i = 1; i <= maxMoves; ++i) {
				if (possibleFoxMoves[i].start.row == Fox[index].start.row + positions &&
					possibleFoxMoves[i].end.row == Fox[index].end.row + positions &&
					board[Fox[index].start.row + positions][Fox[index].start.column] != rabbit &&
					board[Fox[index].end.row + positions][Fox[index].start.column] != rabbit) {
					board[Fox[index].start.row][Fox[index].start.column] = empty;
					board[Fox[index].end.row][Fox[index].end.column] = empty;
					board[Fox[index].start.row + positions][Fox[index].start.column] = fox;
					board[Fox[index].end.row + positions][Fox[index].start.column] = fox;
					Fox[index].start.row += positions;
					Fox[index].end.row += positions;
					ok = true;
					break;
				}
			}
		}
	}
	else {
		if (direction == 'a') {
			for (int i = 1; i <= maxMoves; ++i) {
				if (possibleFoxMoves[i].start.column == Fox[index].start.column - positions &&
					possibleFoxMoves[i].end.column == Fox[index].end.column - positions &&
					board[Fox[index].start.row][Fox[index].start.column - positions] != rabbit &&
					board[Fox[index].end.row][Fox[index].start.column - positions] != rabbit) {
					board[Fox[index].start.row][Fox[index].start.column] = empty;
					board[Fox[index].end.row][Fox[index].end.column] = empty;
					board[Fox[index].start.row][Fox[index].start.column - positions] = fox;
					board[Fox[index].end.row][Fox[index].end.column - positions] = fox;
					Fox[index].start.column -= positions;
					Fox[index].end.column -= positions;
					ok = true;
					break;
				}
			}
		}
		else if (direction == 'd') {
			for (int i = 1; i <= maxMoves; ++i) {
				if (possibleFoxMoves[i].start.column == Fox[index].start.column + positions &&
					possibleFoxMoves[i].end.column == Fox[index].end.column + positions &&
					board[Fox[index].start.row][Fox[index].start.column + positions] != rabbit &&
					board[Fox[index].end.row][Fox[index].start.column + positions] != rabbit) {
					board[Fox[index].start.row][Fox[index].start.column] = empty;
					board[Fox[index].end.row][Fox[index].end.column] = empty;
					board[Fox[index].start.row][Fox[index].start.column + positions] = fox;
					board[Fox[index].end.row][Fox[index].end.column + positions] = fox;
					Fox[index].start.column += positions;
					Fox[index].end.column += positions;
					ok = true;
					break;
				}
			}
		}
	}
	return ok;
}

bool moveRabbit(int L1, int C1, int L2, int C2) {
	if ((L1 != L2 && C1 != C2) || (L1 == L2 && abs(C1 - C2) == 1) || C1 == C2 && abs(L1 - L2) == 1 ||
		board[L2][C2] == mushroom || board[L2][C2] == fox || board[L2][C2] == rabbit_in_hole || abs(L1 - L2) == 1 || abs(C1 - C2) == 1 && !validPosition(L2, C2)) {
		//cout << "Miscare imposibila.\n";
		return false;
	}

	else if (L1 == L2 && C1 == C2)
		return true;
	else if (L1 != L2 && C1 == C2) {
		if (L1 > L2) {
			for (int l = L1 - 1; l > L2; --l)
				if (board[l][C1] != mushroom && board[l][C1] != fox && board[l][C1] != rabbit && board[l][C1] != rabbit_in_hole) {
					//	cout << "Miscare imposibila.\n";
					return false;
				}
		}
		else {
			for (int l = L1 + 1; l < L2; ++l)
				if (board[l][C1] != mushroom && board[l][C1] != fox && board[l][C1] != rabbit && board[l][C1] != rabbit_in_hole) {
					//	cout << "Miscare imposibila.\n";
					return false;
				}
		}
		if (board[L1][C1] == rabbit_in_hole)
			board[L1][C1] = hole;
		else
			board[L1][C1] = empty;
		if (board[L2][C2] == empty)
			board[L2][C2] = rabbit;
		else if (board[L2][C2] == hole)
			board[L2][C2] = rabbit_in_hole;
		return true;
		return true;
	}
	else if (C1 != C2 && L1 == L2) {
		if (C1 > C2) {
			for (int c = C1 - 1; c > C2; --c)
				if (board[L1][c] != mushroom && board[L1][c] != fox && board[L1][c] != rabbit && board[L1][c] != rabbit_in_hole) {
					//	cout << "Miscare imposibila.\n";
					return false;
				}
		}
		else {
			for (int c = C1 + 1; c < C2; ++c)
				if (board[L1][c] != mushroom && board[L1][c] != fox && board[L1][c] != rabbit && board[L1][c] != rabbit_in_hole) {
					//	cout << "Miscare imposibila.\n";
					return false;;
				}
		}
		if (board[L1][C1] == rabbit_in_hole)
			board[L1][C1] = hole;
		else
			board[L1][C1] = empty;
		if (board[L2][C2] == empty)
			board[L2][C2] = rabbit;
		else if (board[L2][C2] == hole)
			board[L2][C2] = rabbit_in_hole;
		return true;
	}
	return false;
}

bool gameWon() {
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			if (board[i][j] == rabbit)
				return false;
	return true;
}

/*
int stepCount;
char solutionSteps[100][100];

void addStep(const char* stepDescription) {
	strcpy(solutionSteps[stepCount], stepDescription);
	stepCount++;
}

bool solveGame(int depth) {
	if (depth > 100)
		return false;
	if (gameWon() == true) {
		for (int i = 0; i < stepCount; ++i) {
			cout << solutionSteps[i] << '\n';
		}
		return true;
	}
	for (int index = 0; index < foxesNumber; ++index) {
		char directions[] = { 'w', 'a', 's', 'd' };
		for (char d = 0; d < 4; ++d) {
			for (int steps = 0; steps <= 3; ++steps) {
				if (moveFox(index, directions[d], steps) == true) {
					char stepDescription[100];
					stepDescription[0] = '\0';
					strcat(stepDescription, "Mutare vulpe de la pozitia ");
					char sir[20];
					itoa(Fox[index].start.row, sir, 20);
					strcat(stepDescription, sir);
					strcat(stepDescription, " ");
					itoa(Fox[index].start.column, sir, 20);
					strcat(stepDescription, sir);
					strcat(stepDescription, " ");
					strcat(stepDescription, (directions[d] == 'w' ? "sus" : (directions[d] == 's' ? "jos" : (directions[d] == 'a' ? "stanga" : "dreapta"))));
					strcat(stepDescription, " cu ");
					itoa(steps, sir, 20);
					strcat(stepDescription, " pași.");
					addStep(stepDescription);
				}
				if (solveGame(depth + 1) == true)
					return true;
				char dir;
				if (directions[d] == 'w')
					dir = 'a';
				else if (directions[d] == 'a')
					dir = 'w';
				else if (directions[d] == 's')
					dir = 'd';
				else if (directions[d] == 'd')
					dir = 's';
				moveFox(index, dir, steps);
				--stepCount;
			}
		}
	}
	for (int r = 0; r < 5; ++r) {
		for (int c = 0; c < 5; ++c) {
			if (board[r][c] == rabbit) {
				for (int i = 0; i < 5; ++i) {
					for (int j = 0; j < 5; ++j) {
						if (moveRabbit(r, c, i, j)) {
							char stepDescription[100];
							stepDescription[0] = '\0';
							strcat(stepDescription, "Mutare iepure de la ");
							char sir[20];
							itoa(r, sir, 20);
							strcat(stepDescription, sir);
							strcat(stepDescription, " ");
							itoa(c, sir, 20);
							strcat(stepDescription, sir);
							strcat(stepDescription, " la ");
							itoa(i, sir, 20);
							strcat(stepDescription, sir);
							strcat(stepDescription, " ");
							itoa(j, sir, 20);
							strcat(stepDescription, sir);
							strcat(stepDescription, ".");
							addStep(stepDescription);
						}
						if (solveGame(depth + 1) == true)
							return true;
						moveRabbit(i, j, r, c);
						--stepCount;
					}
				}
			}
		}
	}
	return false;
}
*/

void playGame() {
	// char board[5][5];
	randomBoard();
	while (true) {
		if (gameWon() == true) {
			cout << "Felicitari! Ai castigat.\n";
			break;
		}
		char choice;
		cout << "Pentru a muta o vulpe, apasa v, apoi Enter.\n";
		cout << "Pentru a muta un iepure, apasa i, apoi Enter.\n";
		cout << "Pentru a incheia jocul, apasa e, apoi Enter.\n";
		cout << "Pentru dezvaluirea solutiei, apasa s, apoi Enter.\n";
		cin >> choice;
		if (choice == 'v') {
			int L, C;
			cout << "Introdu pozitia initiala a vulpii (oricare dintre cele 2 pozitii):\n";
			cin >> L >> C;
			for (int i = 0; Fox[i].orientation != '\0'; ++i) {
				if (((Fox[i].start.row == L && Fox[i].start.column == C) || (Fox[i].end.row == L && Fox[i].end.column == C))) {
					char direction;
					int positions;
					if (Fox[i].orientation == 'v')
						cout << "In ce directie (sus/jos) si cate pozitii doresti sa muti vulpea?\n";
					else
						cout << "In ce directie (stanga/dreapta) si cate pozitii doresti sa muti vulpea?\n";
					cin >> direction >> positions;
					if (moveFox(i, direction, positions) == false) {
						cout << "Miscare imposibila.\n";
					}
					break;
				}
			}
		}
		else if (choice == 'i') {
			int L1, C1, L2, C2;
			cout << "Introdu pozitia initiala:\n";
			cin >> L1 >> C1;
			cout << "Introdu pozitia finala:\n";
			cin >> L2 >> C2;
			if (moveRabbit(L1, C1, L2, C2) == false) {
				cout << "Miscare imposibila.\n";
			}
		}
		else if (choice == 'e')
			break;
		/*else if (choice == 's') {
			if (solveGame(0) == false) {
				cout << "Nu exista nicio solutie.";
				break;
			}
			solveGame(0);
		}*/
		printBoard();
	}
}

void loadLevel(const char* filename) {
	ifstream fis;
	if (!fis)
		return;
	else
		fis.open(filename);
	for (int r = 0; r < 5; ++r) {
		for (int c = 0; c < 5; ++c) {
			fis >> board[r][c];
		}
	}
	fis.close();
}

void fox_level4() {
	foxesNumber = 1;
	Fox[0].start.row = 1;
	Fox[0].start.column = 1;
	Fox[0].end.row = 1;
	Fox[0].end.column = 2;
	Fox[0].orientation = 'h';
}

void fox_level5() {
	foxesNumber = 1;
	Fox[0].start.row = 0;
	Fox[0].start.column = 3;
	Fox[0].end.row = 1;
	Fox[0].end.column = 3;
	Fox[0].orientation = 'v';
}

void fox_level6() {
	foxesNumber = 2;

	Fox[0].start.row = 1;
	Fox[0].start.column = 2;
	Fox[0].end.row = 1;
	Fox[0].end.column = 3;
	Fox[0].orientation = 'h';

	Fox[1].start.row = 3;
	Fox[1].start.column = 0;
	Fox[1].end.row = 3;
	Fox[1].end.column = 1;
	Fox[1].orientation = 'h';
}

void fox_level7() {
	foxesNumber = 2;

	Fox[0].start.row = 0;
	Fox[0].start.column = 1;
	Fox[0].end.row = 1;
	Fox[0].end.column = 1;
	Fox[0].orientation = 'v';

	Fox[1].start.row = 3;
	Fox[1].start.column = 1;
	Fox[1].end.row = 3;
	Fox[1].end.column = 2;
	Fox[1].orientation = 'h';
}

void fox_level8() {
	foxesNumber = 1;

	Fox[0].start.row = 1;
	Fox[0].start.column = 1;
	Fox[0].end.row = 2;
	Fox[0].end.column = 1;
	Fox[0].orientation = 'v';
}