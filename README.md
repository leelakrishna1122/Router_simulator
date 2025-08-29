# Router Simulator

A **C++ router simulator** that automatically selects the best shortest-path algorithm depending on the network topology and edge weights, with an optional **Streamlit UI** for interactive input and visualization.

---

## Features

- Supports multiple shortest path algorithms:  
  - **Dijkstra** (non-negative edges)  
  - **Bellman-Ford** (handles negative edges)  
  - **Floyd-Warshall** (all-pairs)  

- Automatic algorithm selection based on:  
  - Number of nodes (`n`)  
  - Number of links (`m`)  
  - Presence of negative edges  

- Prints **routing tables** for all nodes.  

- **Streamlit UI** allows dynamic entry of nodes and links without manually editing `topology.txt`.  





