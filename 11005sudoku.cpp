#include <iostream>
#include <vector>
#include <string>
using namespace std;
bool check(int board[9][9]);
int main() {
    int board[9][9];
    int number_of_sudokus;
    cin >> number_of_sudokus;
	vector<string> results(number_of_sudokus);
    for (int n = 0; n < number_of_sudokus; n++) {
		for (int i = 0; i < 9; i++) {
			cin >> board[i][0] >> board[i][1] >> board[i][2] >> board[i][3] >> board[i][4] >> board[i][5] >> board[i][6] >> board[i][7] >> board[i][8];
		}
		if (check(board)) { results[n] = "Right"; }
		else { results[n] = "Wrong"; }
        string line;
		getline(cin, line);
    }
	for (int i = 0; i < number_of_sudokus; i++) {
		cout << results[i] << endl;
	}
    return 0;
}

bool check(int board[9][9]){
	int rows[9][9] = { 0 };
	int cols[9][9] = { 0 };
	int subboxes[3][3][9] = { 0 };
	int x;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			x = board[i][j];
			rows[i][x - 1]++;
			cols[j][x - 1]++;
			subboxes[i / 3][j / 3][x - 1]++;
			if (rows[i][x - 1] > 1 || cols[j][x - 1] > 1 || subboxes[i / 3][j / 3][x - 1] > 1) {return false;}
		}
	}
	return true;
}

