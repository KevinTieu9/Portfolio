"""
test_algorithms.py
Basic correctness tests for graph algorithms.
Author: Kevin Tieu
"""

import sys
import os
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from graph_core import Graph
from algorithms import breadth_first_search, dijkstra_shortest_path, reconstruct_path, degree_centrality

def test_simple_path() -> None:
    graph = Graph()
    graph.add_edge("A", "B", 1)
    graph.add_edge("B", "C", 2)
    graph.add_edge("A", "C", 10)

    distances, parent = dijkstra_shortest_path(graph, "A")
    assert distances["C"] == 3.0
    path = reconstruct_path(parent, "A", "C")
    assert path == ["A", "B", "C"]

def test_bfs_reachability() -> None:
    graph = Graph()
    graph.add_edge("X", "Y")
    graph.add_edge("Y", "Z")
    parent = breadth_first_search(graph, "X")
    assert "Z" in parent
    assert "W" not in parent

def test_centrality() -> None:
    graph = Graph()
    graph.add_edge("A", "B")
    graph.add_edge("A", "C")
    graph.add_edge("B", "C")
    centrality = degree_centrality(graph)
    assert centrality["A"] == 1.0  # connected to both others

if __name__ == "__main__":
    test_simple_path()
    test_bfs_reachability()
    test_centrality()
    print("All tests passed.")
