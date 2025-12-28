# [🇨🇳 中文版本](README_zh.md)

# Stanford CS106L — Course Materials and Assignments

This repository collects lecture materials, example code, homework and lab assignments for the Stanford CS106L course. It is intended to make it easy to browse, build, and run the course examples and assignment solutions.

Part 1 — Directory Descriptions

- `Assignments/`  
  Contains course homework and lab assignments. Each assignment generally lives in its own subdirectory and may include source files, tests, a `Makefile` or other build scripts, and a per-assignment `README.md` describing build/run instructions.

- `Lec*/` (for example `Lec2/`, `Lec10/`)  
  Lecture folders containing slides, example code, in-class exercises and notes for each lecture. Files here typically include `.cpp`, `.h`, `.txt`, and example build scripts or snippets used during the lecture.

- `My_Assignments/`  
  Personal or working copies of assignment solutions. Subdirectories (for example `assignment0/`) contain student implementations, quick test harnesses, and small helper utilities used to verify correctness.

- `.gitignore`  
  Ignore rules for build artifacts and IDE files. This repository already contains a `.gitignore` tuned to avoid object files, executables, and common IDE directories.

- `autograder/` (optional, may exist inside assignments)  
  Utilities and scripts used by the course autograder. If present, assignment runners or small helper sources live here.

- Top-level documentation files  
  Files like `README.md`, `LICENSE`, and per-assignment `README.md` files that explain how to build and run specific parts of the repository.

Part 2 — Top-level File Tree (navigation)

Use this tree as a quick reference to find lectures, assignments, and personal work:

```
Stanford_CS106L/
├── Assignments/
│   ├── assignment1/
│   │   ├── src/
│   │   ├── tests/
│   │   ├── Makefile
│   │   └── README.md
│   └── ...
├── Lec2/
├── Lec3/
├── Lec5/
├── Lec8/
├── Lec10/
├── Lec11/
├── Lec12/
├── Lec13/
├── Lec15/
├── Lec16/
├── Lec17/
├── My_Assignments/
│   ├── assignment0/
│   │   ├── main.cpp
│   │   └── (optional) autograder/
│   └── <your_solution_dirs>/
├── .gitignore
└── LICENSE (optional)
```

Build and run notes (general)

- If a `Makefile` exists inside a directory, use:
  ```bash
  make
  make test     # if provided
  make clean
  ```
- If a `CMake` workflow is used:
  ```bash
  mkdir -p build && cd build
  cmake ..
  make
  ```

Example: build/run for `My_Assignments/assignment0`

1. Change into the assignment directory:
   ```bash
   cd My_Assignments/assignment0
   ```
2. If a `Makefile` exists, run `make`. Otherwise compile manually; for a simple example:
   ```bash
   # If main.cpp depends on an autograder helper, compile both
   g++ -std=c++17 main.cpp autograder/utils.cpp -o assignment0
   ./assignment0
   ```
   Adjust compiler flags and source paths per the assignment's README.

