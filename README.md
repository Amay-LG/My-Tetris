# My-Tetris
A simple Tetris clone created in C++. Graphics done in SDL2.

Inspired by [Javier López's original project](https://javilop.com/gamedev/tetris-tutorial-in-c-platform-independent-focused-in-game-logic-for-beginners/), updated to use SDL2 for graphics.

## Building from Source

### 1. Clone the Repository

```bash
git clone [https://github.com/Amay-LG/My-Tetris](https://github.com/Amay-LG/My-Tetris.git)
cd My-Tetris
```

### 2. Install SDL2 Libraries

**On macOS (using Homebrew):**
```bash
brew install sdl2
```

**On Ubuntu/Debian (using APT):**
```bash
sudo apt-get update
sudo apt-get install libsdl2-dev
```

**On Windows (using MSYS2):**
1.  [Install MSYS2](https://www.msys2.org/).
2.  From the MSYS2 terminal, install the toolchain and SDL2:
    ```bash
    pacman -Syu
    pacman -S mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-SDL2
    ```
    *(You'll need to use the "UCRT64" terminal for `make` to work.)*

### 3. Compile the Game

Once the dependencies are installed, run `make`:

```bash
make
```

### 4. Run

```bash
./Tetris
```

### 5. Clean up executables

Run `make clean` to remove executables.

```bash
make clean
```
