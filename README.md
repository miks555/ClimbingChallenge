# Climbing Challenge
![image](https://github.com/user-attachments/assets/cefb028a-eb3a-49b3-bbfa-50501a340477)



## Overview
**Climbing Challenge** is a 2D platformer game where the player controls a climber attempting to ascend a mountain while avoiding obstacles and collecting supplies. The game features dynamic difficulty scaling, physics-based movement, and an immersive audiovisual experience.

## Features

### General
- A vertically scrolling **map** bounded by mountain walls on the left and right sides.
- A **camera** that follows the player character.
- A **supply meter** that starts full and depletes over time. Reaching zero ends the game.
- The **score** is determined by the maximum height reached.
- **Time-based mechanics** affecting difficulty and pacing.
- A **main menu** with options for fullscreen or windowed mode and difficulty selection.
- **Difficulty-dependent parameters**, such as:
  - Probability of rockfalls and supply packs appearing.
  - Rate of supply depletion.
- **Background music**.
- Unified **sound levels** (89 dB standard).

### Player Character
- **Animated movement**, including jumping and directional changes (4-frame animation).
- **Subject to gravity**.
- **Game over** when falling beyond a certain velocity threshold.
- **Movement controlled via:**
  - **Jump:** `Spacebar`
  - **Left/Right Movement:** `A/D` keys
- **Sound effects** for movement actions.

### Platforms
- **Generated** within the camera's view and removed when out of sight.
- Serve as **jumpable surfaces** for the player.
- **Appear randomly** above the player.
- Ensure **progression to higher altitudes**.

### Supply Packs
- **Animated objects**.
- **Spawn** within the camera's view and are removed when out of sight.
- **Restore the supply meter** upon collection.
- **Appear randomly** (max 20 at a time).
- **Disappear upon pickup** with an associated sound effect.

### Falling Rocks
- **Animated objects**.
- **Spawn** within the camera's view and are removed when out of sight.
- **Decrease the supply meter** upon collision with the player.
- **Appear randomly** (max 1000 at a time).
- **Disappear upon collision** with an associated sound effect.
- **Increase in frequency** over time.

## Dependencies
- **Windows:** openal32.dll
- **Linux:** OpenAL package (`libopenal1` or `libopenal.so`)

## License
**MIT**
