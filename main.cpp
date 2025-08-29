#include <iostream>
#include <fstream>
#include "network.h"

int main() {
    Network network;

    // ---------------- Read file ----------------
    std::ifstream fin("topology.txt");
    if (!fin) { std::cout << "Cannot open topology.txt\n"; return 1; }

    int n_nodes, n_links;
    fin >> n_nodes;
    for (int i=0;i<n_nodes;i++) {
        std::string node;
        fin >> node;
        network.add_node(node);
    }
    fin >> n_links;
    for (int i=0;i<n_links;i++) {
        std::string u,v;
        int cost;
        fin >> u >> v >> cost;
        network.add_link(u,v,cost);
    }

    // ---------------- Algorithm choice ----------------
    AlgorithmChoice alg = network.select_best_algorithm();
    std::cout << "Chosen algorithm: ";
    if (alg == AlgorithmChoice::DIJKSTRA) std::cout << "Dijkstra\n";
    else if (alg == AlgorithmChoice::BELLMAN_FORD) std::cout << "Bellman-Ford\n";
    else if (alg == AlgorithmChoice::FLOYD_WARSHALL) std::cout << "Floyd-Warshall\n";
    else std::cout << "Bellman-Ford\n";

    // ---------------- Compute routing tables ----------------
    std::cout << "\n=== Routing Tables ===\n";
    for (auto& node : network.get_nodes()) {
        std::vector<RouteEntry> table;
        if (alg == AlgorithmChoice::DIJKSTRA)
            table = network.run_dijkstra(node);
        else if (alg == AlgorithmChoice::BELLMAN_FORD)
            table = network.run_bellman_ford(node);
        else if (alg == AlgorithmChoice::FLOYD_WARSHALL) {
            network.run_floyd_warshall();
            table = network.get_routing_fw(node);
        }
        else table = network.run_dijkstra(node); 
        std::cout << "Routing table for " << node << ":\n";
        for (auto& e : table)
            std::cout << "  To " << e.destination << " cost " << e.cost << "\n";
        std::cout << "\n";
    }
    return 0;
}
