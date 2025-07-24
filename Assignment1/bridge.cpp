#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

// Time taken by each person
map<string, int> times = {
    {"Amogh", 5},
    {"Ameya", 10},
    {"Grandma", 20},
    {"Grandpa", 25}
};

struct State {
    set<string> left, right;
    string umbrella_side;
    int total_time;

    bool operator<(const State &other) const {
        return tie(left, umbrella_side, total_time) < tie(other.left, other.umbrella_side, other.total_time);
    }
};

// Generate combinations (1 or 2 people)
vector<vector<string>> get_combinations(set<string> side) {
    vector<string> people(side.begin(), side.end());
    vector<vector<string>> combos;

    for (int i = 0; i < people.size(); i++) {
        combos.push_back({people[i]});
        for (int j = i + 1; j < people.size(); j++) {
            combos.push_back({people[i], people[j]});
        }
    }
    return combos;
}

State move(State curr, vector<string> group) {
    State next = curr;
    int max_time = 0;

    for (auto &p : group)
        max_time = max(max_time, times[p]);

    if (curr.umbrella_side == "left") {
        for (auto &p : group) {
            next.left.erase(p);
            next.right.insert(p);
        }
        next.umbrella_side = "right";
    } else {
        for (auto &p : group) {
            next.right.erase(p);
            next.left.insert(p);
        }
        next.umbrella_side = "left";
    }

    next.total_time += max_time;
    return next;
}

void bfs_bridge() {
    set<string> all = {"Amogh", "Ameya", "Grandma", "Grandpa"};
    State start = {all, {}, "left", 0};
    queue<pair<State, vector<pair<vector<string>, int>>>> q;
    set<State> visited;

    q.push({start, {}});

    while (!q.empty()) {
        auto [curr, path] = q.front(); q.pop();

        if (curr.right.size() == 4 && curr.total_time <= 60) {
            cout << "\nBridge Crossing Plan:\n";
            for (auto &[group, t] : path) {
                cout << "Group: ";
                for (string p : group) cout << p << " ";
                cout << " | Time used: " << t << " mins\n";
            }
            cout << "Total Time: " << curr.total_time << " mins\n";
            return;
        }

        if (visited.count(curr)) continue;
        visited.insert(curr);

        set<string> &side = (curr.umbrella_side == "left") ? curr.left : curr.right;

        for (auto &group : get_combinations(side)) {
            State next = move(curr, group);
            auto new_path = path;
            new_path.push_back({group, next.total_time});
            q.push({next, new_path});
        }
    }

    cout << "No valid way found within 60 minutes.\n";
}

int main() {
    bfs_bridge();
    return 0;
}
