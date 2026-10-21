# 🧩 MiniProj3 — Maze Generator

A C program that **randomly generates a maze** of a given size, draws it in the console, then **finds a path from the entrance to the exit** and calculates its weight.

The maze is represented as a **graph**: each cell is a vertex with a random weight, and passages between cells are edges.

---

## ✨ Features

- Generates mazes from **3×3** up to **361×361**
- Size, entrance, exit and generation mode can be entered manually or chosen at random
- Draws the maze in the console using ASCII characters (`_` and `|`)
- Checks that every cell is reachable — if not, the maze is generated again
- A timer running in a separate thread (`pthread`) asks after **15 seconds** whether to keep generating in the chosen mode
- Finds the path from the entrance to the exit (DFS) and calculates its weight
- Saves the results to `status.txt` and `path.txt`

---

## 📁 Project structure

```
MiniProj3/
├── README.md
└── src/
    ├── main.c      # main program logic
    ├── graph.c/h   # vertex structure, graph generation, maze drawing
    ├── func.c/h    # helpers: weights, connections, input handling, timer
    └── search.c/h  # searching for the maze exit
```

---

## ⚙️ Requirements

The program is meant for **Linux** (or WSL / macOS), because it uses:

- `pthread.h` — the timer thread
- `unistd.h` — the `sleep()` function
- `system("clear")` — clearing the console

You need **GCC** (or a compatible compiler).

---

## 🔨 Building and running

```bash
gcc src/*.c -o maze -lpthread
./maze
```

On Windows, the easiest way to run it is through **WSL**.

---

## 🎮 Usage

After starting, the program asks four questions in turn. Answer each with `y` (I'll enter it) or `n` (pick at random):

| Parameter | Range | Meaning |
|---|---|---|
| Size | 3–361 | side length of the square maze |
| Entrance | 1–size | column of the entrance on the **top** edge |
| Exit | 1–size | column of the exit on the **bottom** edge |
| Mode | 1–3 | how connections are generated (see below) |

Invalid values are detected and the program asks you to enter them again.

> The program's prompts and messages are in Polish.

### Generation modes

The mode controls how strongly the program **forces** connections to neighbouring cells. The higher the mode, the more often a connection is forced, which makes it easier to generate a valid maze at large sizes.

If no mode is given, it is chosen automatically:

| Maze size | Mode |
|---|---|
| 3–10 | 1 |
| 11–25 | 2 |
| 26–361 | 3 |

If a manually chosen mode doesn't produce a valid maze within 15 seconds, the program asks whether to continue or switch to automatic mode.

---

## 📄 Output files

### `status.txt`

A description of every vertex: its number, weight, and the numbers of the cells it is connected to.

```
| nr:  1 | waga: 2.37 | polaczenia:  2 |
| nr:  2 | waga: 0.84 | polaczenia:  5  3 |
| nr:  3 | waga: 4.12 | polaczenia: brak |
...
```

### `path.txt`

The path found from the entrance to the exit and its total weight.

```
Sciezka labiryntu: 2 -> 5 -> 8

Waga sciezki: 7.45
```

> The values above are only examples — the maze and weights are randomised on every run.

---

## 🧠 How it works

1. **Initialisation** — `size × size` vertices are created, each with a random weight between `0.01` and `4.99`. Cells on the edges and in the corners have restricted directions of movement.
2. **Generating connections** — starting from the entrance, `connect_graph` recursively picks random passages (up, down, left, right) to neighbours that haven't been visited yet. This produces a tree, i.e. a maze without cycles.
3. **Verification** — the program checks that every cell is reachable. If not, memory is freed and the maze is generated again.
4. **Drawing** — `print_maze` turns the graph into an ASCII picture.
5. **Path finding** — `find_exit` recursively (DFS) checks which branch leads to the exit. The program follows that branch step by step, recording each cell and summing the weights.

---

## 👤 Author

Project made for the **Fundamentals of Computer Science** course (Podstawy Informatyki) — labs, semester 1.
