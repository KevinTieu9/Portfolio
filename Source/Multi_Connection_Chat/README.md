# Multi-Connection Chat

**Course:** CS 346 — Fall 2020  
**Author:** Kevin Tieu

## Overview

A chat system with a Windows Forms GUI client and a multi-threaded server. Supports concurrent connections with separate ports for authentication, sending, and receiving messages.

## What the Program Does

The server listens on three ports:

1. Authentication (username and password, length-prefixed UTF-8).
2. Write channel for outgoing messages.
3. Read / broadcast channel for incoming messages.

The client has a login form and a main chat window. The server uses separate threads for the authenticator, receiver, and broadcasters.

## Files

| File | Description |
|------|-------------|
| Form1.cs | Login form |
| Form2.cs | Chat window |
| Server.cs | Server core |
| Authenticator.cs | Authentication |
| Receiver.cs | Incoming messages |
| Broadcaster.cs | Outgoing broadcasts |
| ChatUser.cs | Connected user |

## Techniques

- Multi-threaded server
- Sockets
- GUI client
- Concurrent connections

## Build and Run

Open the solutions in Visual Studio, start ChatServer.Terminal, then run the GUI client and connect to localhost.
