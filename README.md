# ⭕ Tic-Tac-Toe (SFML C++) ❌

A graphical Tic-Tac-Toe game built with **C++17** and **SFML 3**. The project features an animated UI transition sequence, support for both **Single-player** and **Multi-player** local game modes, responsive layout scaling, and real-time session tracking.

Developed inside **Visual Studio Code / Visual Studio** using native Windows configurations.

---

## ✨ Features

- 🎮 **Two Game Modes:**
  - **Single-Player:** Match your wits against an automated computer opponent using randomized state verification.
  - **Multi-Player:** Play locally with a friend on the same screen, passing the turn smoothly.
- ⏳ **Advanced Transition States:** Implements a professional state-machine workflow (`GameTransitionSequence`):
  - `StartingMenu` $\rightarrow$ `Playing` $\rightarrow$ `DrawingLine` (Animated win-line highlight) $\rightarrow$ `ResultMessage` (Dark overlay pop-up) $\rightarrow$ `FinalMenu`.
- 📊 **Session Statistics Tracker:** Persistently tracks Wins for **X**, Wins for **O**, and total **Draws** during a gameplay session.
- 📐 **Dynamic Layout Engine:** Fully responsive drawing system that recalculates grid properties, cell spaces, button bounds, and geometry configurations instantly when resizing the window.
- 🎨 **Sleek Graphics & Visuals:** Designed with eye-catching contrasting neon elements (Custom Lime Green for **X** and Deep Cyan for **O**).

---

## 🛠 Project Architecture

The codebase relies on a modular OOP design splitting logic, rendering, and engine flow:

- **`Types.h`**: Houses global configurations (`Config` namespace), shared geometric structures (`Clickable` bounding boxes), game tracking structures (`WinInfo`, `GameStatistics`), and state definitions (`GameState`, `GameTransitionSequence`).
- **`Game`**: Governs core game rules, winning combinations array tracking, turn handling, and actions.
- **`Graphics`**: Wraps the SFML window canvas, handles font/text calculations, absolute button coordinate mappings, grid render mechanics, and color profiles.
- **`GameEngine`**: The orchestrator core driving the primary system loop (`run()`), processing window/mouse events, updating game cycles, and ticking interpolation clocks.

├── bin/
│   ├── sfml-graphics-3.dll
│   ├── sfml-system-3.dll
│   └── sfml-window-3.dll
├── TicTacToe/
│   ├── include/
│   │   ├── Game.h
│   │   ├── GameEngine.h
│   │   ├── Graphics.h
│   │   └── Types.h
│   ├── src/
│   │   ├── Game.cpp
│   │   ├── GameEngine.cpp
│   │   ├── Graphics.cpp
│   │   └── main.cpp
│   ├── assets/
│   │   └── arial.ttf
│   ├── TicTacToe.vcxproj
│   └── TicTacToe.vcxproj.filters
└── TicTacToe.sln

---

## 🚀 Getting Started

### Prerequisites

- **Operating System:** Windows 10 / 11 (x64 or x86)
- **Compiler:** MSVC v145 (Visual Studio 2022 toolchain or newer)
- **Language Standard:** C++17 or superior
- **Dependency:** SFML 3.0.2 (Precompiled for MSVC 64-bit placed at `C:\SFML-3.0.2_msvc64\` or configured locally)

### Installation & Compilation

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/your-username/tictactoe-sfml.git](https://github.com/your-username/tictactoe-sfml.git)
   cd tictactoe-sfml
   ```

2. **Build via Visual Studio:**
   - Double-click `TicTacToe.sln` to launch the workspace.
   - Set your Target Platform to **x64** or **x86** and select **Debug** or **Release**.
   - Build the solution (`Ctrl + Shift + B`).

3. **Running the Application:**
   Ensure the three core dynamically linked library dependencies from the `bin/` folder are located in the same directory as your generated executable (`.exe`):
   - `sfml-graphics-3.dll`
   - `sfml-system-3.dll`
   - `sfml-window-3.dll`

---

## 🎮 How to Play

1. **Main Menu:** Click **Single-Player** to practice against the machine or **Multi-Player** to control both sides manually.
2. **Gameplay:** Click inside any of the 9 layout squares to make your move. **X** always moves first.
3. **Endgame:** Once a win state is recognized, the game highlights the winning row/column/diagonal vector, displays a stylized outcome box, and transitions you to the score summary dashboard.
4. **Looping:** Click **Play Again** to clear the board while retaining historical session metrics, or **Main Menu** to reselect game configurations.
