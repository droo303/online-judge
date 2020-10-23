#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>

using namespace std;

int x_min=0, x_max=0, y_min=0, y_max=0;

struct tile {
    int x;
    int y;
    char direction;
    char shape;
};

char rotate(char c){
    switch (c){
        case 'L':
            return 'D';
        case 'R':
            return 'U';
        case 'U':
            return 'L';
        case 'D':
            return 'R';
        default:
            return 'X';
    }
}

char shape(char c) {
    switch (c) {
        case 'L':
            return '_';
        case 'U':
            return '|';
        case 'R':
            return '_';
        case 'D':
            return '|';
        default:
            return 'X';
    }
}

tuple<int,int> direction (char c, char d) {
    switch (c) {
        case 'L':
            switch (d) {
                case 'U':
                    return {-1,0};
                case 'D':
                    return {-1,-1};
                default: return {};
            }
        case 'R':
            switch (d) {
                case 'U':
                    return {1,0};
                case 'D':
                    return {1,-1};
                default: return {};
            }
        case 'U':
            switch (d) {
                case 'L':
                    return {-1,1};
                case 'R':
                    return {1,1};
                default: return {};
            }
        case 'D':
            switch (d) {
                case 'L':
                    return {-1,0};
                case 'R':
                    return {1,0};
                default: return {};
            }
        default:
            return {};
    }
}

void fold(vector<tile> &v,int n){
    if (n==1){
        v[0].direction='R';
        return;
    }
    fold(v,n/2);

    for (int i = 0; i < n/2; ++i) {
        v[n-1-i].direction=rotate(v[i].direction);
    }
}

void location(vector<tile> &v){
    x_min=0, x_max=0, y_min=0, y_max=0;

    v[0].x = 0;
    v[0].y = 0;
    for (int i = 1; i < v.size(); ++i) {
        v[i].x = v[i-1].x + get<0>(direction(v[i-1].direction,v[i].direction));
        v[i].y = v[i-1].y + get<1>(direction(v[i-1].direction,v[i].direction));

        if(v[i].x < x_min){
            x_min = v[i].x ;
        }
        if(v[i].y < y_min){
             y_min = v[i].y;
        }

        if(v[i].x > x_max){
             x_max = v[i].x;
        }
        if(v[i].y > y_max){
             y_max = v[i].y;
        }
    }

    for (auto & j : v) {
        j.x += abs(x_min);
        j.y += abs(y_min);

        j.shape = shape(j.direction);
    }
    x_max += abs(x_min);
    y_max += abs(y_min);
}

int main() {

    int n;

    while(cin >> n) {
        if(n == 0) return 0;

        //every fold multiplies no of tiles by 2
        int len = pow(2, n);
        vector<struct tile> v;
        v.resize(len);

        //fill vector with directions
        fold(v, len);

        //compute x,y of each tile
        location(v);

        char board[y_max + 1][x_max + 1];

        //fill board with ' '
        for (int k = 0; k <= y_max; ++k) {
            for (int j = 0; j <= x_max; ++j) {
                board[k][j] = ' ';
            }
        }

        //fill board with shapes
        for (auto &i : v) {
            board[i.y][i.x] = i.shape;
        }

        //fill board with 0 at the end of rows
        for (int j = 0; j <= y_max; ++j) {
            for (int i = x_max; i >= 0; --i) {
                if (board[j][i] == ' ') board[j][i] = '0';
                else break;
            }
        }

        //print board except 0s
        for (int j = y_max; j >= 0; --j) {
            for (int i = 0; i <= x_max; ++i) {
                if (board[j][i] == '0') break;
                cout << board[j][i];
            }
            cout << endl;
        }

        cout << "^" << endl;
    }

    return 0;
}
