# Programming Portfolio

Kevin Tieu  
October 2026

This repository holds the first checkpoint of my programming portfolio. It contains four programs and a Word document that presents them with a cover, a table of contents, and a technique table.

## Contents

| Folder | Language | Description |
|--------|----------|-------------|
| `Source/Lockbox/` | C | A command-line utility for file storage, environment handling, binary indexing, logging, process control, and a screen-based file browser. This project is still ongoing. |
| `Source/GraphNet/` | Python | A graph algorithms toolkit. Includes an adjacency-list graph, breadth-first and depth-first search, Dijkstra’s shortest path, and simple centrality measures. |
| `Source/Traffic_Light/` | Java | A red-yellow-green traffic light implemented as a finite state machine, with JUnit tests for state transitions and timing. |
| `Source/Multi_Connection_Chat/` | C# | A chat system with a Windows Forms GUI client and a multi-threaded server. Supports concurrent connections with separate ports for authentication, sending, and receiving messages. |
| `Tieu_K_Projects.docx` | — | The portfolio document. Open it in Word, right-click the table of contents, and choose Update Field to fill in the page numbers. |

## Build notes

**Lockbox** (Linux or WSL)
```
cd Source/Lockbox
make
./Tieu_K_lockbox
```

**GraphNet**
```
cd Source/GraphNet
python graph_analyzer.py --help
```

**Traffic Light**
Open the project in an IDE with JUnit support, or run the tests with Maven or Gradle.

**Multi-Connection Chat**
Open the solutions in Visual Studio. Start `ChatServer.Terminal`, then run the GUI client and connect to localhost.

## Comment style

Every file has a header naming the author, the course (or “Personal project”), and what the file does. Every function has a header above it stating what it does, its parameters, and what it returns.
