"""
graph_analyzer.py
Personal project — GraphNet

Author: Kevin Tieu

Command-line network analysis tool. Loads an edge list and runs
breadth-first search, depth-first search, Dijkstra, centrality,
and connected-component queries.
return nothing
"""

import argparse
import sys
from typing import Optional
from graph_core import Graph
from algorithms import (
    breadth_first_search,
    depth_first_search,
    dijkstra_shortest_path,
    reconstruct_path,
    degree_centrality,
    connected_components,
)

"""
Load a graph from a simple edge-list file.
Each line is: source target [weight]. Lines starting with # are skipped.
file_path - path to the edge-list file
directed  - True for a directed graph, False for undirected
return the loaded Graph
"""
def load_edge_list(file_path: str, directed: bool = False) -> Graph:

    graph = Graph(directed=directed)
    with open(file_path, "r", encoding="utf-8") as handle:
        for line_number, line in enumerate(handle, start=1):
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            parts = line.split()
            if len(parts) < 2:
                print(f"Warning: skipping malformed line {line_number}: {line}", file=sys.stderr)
                continue
            source, target = parts[0], parts[1]
            weight = float(parts[2]) if len(parts) >= 3 else 1.0
            graph.add_edge(source, target, weight)
    return graph

"""
Read command-line options, load the edge list, and run the
requested graph queries.
return nothing
"""
def main() -> None:

    parser = argparse.ArgumentParser(
        description="Graph algorithms and network analysis toolkit (Kevin Tieu)."
    )
    parser.add_argument("edge_file", help="Path to edge-list file")
    parser.add_argument("--directed", action="store_true", help="Treat the graph as directed")
    parser.add_argument("--start", help="Start node for path algorithms")
    parser.add_argument("--end", help="End node for path reconstruction")
    parser.add_argument("--algorithm", choices=["bfs", "dfs", "dijkstra", "centrality", "components"],
                        default="components", help="Algorithm to run")
    args = parser.parse_args()

    try:
        graph = load_edge_list(args.edge_file, directed=args.directed)
    except FileNotFoundError:
        print(f"Error: file not found: {args.edge_file}", file=sys.stderr)
        sys.exit(1)

    print(f"Loaded graph with {graph.number_of_nodes()} nodes and {graph.number_of_edges()} edges.")
    print(graph)
    print()

    if args.algorithm == "components":
        components = connected_components(graph)
        print(f"Connected components ({len(components)}):")
        for index, component in enumerate(components, start=1):
            print(f"  Component {index}: {sorted(component)}")

    elif args.algorithm == "centrality":
        centrality = degree_centrality(graph)
        print("Degree centrality (sorted):")
        for node, score in sorted(centrality.items(), key=lambda item: item[1], reverse=True):
            print(f"  {node}: {score:.4f}")

    elif args.algorithm in ("bfs", "dfs", "dijkstra"):
        if not args.start:
            print("Error: --start is required for path algorithms.", file=sys.stderr)
            sys.exit(1)
        if args.algorithm == "bfs":
            parent = breadth_first_search(graph, args.start)
            print(f"BFS parent tree from {args.start}:")
            for node, parent_node in sorted(parent.items()):
                print(f"  {node} <- {parent_node}")
            if args.end:
                path = reconstruct_path(parent, args.start, args.end)
                print(f"Path to {args.end}: {' -> '.join(path) if path else 'unreachable'}")

        elif args.algorithm == "dfs":
            reachable = depth_first_search(graph, args.start)
            print(f"DFS reachable nodes from {args.start}: {sorted(reachable)}")

        elif args.algorithm == "dijkstra":
            distances, parent = dijkstra_shortest_path(graph, args.start)
            print(f"Dijkstra distances from {args.start}:")
            for node in sorted(distances):
                dist = distances[node]
                print(f"  {node}: {dist if dist != float('inf') else 'inf'}")
            if args.end:
                path = reconstruct_path(parent, args.start, args.end)
                if path:
                    total = distances[args.end]
                    print(f"Shortest path to {args.end} (distance {total}): {' -> '.join(path)}")
                else:
                    print(f"{args.end} is unreachable from {args.start}.")

if __name__ == "__main__":
    main()
