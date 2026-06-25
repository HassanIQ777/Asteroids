# Asteroids

A C++ clone of the classic arcade game, built on top of [Tebya](https://github.com/HassanIQ777/Asteroids/tree/main/TebyaEngine) — a custom SDL2 game engine. Dodge rocks, shoot rocks, become one with the void.

The window is 1000×800. The camera follows your ship with lerped smoothing. There is no escape. (Well, there's `ESC`, which sends you back to the start menu. That's the only escape.)

---

## Gameplay

- **Shoot** to destroy asteroids
- **Survive** as long as possible — waves keep spawning
- **Die** and get sent to the death screen
- **Try again** because you will

The world is theoretically infinite — asteroids spawn continuously and the camera tracks the player freely. The asteroid pool refills whenever it drops below 50, keeping the chaos steady.

---

## Controls

| Key | Action |
|---|---|
| `W` / `↑` | Thrust forward |
| `A` / `←` | Rotate left |
| `D` / `→` | Rotate right |
| `SPACE` | Shoot (0.2s cooldown) |
| `ESC` | Return to start menu |

---

## Features

- **Custom game engine (Tebya)** — built on SDL2, compiled separately as `libTebya.a` and linked in
- **Scene system** — `StartMenu`, `Playing`, and `DeathMenu` states managed via `Asteroids::UI_State`
- **TextureManager** — loads and indexes all game textures (asteroid, ship, bullet, heart) by integer ID
- **Camera with lerp follow** — camera smoothly chases the player at `dt * 8.0f` interpolation speed, capped to 1.0
- **Bullet system** — `BulletManager` handles spawning, updating, and rendering projectiles; 0.2s fire rate
- **Asteroid wave spawning** — starts with 20 asteroids, continuously replenishes 1-at-a-time below a threshold of 50
- **Collision handling** — `Entities::handleCollisions()` covers bullet-asteroid and player-asteroid interactions
- **Damage flash effect** — `damage_flash` on the player renders a visual hit indicator
- **Heart HUD** — player HP rendered as heart icons via `renderHearts()`
- **Audio** — shooting plays `shoot.wav` via a `static Audio` instance at volume 50
- **Delta time** — all movement and timers are driven by `g.delta_time.deltaTime()` for framerate-independent physics

---

## Architecture

```
Asteroids/
├── main.cpp                  # Game loop, state machine, entity setup
├── include/
│   ├── scenes.hpp            # Scene init functions (StartMenu, DeathMenu)
│   └── Math.hpp              # lerp() and other math helpers
├── src/                      # Game source files (entities, player, bullets, etc.)
├── assets/
│   ├── Asteroid.png          # Asteroid sprite (texture ID 0)
│   ├── Kla'ed.png            # Player ship sprite (texture ID 1)
│   ├── 03.png                # Bullet sprite (texture ID 2)
│   ├── heart.png             # HP heart icon (texture ID 3)
│   ├── Xirod.otf             # UI font (used at sizes 20, 25, 30)
│   └── shoot.wav             # Shoot sound effect
├── TebyaEngine/              # The Tebya engine (built as a static library)
│   └── lib/<mode>/libTebya.a
├── libutils/                 # Utility library
├── Makefile
└── compile_flags.txt
```

The engine exposes a `tebya` namespace with: `Globals` (singleton game state), `init()` / `update()` / `present()` / `quit()`, `TextureManager`, `Input`, `Audio`, `Colors`, `Scene`, `Text`, `Timer`, and `setScreenDimensions()`.

---

## Building

### Dependencies

- `g++` with C++20 support
- `SDL2`
- `SDL2_image`
- `SDL2_ttf`
- `SDL2_mixer`

Install on Debian/Ubuntu:
```bash
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
```

On Arch:
```bash
sudo pacman -S sdl2 sdl2_image sdl2_ttf sdl2_mixer
```

### Compile

```bash
git clone https://github.com/HassanIQ777/Asteroids
cd Asteroids
make
```

The Makefile first builds `TebyaEngine` as a static library, then compiles and links the game against it.

```bash
# Release build (default, -O2 -DNDEBUG)
make

# Debug build (ASan + UBSan, -g -O0 -DDEBUG)
make debug

# Build and run immediately
make run

# Clean game objects only
make clean

# Clean everything including TebyaEngine
make cleanall

# Full rebuild from scratch
make rebuild
```

Binaries land in `bin/release/Asteroids` or `bin/debug/Asteroids`.

---

## Running

```bash
./bin/release/Asteroids
```

---

## License

MIT — shoot freely.

---

*Made by [HassanIQ777](https://github.com/HassanIQ777)*