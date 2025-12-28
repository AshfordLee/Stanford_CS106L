# [🇺🇸 English version](README.md)

# Stanford CS106L — 课程资料与作业集合（中文）

本仓库汇集了 Stanford CS106L 课程的讲义、示例代码、作业与实验，方便浏览、编译与运行课堂示例与作业实现。

第一部分 — 目录说明

- `Assignments/`  
  存放课程的作业与实验，每个作业通常有独立子目录，可能包含源代码、测试用例、`Makefile` 或其它构建脚本，以及每个作业的 `README.md`（说明如何构建/运行/测试）。

- `Lec*/`（例如 `Lec2/`, `Lec10/`）  
  每次讲座对应的文件夹，包含幻灯片、示例代码、课堂练习与笔记。常见文件类型包括 `.cpp`、`.h`、`.txt` 等，以及示例的构建片段或脚本。

- `My_Assignments/`  
  个人或正在开发的作业解答目录。子目录（例如 `assignment0/`）包含学生实现、快速测试脚本以及用于验证正确性的辅助工具。

- `.gitignore`  
  仓库的忽略规则，用于排除编译产物和 IDE 文件。仓库中已有针对对象文件、可执行文件和常见 IDE 目录的规则。

- `autograder/`（可选，可能位于某些 assignment 内）  
  自动评分器的工具和脚本。如果存在，assignment 的运行器或辅助源码通常放在此处。

- 顶层文档文件  
  如 `README.md`、`LICENSE` 以及各 assignment 的局部 `README.md`，用于记录如何构建和运行特定部分。

第二部分 — 顶层文件树（快速导航）

以下树形结构用于快速定位讲义、作业及个人代码：

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

构建与运行（通用说明）

- 若目录内存在 `Makefile`，通常使用：
  ```bash
  make
  make test     # 若提供
  make clean
  ```
- 若使用 `CMake`：
  ```bash
  mkdir -p build && cd build
  cmake ..
  make
  ```

示例：`My_Assignments/assignment0` 的编译与运行

1. 进入作业目录：
   ```bash
   cd My_Assignments/assignment0
   ```
2. 若存在 `Makefile`，运行 `make`。否则可手动编译，例如本仓库示例：
   ```bash
   # 如果 main.cpp 依赖 autograder 辅助文件，一并编译
   g++ -std=c++17 main.cpp autograder/utils.cpp -o assignment0
   ./assignment0
   ```
   根据每个作业的具体说明调整编译选项和源码路径。



