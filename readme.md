
# CSE318 — Artificial Intelligence (Course Assignments)

This repository collects the offline assignments for the CSE318 Artificial Intelligence course. It contains four offline assignment directories (`offline1` → `offline4`). Each folder contains the problem statement, code, datasets, and short instructions below.

---

## Repository layout

- `offline1-A_star_algo/` — N-Puzzle (A* search) implementation, testcases, and solution code.
- `offline2-max cut/` — Max-Cut approximate/heuristic solutions (constructive, local search, GRASP) with datasets.
- `offline3 Reaction chain/` — Chain Reaction project with backend AI and a frontend web UI.
- `offline4-decission tree/` — Decision tree implementation, datasets and scripts for experiments.

---

**Quick start**: choose the `offlineN` folder you want to run and follow the per-assignment instructions below.

---

## Offline 1 — A* (N-Puzzle)

Location: `offline1-A_star_algo/`

What is included:
- `318_N_Puzzle_testcases/` — multiple input (`inNN.txt`) and expected output (`outNN.txt`) testcases for the N-puzzle.
- `problem_definition/` — assignment PDF (`CSE318-Offline1-Spec.pdf`).
- `solution/` — source files and binaries:
	- `2105160_main.cpp`, `Astarv1.hpp`, `Board.hpp`, `Heuristic.hpp`, `test.cpp`
	- `a.out`, `test.exe` (pre-built binaries)
	- `input.txt`, `output.txt` (examples)

How to run:

- Use the included binary (recommended when present):

	```bash
	cd "offline1-A_star_algo/solution"
	./a.out < input.txt
	```

- Or recompile from source (example):

	```bash
	cd "offline1-A_star_algo/solution"
	g++ -std=c++17 2105160_main.cpp test.cpp -o offline1
	./offline1 < input.txt
	```

Notes:
- The `318_N_Puzzle_testcases/` folder contains input files you can feed to the program to validate outputs.
- If the project expects specific header filenames, adjust the compile command accordingly. Pre-built `a.out` is the fastest way to test.

---

## Offline 2 — Max-Cut (Constructive / Local Search / GRASP)

Location: `offline2-max cut/`

What is included:
- C++ implementation files: `2105160_ConstructiveAlgorithms.cpp`, `2105160_ConstructiveAlgorithms.hpp`, `2105160_Graph.hpp`, `2105160_Grasp.hpp`, `2105160_LocalSearch.hpp`, `2105160_Report.hpp`, `2105160_main.cpp`.
- Run script: `2105160_run.sh`
- Dataset set: `set1/` contains many `.rud` graph files used as inputs.
- Report and PDF resources: `2105160.pdf`, `Offline_02_CSE318.pdf`.

How to run:

```bash
cd "offline2-max cut"
bash 2105160_run.sh
# or build manually
g++ -std=c++17 2105160_main.cpp 2105160_ConstructiveAlgorithms.cpp -o offline2
./offline2
```

Notes:
- The provided `2105160_run.sh` automates running the solver on datasets in `set1/`.
- Check the script if you want to modify which datasets are used or adjust parameters.

---

## Offline 3 — Chain Reaction (AI)

Location: `offline3 Reaction chain/`

What is included:
- Assignment PDF: `CSE 318 Assignment-03.pdf`.
- Project folder: `project/` containing the backend AI and the frontend UI.
    - `ai/` and auxiliary scripts for running tests.

How to run backend (Python):




Notes:
- The backend contains the AI logic (`ai.py`) and game state handling. The frontend is a separate web app.
- Look at `gamestate.txt` and example scripts to see expected inputs/outputs.

---

## Offline 4 — Decision Tree

Location: `offline4-decission tree/CSE 318 Offline 4/`

What is included:
- C++ and helper headers: `main.cpp`, `decissiontree.hpp`, `dataloader.hpp`, `node.hpp`, `criterion.hpp`.
- Python helper/report: `report.py`.
- Datasets: `Datasets/` and CSV result files `results_adult.csv`, `results_iris.csv`.
- A `run.sh` script and `a.out` binary are also included.

How to run:

```bash
cd "offline4-decission tree/CSE 318 Offline 4"
# Run the provided script (recommended)
./run.sh

# Or compile and run manually
g++ -std=c++17 main.cpp -o decision_tree
./decision_tree
```

Notes:
- `report.py` can be used to generate plots or summarize results from produced CSVs.
- Check `run.sh` for exact preprocessing and invocation parameters.

---
