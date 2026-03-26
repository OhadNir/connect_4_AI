# CLAUDE.md — Connect-4 AI Codebase Guide

## Project Overview

A command-line Connect-4 game where a human player competes against an AI. The AI uses the **minimax algorithm with alpha-beta pruning** and a positional heuristic evaluation function. This is a pure game-tree search approach — no machine learning or neural networks.

---

## Repository Structure

```
connect_4_AI/
├── main.cpp          # Entry point: game loop, user I/O
├── GameTree.h/.cpp   # AI logic: tree generation, minimax, move selection
├── node.h            # Node class header (note: lowercase filename)
├── Node.cpp          # Node class: board state, evaluation, rendering
├── connect_4_ai.exe  # Pre-compiled Windows binary (do not edit)
├── a                 # Pre-compiled Linux binary (do not edit)
├── .gitignore        # Python template (not C++-specific; mostly irrelevant)
└── README.md         # Minimal title-only file
```

**Important:** The header file is `node.h` (lowercase) but `main.cpp` includes `"Node.h"` (capitalized). On case-sensitive Linux filesystems this will fail to compile. On Windows (case-insensitive) it works. Any new files referencing the Node header should use `#include "node.h"`.

---

## Building

There is no Makefile or CMake. Compile manually:

```bash
# Linux
g++ -o connect_4_ai main.cpp GameTree.cpp Node.cpp

# Windows (MinGW)
g++ -o connect_4_ai.exe main.cpp GameTree.cpp Node.cpp
```

Recommended depth for the AI is **4** (as noted in the program itself). Higher depths increase search time exponentially.

---

## Running

```bash
./connect_4_ai   # Linux
connect_4_ai.exe # Windows
```

The program prompts for:
1. **AI search depth** — how many moves ahead the AI looks (4 recommended)
2. **Suggestions ON/OFF** — enter `1` to enable move hints from the AI

Player always moves first. Columns are numbered 1–7 for the user.

---

## Architecture

### Class Hierarchy

```
GameTree
├── owns: Node root       (current game state, root of search tree)
└── calls: minimax, generateTree

Node
├── owns: int** board     (7 columns × 6 rows, heap-allocated)
├── owns: list<Node*> children
└── provides: evaluationBoard(), print_board(), numCol_open()
```

### Board Representation

- `board[column][row]` — column-major indexing (x first, y second)
- Dimensions: 7 columns (index 0–6), 6 rows (index 0–5)
- Row 0 is the **top**, row 5 is the **bottom**
- Cell values: `1` = AI piece (O), `-1` = player piece (X), `0` = empty (*)
- A column is full when `board[col][0] != 0`

### Player Encoding

| Value | Meaning       | Symbol |
|-------|---------------|--------|
| `1`   | AI            | `O`    |
| `-1`  | Human player  | `X`    |
| `0`   | Empty cell    | `*`    |

### Turn Convention

- AI moves as **maximizer** (player = 1) in minimax
- Human moves as **minimizer** (player = -1) in minimax
- `generateTree` alternates by negating the player value

---

## Key Algorithms

### `GameTree::generateTree(Node&, int depth, int player)`

Recursively builds the game tree from the current node:
- Terminates when `depth == 0`, no open columns, or board score ≥ 50000 or ≤ -50000 (terminal state)
- If the node already has children (tree was built before), recurses into existing children
- Otherwise creates new child `Node`s for each open column
- Sets `gameOver = true` on terminal nodes

### `GameTree::minimax(Node&, int depth, int alpha, int beta, int player)`

Standard minimax with alpha-beta pruning:
- `player == 1` (AI): maximizer
- `player == -1` (human): minimizer
- Initial alpha/beta window: `-1010` to `1010`
- Updates `boardsAnalyzed`, `numberOfWinStatesPY`, `numberOfWinStatesAI` as side effects
- Returns the evaluated score for the node

### `Node::evaluationBoard()`

Scores the board by scanning all 4-cell windows in four directions:

| Direction    | Outer loop       | Inner window    |
|--------------|------------------|-----------------|
| Horizontal   | rows 0–5         | 4 consecutive cols |
| Vertical     | columns 0–6      | 4 consecutive rows |
| Diagonal ↗   | 4 column offsets | 4 diagonal cells   |
| Diagonal ↖   | 4 column offsets | 4 diagonal cells   |

### `Node::scoring(int ai, int player, int blank)`

Scores a single 4-cell window:

| AI pieces | Blanks | Score     | Player pieces | Blanks | Score     |
|-----------|--------|-----------|---------------|--------|-----------|
| 1         | 3      | +2        | 1             | 3      | -1        |
| 2         | 2      | +6        | 2             | 2      | -6        |
| 3         | 1      | +12       | 3             | 1      | -1000     |
| 4         | 0      | +100000   | 4             | 0      | -100000   |

Terminal states (4-in-a-row) are detected in `generateTree` using the ±50000 threshold.

---

## Game Flow

```
main()
  ├── Create GameTree(depth)       → generateTree from empty board
  └── Loop:
       ├── WinDraw() → break if game over
       ├── Player turn:
       │    ├── print board
       │    ├── (optional) suggestMove()
       │    └── playerMove(col-1)  → find child, regenerate tree, minimax
       └── AI turn:
            └── aiMove()           → pick best child, regenerate tree
```

---

## Statistics Tracked

After every game, `main.cpp` prints:

| Statistic | Method |
|-----------|--------|
| Total moves made | `NumberOFMoves()` |
| Board states generated | `NumberOfBoardsGenerated()` |
| Boards analyzed (leaf nodes) | `NumberOfBoardsAnalyzed()` |
| Player win states within depth | `NumberOfWinStatesPY()` |
| AI win states within depth | `NumberOfWinStatesAI()` |

---

## Known Issues / Limitations

- **Memory leaks**: `Node` objects are heap-allocated with `new` but never deleted. The tree is effectively leaked each time a move is made and a new root is assigned.
- **Case mismatch**: `node.h` vs `#include "Node.h"` — will fail on Linux without a fix.
- **No tests**: No unit tests or test framework exists.
- **No build system**: No Makefile or CMake; must compile manually.
- **`.gitignore` is Python-specific**: Does not cover C++ artifacts (`*.o`, `*.exe`, `a`).
- **Alpha-beta logic**: The alpha update in the maximizer uses `if (alpha > value)` instead of the conventional `if (value > alpha)` — this may reduce pruning effectiveness but does not break correctness.

---

## Conventions to Follow

- **C++ standard**: Code uses C++11-compatible style (range-for loops not used; prefer maintaining consistency with existing iterator-based loops).
- **Naming**: Methods use camelCase; member variables are lowercase (`boardsGenerated`, `treedepth`). Follow the existing style.
- **Board access**: Always use `board[column][row]` ordering.
- **Player values**: Always use `1` for AI and `-1` for human; never use `0` or other values.
- **Column indexing**: Internal logic uses 0–6; user-facing display uses 1–7. Convert with `col - 1` on input and `col + 1` on output.
- **No external dependencies**: The project uses only the C++ standard library (`iostream`, `cstdlib`, `list`).
- **No new files without cause**: The project is intentionally flat and minimal. Avoid adding directories or splitting logic unnecessarily.

---

## Development Branch

Active development happens on: `claude/add-claude-documentation-UE7JI`
Main branch: `master`
