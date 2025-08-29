Router & Routing Algorithm Simulator (C++)


Files:
- main.cpp : Program entry, CLI loop
- network.h/.cpp : Network and Graph implementation, Dijkstra routing
- util.h/.cpp : Small helpers (string split)
- topology.txt : Example input topology
- Makefile : Build instructions


Build:
make


Run:
./router topology.txt


Commands (interactive after running):
show ip route <RouterName> # display routing table for router
linkdown <A> <B> # remove link between A and B
linkup <A> <B> <cost> # add/update link between A and B
exit # quit


Example topology format (topology.txt):
NODES: A B C D
LINKS:
A B 2
A C 5
B C 1
B D 3
C D 2


This project computes routing tables using Dijkstra's algorithm (link-state style).
