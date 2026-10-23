"""
algorithms.py
Personal project — GraphNet

Author: Kevin Tieu

Core graph algorithms implemented from first principles.
Includes breadth-first search, depth-first search, Dijkstra,
path reconstruction, degree centrality, and connected components.
"""

from collections import deque, defaultdict
from typing import Dict, List, Optional, Set, Tuple
from graph_core import Graph

"""
Breadth-first search from a start node.
Visits nodes level by level and records the parent of each node so the
shortest unweighted path can be rebuilt later.

graph - the graph to search
start - the node to begin from
return a dictionary mapping each reached node to its parent
"""
def breadth_first_search(graph: Graph, start: str) -> Dict[str, Optional[str]]:
    if start not in graph.nodes:
        raise ValueError(f"Start node '{start}' is not in the graph.")

    parent: Dict[str, Optional[str]] = {start: None}
    queue = deque([start])

    while queue:
        current = queue.popleft()
        for neighbor in graph.neighbors(current):
            if neighbor not in parent:
                parent[neighbor] = current
                queue.append(neighbor)

    return parent

"""
Depth-first search from a start node.
Follows one path as far as it will go before backtracking, and records
every node that can be reached from the start.

graph - the graph to search
start - the node to begin from
return the set of nodes reachable from the start
"""
def depth_first_search(graph: Graph, start: str) -> Set[str]:
    if start not in graph.nodes:
        raise ValueError(f"Start node '{start}' is not in the graph.")

    visited: Set[str] = set()

    def visit(node: str) -> None:
        visited.add(node)
        for neighbor in graph.neighbors(node):
            if neighbor not in visited:
                visit(neighbor)

    visit(start)
    return visited

"""
Dijkstra's algorithm for single-source shortest paths.
Assumes non-negative edge weights. Builds a distance map and a
parent map so the shortest path to any node can be rebuilt.

graph - the weighted graph to search
start - the node to begin from
return a tuple of (distance dictionary, parent dictionary)
"""
def dijkstra_shortest_path(graph: Graph, start: str) -> Tuple[Dict[str, float], Dict[str, Optional[str]]]:
    if start not in graph.nodes:
        raise ValueError(f"Start node '{start}' is not in the graph.")

    import heapq
    distances: Dict[str, float] = {node: float('inf') for node in graph.nodes}
    distances[start] = 0.0
    parent: Dict[str, Optional[str]] = {start: None}
    priority_queue = [(0.0, start)]

    while priority_queue:
        current_distance, current = heapq.heappop(priority_queue)
        if current_distance > distances[current]:
            continue

        for neighbor in graph.neighbors(current):
            weight = graph.weight(current, neighbor)
            if weight is None:
                continue
            distance = current_distance + weight
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                parent[neighbor] = current
                heapq.heappush(priority_queue, (distance, neighbor))

    return distances, parent

"""
Rebuild the path from start to end using a parent dictionary
produced by breadth-first search or Dijkstra.

parent - maps each node to the node that led to it
start  - the beginning of the path
end    - the end of the path
return the list of nodes from start to end, or None if no path exists
"""
def reconstruct_path(parent: Dict[str, Optional[str]], start: str, end: str) -> Optional[List[str]]:
    if end not in parent:
        return None
    path = []
    current = end
    while current is not None:
        path.append(current)
        current = parent.get(current)
    path.reverse()
    return path if path and path[0] == start else None

"""
Degree centrality: number of neighbors divided by (n - 1).
For a directed graph, uses out-degree.

graph - the graph to measure
return a dictionary mapping each node to its centrality score
"""
def degree_centrality(graph: Graph) -> Dict[str, float]:
    n = graph.number_of_nodes()
    if n <= 1:
        return {node: 0.0 for node in graph.nodes}
    return {node: len(graph.neighbors(node)) / (n - 1) for node in graph.nodes}

"""
Find the connected components of an undirected graph by
repeated depth-first search.

graph - the graph to search
return a list of sets, one set of nodes per component
"""
def connected_components(graph: Graph) -> List[Set[str]]:
    remaining = set(graph.nodes)
    components: List[Set[str]] = []
    while remaining:
        start = remaining.pop()
        component = depth_first_search(graph, start)
        components.append(component)
        remaining -= component
    return components
