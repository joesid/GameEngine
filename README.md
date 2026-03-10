# World Engine | GameEngine

A 3D game application built with a custom engine using C++17 and OpenGL. The game features player-controlled mechanics, interactive UI, and physics-based gameplay elements including jumping platforms and projectile systems.

## Overview

This project implements a game application that extends the custom `eng::Engine` framework. It provides a complete game loop with scene management, UI interactions, and game object management including a controllable player character with shooting mechanics.

## Features

- **Scene Management**: Load and manage complex scenes from serialized formats
- **Player Controls**:
    - WASD keys for movement
    - Left mouse button for shooting projectiles
    - Space for jumping
    - ESC to toggle menu
- **UI System**: Main menu with Play and Quit buttons
- **Physics Integration**: Dynamic physics for player movement, bullets, and platforms
- **Audio Support**: Sound effects for shooting, jumping, and walking
- **Animation System**: Character animations including shooting sequences
- **Game Objects**:
    - `Player`: Controllable character with gun and animation support
    - `Bullet`: Physics-enabled projectiles spawned on firing
    - `JumpPlatform`: Interactive platforms that affect player movement

## Project Structure



## Requirements

- **Language**: C++17
- **Build System**: CMake 3.8+
- **Generator**: Ninja
- **Dependencies**:
    - Custom `eng` game engine library
    - GLFW3 (for input handling)
    - Standard C++ library

## Build Instructions


## Running the Game

After building, run the executable:


The game launches with a 1280x720 window. Use the main menu to start playing or quit.

## Game Controls

| Input | Action |
|-------|--------|
| W, A, S, D | Move player |
| Space | Jump |
| Left Mouse Button | Fire bullet |
| ESC | Toggle menu |

## Architecture

### Game Class

The `Game` class extends `eng::Application` and manages the overall game state:

- **RegisterTypes()**: Registers custom game object types (Player, Bullet, JumpPlatform) with the engine
- **Init()**:
    - Loads the scene from `scenes/scene.sc`
    - Sets up UI canvas with Play/Quit buttons
    - Configures game world appearance
    - Initializes button callbacks for menu interaction
- **Update()**:
    - Updates scene state each frame
    - Handles ESC key input to toggle between game and menu
- **Destroy()**: Cleanup on application shutdown

### Scene Management

Scenes are loaded from JSON-based `.sc` files containing:
- Game object hierarchy with transforms
- Component configurations (physics, audio, animation, etc.)
- Camera and canvas settings

### Physics & Collision

The physics system uses:
- RigidBody components for dynamic objects
- Collider shapes (spheres, etc.)
- Contact listeners for event-driven collision handling

## Scene File Location

Game scenes are loaded from `scenes/scene.sc` relative to the asset directory.

