# ChessBuddy

ChessBuddy is a personal C++ project developed as part of my programming portfolio. The project is intended as a practical exercise to sharpen my C++ skills through the implementation of non-trivial game logic, rather than to compete with full-scale chess engines.

## What it does

ChessBuddy implements the core rules of chess:

* Board representation and piece management
* Turn‑based gameplay (white / black)
* Legal move validation per piece
* Special moves: castling, en passant, and pawn promotion
* Basic check detection

The engine runs in a console environment and is designed to be easy to test and extend.

## Design approach

The code is written in modern C++ with an object‑oriented structure:

* A `Board` class responsible for game state
* A base `Piece` abstraction with derived classes for each piece type
* Explicit `movement` structures to represent moves
* Clear separation between game flow and board logic

The project evolved iteratively, with frequent refactoring to improve clarity as new rules were added. This mirrors how real‑world systems tend to grow over time.

## Why this project

I built ChessBuddy to strengthen my C++ skills, especially:

* Object‑oriented design
* Rule‑based logic
* Debugging complex state interactions
* Writing maintainable code with tests in mind

## Status

The project is functional and actively evolving. Future improvements may include:

* More exhaustive check and checkmate handling
* Improved move generation and validation structure
* Simple AI
* Graphical interface
* An optional networked mode to support playing over a network

## Build

The project can be built using a standard C++ compiler (e.g. `g++`) without external dependencies.

---