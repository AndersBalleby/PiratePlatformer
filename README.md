# 🏴☠️ Pirate Platformer

Et simpelt 2D platformer-spil skrevet i **C** med [**raylib**](https://www.raylib.com/).  
Projektet er lavet som en læringsrejse i C-programmering og spiludvikling – med inspiration fra [Clear Code's 2D Mario-style platformer](https://github.com/clear-code-projects/2D-Mario-style-platformer) skrevet i Python.

## 🎮 Om spillet

I **Pirate Platformer** spiller du som en pirat, der hopper gennem klassiske platformer-baner, undgår farer og måske finder skjulte skatte.  
Spillet er under udvikling, og formålet er både at eksperimentere med:

- Grundlæggende game loop i C  
- Brug af raylib til rendering, input og kollisionsdetektion  
- Egne dataformater til fx baner eller assets  

## 🧰 Teknologier

- **C** – lavniveau programmering og læring  
- **raylib** – simpel og kraftfuld C-baseret game framework  
- **CMake** – til build og projektstruktur  

## 📦 Installation
### 1. Klon projektet og submoduler

git clone --recurse-submodules https://github.com/AndersBalleby/PiratePlatformer.git
cd PiratePlatformer

### 2. Byg med CMake

mkdir build
cd build
cmake ..
cmake --build .

### 3. Kør spillet

./Pirate_Platformer

> Sørg for at du har raylib's afhængigheder (f.eks. X11, OpenGL, pthread på Linux)

## 📁 Projektstruktur
```text
PiratePlatformer/
├── src/          # Spilkode i C
├── resources/    # Grafikker, lyde osv.
├── levels/       # Banefiler
├── external/     # raylib (submodul)
├── build/        # Midlertidig build-mappe
└── CMakeLists.txt
```

## 🏗️ Inspiration

Projektet er inspireret af:
- Clear Code's Python platformer: https://github.com/clear-code-projects/2D-Mario-style-platformer
- raylib eksempler og dokumentation: https://github.com/raysan5/raylib


