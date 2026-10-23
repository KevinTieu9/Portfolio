"""
visualize_example.py
Demonstration of visualization using NetworkX (optional dependency).
Author: Kevin Tieu
"""

import matplotlib.pyplot as plt
import networkx as nx
from graph_core import Graph

def to_networkx(graph: Graph) -> nx.Graph:
    """Convert the pure Python Graph to a NetworkX graph for visualization."""
    nx_graph = nx.DiGraph() if graph.directed else nx.Graph()
    for source in graph.nodes:
        for target, weight in graph.adjacency[source].items():
            if graph.directed or source < target:  # avoid duplicate undirected edges
                nx_graph.add_edge(source, target, weight=weight)
    return nx_graph

def main() -> None:
    graph = Graph()
    # Humboldt cities sample
    graph.add_edge("Arcata", "Eureka", 25)
    graph.add_edge("Arcata", "McKinleyville", 8)
    graph.add_edge("Eureka", "Fortuna", 20)
    graph.add_edge("McKinleyville", "Trinidad", 12)
    graph.add_edge("Trinidad", "Eureka", 30)
    graph.add_edge("Fortuna", "RioDell", 10)
    graph.add_edge("RioDell", "Arcata", 45)

    nx_graph = to_networkx(graph)
    position = nx.spring_layout(nx_graph, seed=42)
    edge_labels = {(u, v): data["weight"] for u, v, data in nx_graph.edges(data=True)}

    plt.figure(figsize=(8, 6))
    nx.draw(nx_graph, position, with_labels=True, node_color="lightblue",
            node_size=1200, font_size=10, font_weight="bold")
    nx.draw_networkx_edge_labels(nx_graph, position, edge_labels=edge_labels)
    plt.title("Humboldt County Cities Network (edge weights = distance)")
    plt.tight_layout()
    plt.savefig("examples/humboldt_cities_network.png", dpi=150)
    print("Saved visualization to examples/humboldt_cities_network.png")
    # plt.show()  # Uncomment for interactive display

if __name__ == "__main__":
    main()
