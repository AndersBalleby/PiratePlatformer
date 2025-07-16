# 🏴☠️ Pirate Platformer

> ⚠️ **Projektet er stadig under udvikling!** Dette er et læringsprojekt, og der tilføjes løbende nye funktioner og forbedringer.

Et simpelt 2D platformer-spil skrevet i **C** med [**raylib**](https://www.raylib.com/).  
Projektet er lavet som en læringsrejse i C-programmering og spiludvikling – med inspiration fra [Clear Code's 2D Mario-style platformer](https://github.com/clear-code-projects/2D-Mario-style-platformer) skrevet i Python.

## 🎮 Om spillet

I **Pirate Platformer** spiller du som en pirat, der hopper gennem klassiske platformer-baner, undgår farer og måske finder skjulte skatte.  
Spillet er under udvikling, og formålet er at opnå en bedre forståelse i C

## 🧰 Teknologier

- **C** – programmering og læring  
- **raylib** – simpelt C-baseret game framework  
- **CMake** – til build og projektstruktur  

## 📦 Installation
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

## ℹ️  Brug af AI 

Alle former for kunstig intelligens er kun brugt som skriveassistent til denne README.  
Alt kode og design er lavet manuelt med mindre andet er angivet.


