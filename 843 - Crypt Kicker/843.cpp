#include <iostream>
#include <utility>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

vector<string> v, hashed_v;

map<char, char> keymap;

vector<pair<char, char>> add_to_key(string a, string b) {
    vector<pair<char, char>> v_pair;

    v_pair.reserve(b.length());

    for (int i = 0; i < b.length(); ++i) {
        if (!keymap.count(b[i])) {
            v_pair.emplace_back(b[i], a[i]);
            keymap.insert({b[i], a[i]});
        }
    }
    return v_pair;
}

void erase_key(const vector<pair<char, char>> &vector) {

    for (auto &i : vector) {
        keymap.erase(i.first);
    }
}

bool match(string a, string b) {

    map<char, char> kmap;
    kmap.clear();


    if (a.length() != b.length()) return false;

    for (int i = 0; i < b.length(); ++i) {

        for (auto k : keymap) {
            if (k.second == a[i])
                if (k.first != b[i]) return false;
        }

        if (keymap.count(b[i]) != 0) {
            if (keymap.at(b[i]) != a[i]) return false;
        }

        for (auto km : kmap) {
            if (km.second == a[i])
                if(km.first != b[i]) return false;
        }

        if (kmap.count(b[i]) != 0) {
            if (kmap.at(b[i]) != a[i]) return false;
        } else kmap.insert({b[i], a[i]});


    }
    return true;
}

bool solve(int n) {

    if (n == hashed_v.size()) return true;

    vector<pair<char, char>> tmp_keys;

    for (auto &word : v) {
        if (match(word, hashed_v[n])) {
            tmp_keys = add_to_key(word, hashed_v[n]);
            if (solve(n + 1)) return true;
            erase_key(tmp_keys);
        }
    }

    return false;
}

int main() {
    int x;
    string s;

    cin >> x;
    //words into vector v
    for (int i = 0; i < x; ++i) {
        cin >> s;
        v.push_back(s);
    }
    cin >> ws;

    string line;

    while (getline(cin, line)) {
        hashed_v.clear();
        keymap.clear();

        istringstream is(line);
        while (is >> s) {
            hashed_v.push_back(s);
        }

        bool solved = false;
        if (solve(0)) solved = true;

        for (int k = 0; k < hashed_v.size(); ++k) {
            for (auto i : hashed_v[k]) {
                if (solved) cout << keymap.at(i) ;
                else cout << "*";
            }
            if (k < hashed_v.size() - 1) cout << " ";
        }
        cout << endl;
    }
    return 0;
}