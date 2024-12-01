#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <cmath>

// https://en.wikipedia.org/wiki/Stoer%E2%80%93Wagner_algorithm#Example_code

std::pair<int, std::vector<int>> global_min_cut(std::vector<std::vector<int>> mat) {
    std::pair<int, std::vector<int>> best = {INT_MAX, {}};
    int n = mat.size();
    std::vector<std::vector<int>> co(n);

    for (int i = 0; i < n; i++)
        co[i] = {i};

    for (int ph = 1; ph < n; ph++) {
        std::vector<int> w = mat[0];
        size_t s = 0, t = 0;
        for (int it = 0; it < n - ph; it++) {
            w[t] = INT_MIN;
            s = t, t = std::max_element(w.begin(), w.end()) - w.begin();
            for (int i = 0; i < n; i++) w[i] += mat[t][i];
        }
        best = std::min(best, {w[t] - mat[t][t], co[t]});
        co[s].insert(co[s].end(), co[t].begin(), co[t].end());
        for (int i = 0; i < n; i++) mat[s][i] += mat[t][i];
        for (int i = 0; i < n; i++) mat[i][s] = mat[s][i];
        mat[0][t] = INT_MIN;
    }

    return best;
}

void solve() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    if (!in.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    std::string line;
    std::unordered_map<std::string, int> node_to_index;
    std::vector<std::pair<int, int>> connections;

    while(std::getline(in, line)) {
        std::stringstream ss(line);
        std::string node;
        ss >> node;
        node = node.substr(0, node.length() - 1);
        int node_index = -1;
        if(node_to_index.count(node)) {
            node_index = node_to_index[node];
        } else {
            node_index = node_to_index.size();
            node_to_index[node] = node_index;
        }

        while(ss >> node) {
            int index = -1;
            if(node_to_index.count(node)) {
                index = node_to_index[node];
            } else {
                index = node_to_index.size();
                node_to_index[node] = index;
            }
            connections.push_back({node_index, index});
        }
    }

    std::vector<std::vector<int>> adj(node_to_index.size(), std::vector<int>(node_to_index.size(), 0));
	for (const auto& p : connections)
		adj[p.first][p.second] = adj[p.second][p.first] = 1;

	auto result = global_min_cut(adj);
	out << result.second.size() * (node_to_index.size() - result.second.size());

    out.close();
    in.close();
}

int main() {
    solve();
    return 0;
}
