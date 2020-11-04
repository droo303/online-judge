#include <iostream>
#include <cstring>

#define MAX_LEN 200

using namespace std;
typedef long long ll;
ll results[MAX_LEN];

ll calc(int i, string &s) {
    if (i == s.size()) return 0;
    ll &res = results[i];
    if (res != -1) return res;

    res = 0;
    ll num = 0;
    for (int j = i; j < s.size(); ++j) {
        num *= 10;
        num += s[j] - '0';
        if (num > INT32_MAX) break;
        res = max(res, num + calc(j + 1, s)); //last or new
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    string s;
    while (n--) {
        memset(results, -1, sizeof(results));
        cin >> s;
        cout << calc(0, s) << endl;
    }
    return 0;
}