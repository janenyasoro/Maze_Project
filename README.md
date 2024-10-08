# The Maze Project
![photo1](https://github.com/user-attachments/assets/953bcbf7-d89c-439d-8d33-81725c901332)



The **Maze Project** is a 3D Maze game that uses ray casting to render a 2D map into a 3D navigable world! It is built using the **SDL2** library in **C** and runs on **Ubuntu**. Navigate through the maze and explore the 3D world generated by the raycasting algorithm.

## Project Links
- **Deployed Site**: https://janenyasoro.github.io/Maze_Project/
- **Final Project Blog Article**: [Maze Project Blog](#) (Link to your blog post)
- **Author's LinkedIn**: [Jane Nyasoro](https://www.linkedin.com/in/jane-nyasoro/)

---

## Introduction

The Maze Project is a fun, interactive 3D game where the player can move through a maze rendered using raycasting. The game demonstrates the power of **SDL2** for 3D rendering and game development. This project can serve as an introduction to game development, C programming, and graphics rendering using SDL2.

### About SDL2 

Simple DirectMedia Layer (**SDL2**) is a cross-platform development library that provides low-level access to audio, keyboard, mouse, joystick, and graphics hardware. It supports rendering via OpenGL and Direct3D and is widely used in video playback software, emulators, and popular games.

---

## Screenshot

 https://youtu.be/6T2N8gNUTQ8
---

## Installation

To set up the project locally, clone the repository and follow the instructions below.

### Prerequisites

Ensure you have the following installed:
- GCC (Gnu Compiler Collection)
- SDL2 Development Libraries
- Make (for running build commands)

### Installation Steps

1. Clone the repository:
    ```bash
    git clone https://github.com/janenyasoro/Maze_Project.git
    cd Maze_Project
    ```
2. Install SDL2 (Ubuntu):
    ```bash
    sudo apt-get install libsdl2-dev
    ```

3. Build the project:
    ```bash
    make
    ```

---

## Usage

Once you have installed and compiled the project, you can run the Maze game as follows:

1. Execute the binary directly:
    ```bash
    ./maze
    ```

2. Or, use the make command:
    ```bash
    make run
    ```

### Controls

- **Move Forward/Backward**: Up/Down Arrow Keys or `W` / `S` keys
- **Turn Camera**: Left/Right Arrow Keys or `A` / `D` keys

---

## Compilation

To compile the project manually, use the following GCC command:

```bash
gcc -Wall -Werror -Wextra -pedantic ./src/*.c -lm -o maze `sdl2-config --cflags` `sdl2-config --libs`
```

This will compile the source files and generate the executable for the Maze game.

---

## Flowchart

Include a flowchart that represents how the game logic and raycasting work. (Update the link with the flowchart image)

![image](https://github.com/user-attachments/assets/c83a9bb3-691a-4d4e-abae-8571b82e6156)


---

## Contributing

We welcome contributions to the Maze Project! Here's how you can help:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Submit a pull request describing your changes.

For major changes, please open an issue to discuss what you would like to change.

---

## Related Projects

- [Raycasting in Games](#)
- [SDL2 Tutorials](#)

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.



