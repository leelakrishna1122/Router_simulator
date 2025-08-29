#include "network.h"
#include <iostream>
#include <algorithm>
#include <cmath> // add this for log2
#include <limits>

// ----------------- Graph construction -----------------
void Network::add_node(const std::string& node) {
    nodes.push_back(node);
    if (adj.find(node) == adj.end())
        adj[node] = {};
}

void Network::add_link(const std::string& u, const std::string& v, int cost) {
    adj[u].push_back({v, cost});
    adj[v].push_back({u, cost});
    if (cost < 0) has_negative = true;
}

int Network::get_m() const {
    int cnt = 0;
    for (auto& kv : adj) cnt += kv.second.size();
    return cnt/2; // because undirected
}

// ----------------- Dijkstra -----------------
std::vector<RouteEntry> Network::run_dijkstra(const std::string& src) {
    std::unordered_map<std::string,int> dist;
    for (auto& kv : adj) dist[kv.first] = std::numeric_limits<int>::max();
    dist[src] = 0;

    using pii = std::pair<int,std::string>;
    std::priority_queue<pii,std::vector<pii>,std::greater<pii>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d,u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto& [v,cost] : adj[u]) {
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                pq.push({dist[v], v});
            }
        }
    }

    std::vector<RouteEntry> table;
    for (auto& kv : dist)
        if (kv.first != src) table.push_back({kv.first, kv.second});
    return table;
}

// ----------------- Floyd-Warshall -----------------
void Network::run_floyd_warshall() {
    fw_dist.clear();
    for (auto& u : nodes)
        for (auto& v : nodes)
            fw_dist[u][v] = (u==v ? 0 : std::numeric_limits<int>::max()/2);

    for (auto& kv : adj)
        for (auto& p : kv.second)
            fw_dist[kv.first][p.first] = p.second;

    for (auto& k : nodes)
        for (auto& i : nodes)
            for (auto& j : nodes)
                if (fw_dist[i][k] + fw_dist[k][j] < fw_dist[i][j])
                    fw_dist[i][j] = fw_dist[i][k] + fw_dist[k][j];
}

std::vector<RouteEntry> Network::get_routing_fw(const std::string& src) {
    std::vector<RouteEntry> table;
    for (auto& dest : nodes)
        if (dest != src)
            table.push_back({dest, fw_dist[src][dest]});
    return table;
}

// ----------------- Bellman-Ford -----------------
std::vector<RouteEntry> Network::run_bellman_ford(const std::string& src) {
    std::unordered_map<std::string,int> dist;
    for (auto& n : nodes) dist[n] = std::numeric_limits<int>::max()/2;
    dist[src] = 0;

    int n_nodes = nodes.size();
    for (int i=0;i<n_nodes-1;i++) {
        for (auto& u : nodes)
            for (auto& [v,c] : adj[u])
                if (dist[u] + c < dist[v])
                    dist[v] = dist[u] + c;
    }

    std::vector<RouteEntry> table;
    for (auto& kv : dist)
        if (kv.first != src) table.push_back({kv.first, kv.second});
    return table;
}

// ----------------- Johnson -----------------


// ----------------- Algorithm selection -----------------
AlgorithmChoice Network::select_best_algorithm() {
    int n = get_n();
    int m = get_m();

    // compute "estimated time" using formulae
    // Use integers to compare:
    // Dijkstra: n*(n+m)*log n
    // Bellman-Ford: n*n*m
    // Floyd-Warshall: n^3
  
    int est_dijkstra = (!has_negative ? n*(n+m)*(int)log2(n+1) : 1e9);
    int est_bf = has_negative ? n*n*m : 1e9;
    int est_fw = n*n*n;

    
    int min_est = std::min({est_dijkstra, est_bf, est_fw});

    if (min_est == est_dijkstra) return AlgorithmChoice::DIJKSTRA;
    if (min_est == est_bf) return AlgorithmChoice::BELLMAN_FORD;
    if (min_est == est_fw) return AlgorithmChoice::FLOYD_WARSHALL;
    return AlgorithmChoice::BELLMAN_FORD;
}
