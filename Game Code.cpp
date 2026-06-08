#include<iostream>
#include<conio.h>
#include<ctime>
#include<cstdlib>
#include<windows.h>
#include<fstream>
#include<iomanip>
using namespace std;
#define w 25
#define h 25
#define max_l 1000

class SG {
private:
    char board[h][w];
    int posX[max_l], posY[max_l], snakeLength;
    int frow, fcol, score, rtime, rid, obstacleTotal;
    bool isGameOver;
    HANDLE consoleHandle;

public:
    SG(int currentRound, int timeSeconds) {
        rid = currentRound;
        rtime = timeSeconds;
        obstacleTotal = (w*h*rid) / 100;
        score = 0;
        snakeLength = 1;
        isGameOver = false;
        consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void moveCursorTo(int row, int col) {
        COORD cursorPos = {col, row };
        SetConsoleCursorPosition(consoleHandle, cursorPos);
    }

    void game_board() {
        system("cls");
        srand(time(0));

        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                board[i][j] = ' ';

        for (int i = 0; i < h; i++) {
            board[i][0] = '#';
            board[i][w - 1] = '#';
        }
        for (int j = 0; j < w; j++) {
            board[0][j] = '#';
            board[h - 1][j] = '#';
        }

        for (int k = 0; k < obstacleTotal; k++) {
            int ox = rand() % (h - 2) + 1;
            int oy = rand() % (w - 2) + 1;
            if (board[ox][oy] == ' ')
                board[ox][oy] = 'X';
        }

        posX[0] = h / 2;
        posY[0] = w / 2;
        board[posX[0]][posY[0]] = 'O';

        food_func();
        redraw_board();
    }

    void food_func() {
        do {
            frow = rand() % (h - 2) + 1;
            fcol = rand() % (w - 2) + 1;
        } while (board[frow][fcol] != ' ');
        board[frow][fcol] = '*';
    }

    void redraw_board() {
        moveCursorTo(0, 0);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cout << board[i][j];
            }
            cout << endl;
        }
    }

    bool collision(int x, int y) {
        if (board[x][y] == '#' || board[x][y] == 'X')
            return true;
        for (int i = 0; i < snakeLength; i++)
            if (posX[i] == x && posY[i] == y)
                return true;
        return false;
    }

    void movement_func(char direction) {
        int dx = 0, dy = 0;
        if (direction == 'w') dx = -1;
        else if (direction == 's') dx = 1;
        else if (direction == 'a') dy = -1;
        else if (direction == 'd') dy = 1;

        int headX = posX[0] + dx;
        int headY = posY[0] + dy;

        if (collision(headX, headY)) {
            isGameOver = true;
            return;
        }

        bool ateFood = (board[headX][headY] == '*');
        if (ateFood) {
            score=score+10;
            snakeLength++;
            food_func();
        }
        else {
            int tailX = posX[snakeLength - 1];
            int tailY = posY[snakeLength - 1];
            board[tailX][tailY] = ' ';
        }

        for (int i = snakeLength - 1; i > 0; i--){
            posX[i] = posX[i - 1];
            posY[i] = posY[i - 1];
        }

        posX[0] = headX;
        posY[0] = headY;
        board[headX][headY] = 'O';
    }

    void startGame() {
        time_t gameStart = time(0);
        char direction = 'd';
        redraw_board();
        printHUD(rtime);

        while (!isGameOver && difftime(time(0), gameStart) < rtime) {
            int timeLeft = rtime - (int)difftime(time(0), gameStart);

            if (_kbhit()) {
                char key = _getch();
                if (key == -32) {
                    key = _getch();
                    switch (key) {
                    case 72: direction = 'w'; break;
                    case 80: direction = 's'; break;
                    case 75: direction = 'a'; break;
                    case 77: direction = 'd'; break;
                    }
                    movement_func(direction);
                    redraw_board();
                    printHUD(timeLeft);
                }
            }

            printTimer(timeLeft);
            Sleep(100);
        }

        moveCursorTo(h+4 ,0);
        if (isGameOver)
            cout << "Game Over! Collision detected.      " << endl;
        else
            cout << "Time's up!                          " << endl;

        recordStats((int)difftime(time(0), gameStart));
    }

    void printHUD(int timeLeft) {
        moveCursorTo(h, 0);
        cout << "Score: " << score << "\tRound: " << rid << "                     " << endl;
        cout << "Time Left: " << setw(3) << timeLeft << "s                           " << endl;
    }

    void printTimer(int timeLeft) {
        moveCursorTo(h + 1, 0);
        cout << "Time Left: " << setw(3) << timeLeft << "s                           ";
    }

    void recordStats(int timeSpent) {
    bool writeHeader = false;
    ifstream checkFile("D:\\Razi Abdullah\\Second Semester\\OOP\\Game practice program\\results.txt");
    if (!checkFile || checkFile.peek() == ifstream::traits_type::eof()) {
        writeHeader = true;
    }
    checkFile.close();

    ofstream resultFile("D:\\Razi Abdullah\\Second Semester\\OOP\\Game practice program\\results.txt", ios::app);
    
    if (writeHeader) {
        resultFile << "+----------+---------------+----------+" << endl;
        resultFile << "| "<<left<<setw(8)<<"Round"<< "| "<<left<<setw(13)<<"Time(s)"<< "| "<<left <<setw(8)<<"Score"<<" |"<<endl;
        resultFile << "+----------+---------------+----------+" << endl;
    }

    resultFile << "| "<< left << setw(8) << rid << "| " << left << setw(13) << timeSpent<< "| " << left << setw(8) << score << " |" << endl;
    resultFile << "+----------+---------------+----------+" << endl;

    resultFile.close();
}

};

int main() {
    int tRounds, time;

    cout << "Enter number of rounds: ";
    cin >> tRounds;
    cout << "Enter time per round (in seconds): ";
    cin >> time;

    for (int round = 1; round <= tRounds; round++) {
        SG match(round, time);
        match.game_board();
        match.startGame();
        system("pause");
    }

    cout << "\nAll rounds finished! Results saved in 'results.txt'.\n";
    return 0;
}

