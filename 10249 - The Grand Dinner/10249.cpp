#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Table {
    Table(int x, int y) : number(x + 1), seats_left(y) {}

    int number;
    int seats_left;
};

struct Team {
    explicit Team(int x, int y) : number(x), not_seated(y) {}

    int number;
    int not_seated;
    vector<int> seat_at;
};

int main() {
    int te, ta;

    while (true) {
        start:
        cin >> te >> ta;
        if (te == 0 && ta == 0) break;

        vector<Team> teams_v;
        vector<Table> tables_v;

        for (int i = 0; i < te; ++i) {
            int t;
            cin >> t;
            teams_v.emplace_back(i, t);
        }
        for (int i = 0; i < ta; ++i) {
            int t;
            cin >> t;
            tables_v.emplace_back(i, t);
        }

        sort(tables_v.begin(), tables_v.end(),
             [](const Table &a, const Table &b) { return a.seats_left > b.seats_left; }
        );
        sort(teams_v.begin(), teams_v.end(),
             [](const Team &a, const Team &b) { return a.not_seated > b.not_seated; }
        );

        //less tables than the members of the largest team
        if (tables_v.size() < teams_v[0].not_seated) {
            cout << '0' << endl;
            goto start;
        }

        //for each table assign one seat to each team, then sort teams
        for (auto &table : tables_v) {
            for (int i = 0; i < table.seats_left; ++i) {
                if (teams_v.size() <= i) break;
                if (teams_v[i].not_seated == 0) break;
                teams_v[i].seat_at.push_back(table.number);
                teams_v[i].not_seated--;
            }
            sort(teams_v.begin(), teams_v.end(),
                 [](const Team &a, const Team &b) { return a.not_seated > b.not_seated; }
            );
        }

        //fail if somebody not seated
        for (const auto &team : teams_v) {
            if (team.not_seated > 0) {
                cout << '0' << endl;
                goto start;
            }
        }

        //sort teams and print seat_at for each
        sort(teams_v.begin(), teams_v.end(),
             [](const Team &a, const Team &b) { return a.number < b.number; }
        );
        cout << 1 << endl;
        for (const auto &team : teams_v) {
            bool first = true;
            for (auto seat : team.seat_at) {
                if (!first) cout << " ";
                cout << seat;
                first = false;
            }
            cout << endl;
        }
    }
    return 0;
}
