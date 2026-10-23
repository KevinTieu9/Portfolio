"""
graph_core.py
Personal project — GraphNet

Author: Kevin Tieu

Pure Python graph data structure for discrete mathematics algorithms.
Supports directed and undirected graphs with weighted edges.
"""

from collections import defaultdict
from typing import Dict, List, Set, Tuple, Optional

class Graph:
    """
    Undirected or directed graph using adjacency lists.
    Supports weighted edges.
    """

    """
    Create an empty graph.

    directed - True for a directed graph, False for undirected
    return nothing
    """
    def __init__(self, directed: bool = False) -> None:
        self.directed = directed
        self.adjacency: Dict[str, Dict[str, float]] = defaultdict(dict)
        self.nodes: Set[str] = set()

    """
    Add an isolated node to the graph.
    The node is recorded even if it has no edges yet.

    node - the name of the node to add
    return nothing
    """
    def add_node(self, node: str) -> None:
        self.nodes.add(node)
        if node not in self.adjacency:
            self.adjacency[node] = {}

    """
    Add a weighted edge from source to target.
    For an undirected graph, the reverse edge is added as well.
    Both nodes are created if they do not already exist.

    source - the node the edge starts from
    target - the node the edge points to
    weight - the cost of the edge (default 1.0)
    return nothing
    """
    def add_edge(self, source: str, target: str, weight: float = 1.0) -> None:
        self.add_node(source)
        self.add_node(target)
        self.adjacency[source][target] = weight
        if not self.directed:
            self.adjacency[target][source] = weight

    """
    Return the nodes that can be reached in one step from the given node.

    node - the node to look up
    return a list of neighbor names
    """
    def neighbors(self, node: str) -> List[str]:
        return list(self.adjacency.get(node, {}).keys())

    """
    Return the weight of the edge from source to target.
    If the edge does not exist, return None.

    source - the start of the edge
    target - the end of the edge
    return the weight, or None
    """
    def weight(self, source: str, target: str) -> Optional[float]:
        return self.adjacency.get(source, {}).get(target)

    """
    Return how many nodes are in the graph.

    return the node count
    """
    def number_of_nodes(self) -> int:
        return len(self.nodes)

    """
    Return how many edges are in the graph.
    An undirected edge is counted once.

    return the edge count
    """
    def number_of_edges(self) -> int:
        count = sum(len(neighbors) for neighbors in self.adjacency.values())
        return count if self.directed else count // 2

    """
    Build a printable summary of the graph and its edges.

    return a multi-line string listing each node and its edges
    """
    def __str__(self) -> str:
        lines = [f"Graph({'directed' if self.directed else 'undirected'})"]
        for node in sorted(self.nodes):
            edges = [f"{neighbor}:{weight}" for neighbor, weight in self.adjacency[node].items()]
            lines.append(f"  {node} -> {', '.join(edges) if edges else '(isolated)'}")
        return "\n".join(lines)
