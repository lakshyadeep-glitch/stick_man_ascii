# Bad Apple ASCII — Standalone C Edition 🍎

A dependency-free C terminal animation with a monochrome ASCII aesthetic.

**Important:** This is an original procedural dancing-silhouette animation inspired by the broad black-and-white terminal-art look. It is not the original Bad Apple video, and it does not reproduce its frames or soundtrack.

## No external files required

This version needs:
- GCC (or another C compiler)
- A terminal with ANSI escape-sequence support

It does **not** need:
- MP4 video
- FFmpeg
- Python
- OpenCV
- Internet access at runtime

## Compile

Open this folder in VS Code, then open **Terminal → New Terminal**:

```powershell
gcc main.c -o badapple.exe
```

## Run

```powershell
.\badapple.exe
```

The animation plays directly in the terminal. Press `Ctrl+C` to stop early.

## Customize

Edit these constants near the top of `main.c`:

```c
#define W 80
#define H 30
#define FRAMES 240
#define DELAY_MS 70
```

- `W` and `H`: terminal animation dimensions.
- `FRAMES`: number of animation frames.
- `DELAY_MS`: delay between frames in milliseconds.

If your terminal is small, reduce `W` and `H` together.

## Project files

```text
bad-apple-ascii-standalone/
├── main.c
├── README.md
└── .gitignore
```

## License

MIT for this original source code.
