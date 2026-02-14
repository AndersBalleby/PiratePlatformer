# Pirate Platformer

Et simpelt 2D platformer-spil skrevet i **C** med [**raylib**](https://www.raylib.com/).  
Projektet er lavet med inspiration fra [Clear Code's 2D Mario-style platformer](https://github.com/clear-code-projects/2D-Mario-style-platformer) skrevet i Python.

## Om spillet
**Pirate Platformer** er et spil som minder meget om Super Mario. Man hopper gennem klassiske platformer-baner, indsamler mønter og besejrer fjender.

## Teknologier

- **C** – valgte programmeringssprog  
- **raylib** – simpelt C-baseret game framework  
- **CMake** – til build og projektstruktur  

## Installation
### 1. Klon projektet og submoduler
```code
git clone --recurse-submodules https://github.com/AndersBalleby/PiratePlatformer.git
cd PiratePlatformer
```

### 2. Byg med CMake
```code
mkdir build
cd build
cmake ..
cmake --build .
```
### 3. Kør spillet
```code
./Pirate_Platformer
```
> Sørg for at du har raylib's dependencies (f.eks. X11, OpenGL, pthread på Linux)

## Projektstruktur
```text
PiratePlatformer/
├── src/          # Spilkode
├── resources/    # Graphics, lyde osv.
├── levels/       # Baner
├── external/     # raylib (submodul)
├── build/        # Midlertidig build-mappe
└── CMakeLists.txt
```
