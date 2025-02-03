# Assembly-Optimized Game Project

## Overview

This project demonstrates the integration of assembly language optimizations in performance-critical sections of a C++ game implementation. The primary focus is on showcasing how assembly can be used to enhance performance in hot spots of the application.

## Key Features

- Custom assembly implementations for performance-critical functions
- Hybrid C++ and assembly architecture
- Performance comparisons between pure C++ and assembly-optimized versions

## Technical Implementation

### Assembly Integration

- Assembly routines optimize critical operations:
  - `SE.s`, `EA.s`, `SA.s` - Core assembly optimizations
  - `EX.s`, `EY.s` - Additional performance-critical routines
  - `R.s`, `S.s`, `C.s`, `G.s` - contain optimized assembly routines
- Hot paths identified and reimplemented in assembly for maximum performance
- Direct integration with C++ codebase through proper calling conventions

### Project Structure

- `CPP/` directory:
  - `game.cpp` - Main game logic
  - `kgh.h` - Header definitions
  - `class.cpp` - Core C++ implementations
  - `function.cpp` - Supporting functions
- `ASM/` directory:
  - `R.s` - Regular
  - `S.s` - SinPath
  - `C.s` - CurvePath
  - `G.s` - Gradient
  - `SE.s` - Segment
  - `SA.s` - StartAngle
  - `EA.s` - EndAngle
  - `EX.s` - EndX
  - `EY.s` - EndY
- `game.sh` - Build/run script

## Performance Highlights

- Assembly-optimized sections show significant performance improvements in:
  - Critical game calculations
  - Time-sensitive computations

## Building and Running

```bash
./game.sh
```
