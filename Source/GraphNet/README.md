# Project_GraphNet
# Graph Algorithms and Network Analysis Toolkit
# Author: Kevin Tieu
# Description: A Python implementation of core graph algorithms and a network
# analysis toolkit demonstrating discrete mathematics concepts with real-world
# applications in routing, social networks, and dependency analysis.
# Requirements: networkx, matplotlib (optional for visualization)

## Installation

```bash
pip install -r requirements.txt
```

## Usage

Run the analyzer:

```bash
python graph_analyzer.py
```

Or import the modules:

```python
from graph_core import Graph
from algorithms import breadth_first_search, dijkstra_shortest_path
```

## Project Structure

- graph_core.py          : Pure Python graph data structure
- algorithms.py          : Core graph algorithms (BFS, DFS, Dijkstra, centrality)
- graph_analyzer.py      : Command-line network analysis tool
- examples/              : Sample edge lists and demonstration scripts
- tests/                 : Basic correctness tests
- requirements.txt       : Dependencies
- README.md              : This file

## Mathematical Foundations

This project implements standard discrete mathematics results from graph theory:

- Breadth-first search (BFS) and depth-first search (DFS) for traversal and connectivity
- Dijkstra's algorithm for single-source shortest paths on weighted graphs with non-negative weights
- Degree centrality and simple PageRank-style ranking for network analysis
- Connected components for identifying clusters

Real-world applications include route planning, social influence measurement, and software dependency resolution.

## Visualization

```bash
python visualize_example.py
```

This produces `examples/humboldt_cities_network.png` using NetworkX and matplotlib.