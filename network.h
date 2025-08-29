#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
#include <queue>

struct RouteEntry {
    std::string destination;
    int cost;
};

enum class AlgorithmChoice {
    DIJKSTRA,
    FLOYD_WARSHALL,
    BELLMAN_FORD
};

class Network {
private:
    std::unordered_map<std::string, std::vector<std::pair<std::string,int>>> adj;
    std::vector<std::string> nodes;
    bool has_negative;

    // For Floyd-Warshall
    std::unordered_map<std::string,std::unordered_map<std::string,int>> fw_dist;

public:
    Network() : has_negative(false) {}

    void add_node(const std::string& node);
    void add_link(const std::string& u, const std::string& v, int cost);

    bool contains_negative_edges() const { return has_negative; }
    int get_n() const { return nodes.size(); }
    int get_m() const;
    const std::vector<std::string>& get_nodes() const { return nodes; }

    // Algorithms
    std::vector<RouteEntry> run_dijkstra(const std::string& src);
    void run_floyd_warshall();
    std::vector<RouteEntry> get_routing_fw(const std::string& src);
    std::vector<RouteEntry> run_bellman_ford(const std::string& src);
     // simplified: just chooses Dijkstra after reweighting

    // Auto selection
    AlgorithmChoice select_best_algorithm();
};
