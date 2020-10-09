#include <iostream>
#include <cstring>

using namespace std;

int main() {

    int k; //count of problems
    cin >> k;

    for (int i = 0; i < k; ++i) {

        int n; //height
        cin >> n;

        string unsorted[n];
        string sorted[n];

        cin.ignore();
        for (int j = 0; j < n; ++j) {
            getline(cin,unsorted[j]);
        }
        for (int l = 0; l < n; ++l) {
            getline(cin,sorted[l]);
        }

        int s = n - 1;
        for (int m = n - 1; m >= 0; --m) {
            if (unsorted[m] == sorted[s]) {
                --s;
            }
        }

        for (int i1 = s; i1 >= 0; --i1) {
            cout << sorted[i1] << endl;
        }
        cout << endl;
    }
    return 0;
}
