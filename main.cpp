#include <iostream>

using namespace std;
#define MAX 15

int row, col, start_r, start_c, goal_r, goal_c, wall[MAX][MAX], result[MAX][MAX], dataset = 1;

void init() {
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            wall[i][j] = 0;
            result[i][j] = 0;
        }
    }
}

void read() {
    for(int i = 1; i <= row; i++) {
        for(int j = 1; j <= col; j++) {
            cin >> wall[i][j];
        }
    }
}

int check(int r, int c, int val, int right, int down) {
    if(r <= 0 || r > row || c <= 0 || c > col) {
        return 0;
    }
    if(right == 0 && down == 0) {
        if(wall[r][c] == val || wall[r][c] == 3) {
            return 0;
        }
    }
    else if(right == 1) {
        if(wall[r][c-1] == val || wall[r][c-1] == 3) {
            return 0;
        }
    }
    else if(down == 1) {
        if(wall[r-1][c] == val || wall[r-1][c] == 3) {
            return 0;
        }
    }
    if(result[r][c]) {
        return 0;
    }

    return 1;
}

int solve(int r, int c, int count) {
    if((r == goal_r) && (c == goal_c)) {
        result[r][c] = count;
        return 1;
    }

    result[r][c] = count;

    if((check(r, c-1, 1, 0, 0)) && (solve(r, c-1, count+1))) {
        return 1;
    }
    if((check(r-1, c, 2, 0, 0)) && (solve(r-1, c, count+1))) {
        return 1;
    }
    if((check(r, c+1, 1, 1, 0)) && (solve(r, c+1, count+1))) {
        return 1;
    }
    if((check(r+1, c, 2, 0, 1)) && (solve(r+1, c, count+1))) {
        return 1;
    }

    result[r][c] = -1;
    return 0;

}

void solveCase() {
    solve(start_r, start_c, 1);
}

void printOutput() {
    int isFirst = 1;

    cout << "Maze " << dataset++ << endl << endl;

    int c = col;
    while(c--) {
        cout << "+---";
        if(!c) cout << "+" << endl;
    }

    for(int i = 1; i <= row; i++) {
        if(isFirst) {
            isFirst = 0;
        }
        else {
            cout << "+";
            for(int j = 1; j <= col; j++) {
                if(wall[i-1][j] > 1) {
                    cout << "---+";
                }
                else {
                    cout << "   +";
                }
            }
            cout << endl;
        }

        for(int j = 1; j <= col; j++) {
            if(j == 1) {
                cout << "|";
            }

            if(result[i][j] == -1) {
                cout << "???";
            }
            else if(result[i][j] == 0) {
                cout << "   ";
            }
            else {
                if(result[i][j] >= 10) {
                    cout << " " << result[i][j];
                }
                else {
                    cout << "  " << result[i][j];
                }
            }

            if(wall[i][j] == 1 || wall[i][j] == 3 || j == col) {
                cout << "|";
            }
            else {
                cout << " ";
            }
        }
        cout << endl;
    }

    c = col;
    while(c--) {
        cout << "+---";
        if(!c) cout << "+" << endl;
    }

    cout << endl << endl;
}

int main()
{
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    while((cin >> row >> col >> start_r >> start_c >> goal_r >> goal_c) && (row || col || start_r || start_c || goal_r || goal_c)) {
        init();
        read();
        solveCase();
        printOutput();
    }
    return 0;
}
