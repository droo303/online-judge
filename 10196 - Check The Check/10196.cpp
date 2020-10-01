#include <iostream>

using namespace std;

void input(int &, int &, int &, int &, char[][12]);

void output(char[][12]);

bool check(int kx, int ky, char board[][12], bool white_takes);

int main() {
    int game = 1;
    while (true) {
        char board[12][12];
        int bkx = -1, bky = -1, wkx = -1, wky = -1;

        input(bkx, bky, wkx, wky, board);
        if (bkx == -1 || wkx == -1) return 0; //exit if empty board
        //output(board);
        //Game #n: black/white/no king is in check
        cout << "Game #" << game << ": ";
        if (check(bkx, bky, board, true)) cout << "black";
        else if (check(wkx, wky, board, false)) cout << "white";
        else cout << "no";
        cout << " king is in check." << endl;

        game++;
    }
}

void input(int &bkx, int &bky, int &wkx, int &wky, char board[][12]) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (i < 2 || j < 2 || i > 9 || j > 9) {
                board[i][j] = '*';
                continue;
            }
            cin >> board[i][j];
            if (board[i][j] == 'k') {
                bky = i;
                bkx = j;
            } else if (board[i][j] == 'K') {
                wky = i;
                wkx = j;
            }
        }
    }
}

void output(char board[][12]) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}

bool check(int kx, int ky, char board[][12], bool white_takes) {
    int ds[][2] = {{0,  -1},
                   {0,  1},
                   {-1, 0},
                   {1,  0},
                   {1,  1},
                   {-1, 1},
                   {-1, -1},
                   {1,  -1}}; //directions

    int knight[][2] = {{-2, -1},
                       {-2, 1},
                       {-1, -2},
                       {-1, 2},
                       {1,  -2},
                       {1,  2},
                       {2,  -1},
                       {2,  1}};

    int pawn[][2] = {{-1, -1},
                     {1,  -1},
                     {-1, 1},
                     {1,  1}}; //{x,y}/{w,w,b,b}

    char piece;
    char tile;
    char mod;
    int pawnm;

    if (white_takes) {
        mod = 0, pawnm = 2;
    } else {
        mod = ' ', pawnm = 0;
    } //set w/b modulator and pawn modulator

    //pawn
    for (int i = 0; i < 2; ++i) {
        tile = board[ky + pawn[i+pawnm][1]][kx + pawn[i+pawnm][0]];
        if (tile == ('P' | mod)) return true;
    }
    //knight
    for (int i = 0; i < 8; ++i) {
        tile = board[ky + knight[i][1]][kx + knight[i][0]];
        if (tile == ('N' | mod)) return true;
    }
    //the rest
    for (int i = 0; i < 8; ++i) {
        i < 4 ? piece = 'R' | mod : piece = 'B' | mod;
        int dx = 0, dy = 0;
        do {
            dx += ds[i][0];
            dy += ds[i][1];
            tile = board[ky + dy][kx + dx];
            if (tile == piece || tile == ('Q' | mod)) return true;
        } while (tile == '.');
    }
    return false;
}

