# Stick Man Dance ASCII — Standalone C Edition

A lightweight, dependency-free C terminal animation featuring an animated stick figure, rendered entirely using ASCII characters.

## Features

- Animated dancing stick figure.
- Monochrome ASCII graphics.
- Real-time terminal rendering.
- Procedurally generated animation.
- Adjustable animation dimensions and speed.
- No external assets or libraries required.

## Requirements

- GCC (or another C compiler).
- VS Code or any terminal supporting ANSI escape sequences.

## Compile

Open the project folder in VS Code and select **Terminal → New Terminal**.

```powershell
gcc main.c -o stickman.exe
```

## Run

```powershell
.\stickman.exe
```

The animation plays directly in your terminal. Press `Ctrl+C` to stop it.

## Customization

Edit these constants near the top of `main.c`:

```c
#define W 80
#define H 30
#define FRAMES 240
#define DELAY_MS 70
```

- `W`: Animation width.
- `H`: Animation height.
- `FRAMES`: Total number of animation frames.
- `DELAY_MS`: Delay between frames in milliseconds.

Reduce `W` and `H` if your terminal window is small.

## Project Structure

```text
stick-man-dance-ascii/
├── main.c
├── README.md
└── .gitignore
```

## License

MIT License. Feel free to use, modify, and distribute this project.
