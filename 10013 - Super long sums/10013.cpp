#include <iostream>

using namespace std;

int main() {
    int l, r, n, c;

    cin >> c;
    for (int m = 0; m < c; ++m) {
        if(m > 0) cout << endl;     //newline before number, except the 1st

        cin >> n;
        auto *arr = new int[n + 1];

        for (int i = 1; i < n + 1; ++i) {

            cin >> l;
            cin >> r;
            arr[i] = l + r;
        }

        for (int j = n; j > 0; --j) {

            if (arr[j] >= 10) {
                arr[j - 1]++;
                arr[j] -= 10;
            }
        }

        if (arr[0] != 0) cout << arr[0];
        for (int k = 1; k < n + 1; ++k) {

            cout << arr[k];
        }

        delete[] arr;
        cout << endl;
    }
    return 0;
}