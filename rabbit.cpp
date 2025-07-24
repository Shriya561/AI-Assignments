#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
using namespace std;

typedef vector<char> State;

// Print state like: E E E _ W W W
void print_state(const State &state) {
    for (char c : state) cout << c << " ";
    cout << endl;
}

// Get next valid states
vector<State> get_next_states(State state) {
    vector<State> next_states;
    for (int i = 0; i < state.size(); i++) {
        int dir = (state[i] == 'E') ? 1 : (state[i] == 'W') ? -1 : 0;
        if (dir == 0) continue;

        // 1-step move
        int j = i + dir;
        if (j >= 0 && j < state.size() && state[j] == '_') {
            State temp = state;
            swap(temp[i], temp[j]);
            next_states.push_back(temp);
        }

        // 2-step jump
        j = i + 2 * dir;
        if (j >= 0 && j < state.size() && state[j] == '_' && state[i + dir] != '_') {
            State temp = state;
            swap(temp[i], temp[j]);
            next_states.push_back(temp);
        }
    }
    return next_states;
}

// BFS Search
void bfs(State start, State goal) {
    cout << "\nBFS Path:\n";
    queue<pair<State, vector<State>>> q;
    set<State> visited;
    q.push({start, {start}});

    while (!q.empty()) {
        auto [current, path] = q.front();
        q.pop();
        if (current == goal) {
            for (auto &s : path) print_state(s);
            return;
        }

        visited.insert(current);
        for (auto &next : get_next_states(current)) {
            if (visited.find(next) == visited.end()) {
                vector<State> new_path = path;
                new_path.push_back(next);
                q.push({next, new_path});
            }
        }
    }
}

// DFS Search
void dfs(State start, State goal) {
    cout << "\nDFS Path:\n";
    stack<pair<State, vector<State>>> st;
    set<State> visited;
    st.push({start, {start}});

    while (!st.empty()) {
        auto [current, path] = st.top();
        st.pop();
        if (current == goal) {
            for (auto &s : path) print_state(s);
            return;
        }

        visited.insert(current);
        for (auto &next : get_next_states(current)) {
            if (visited.find(next) == visited.end()) {
                vector<State> new_path = path;
                new_path.push_back(next);
                st.push({next, new_path});
            }
        }
    }
}

int main() {
    State start = {'E', 'E', 'E', '_', 'W', 'W', 'W'};
    State goal =  {'W', 'W', 'W', '_', 'E', 'E', 'E'};
    bfs(start, goal);
    dfs(start, goal);
    return 0;
}
