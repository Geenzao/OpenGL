# OpenGL - MiniGL

## Prérequis (une seule fois)

Dans un terminal **MSYS2 UCRT64** :

```bash
pacman -S mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-glfw
```

## Compiler et lancer (PowerShell, depuis la racine `OpenGL`)

```powershell
$env:PATH = "C:\msys64\ucrt64\bin;$env:PATH"

# Configuration (à refaire seulement si build/ est supprimé)
cmake -S MiniGL -B build -G "MinGW Makefiles" "-DCMAKE_CXX_STANDARD_LIBRARIES=C:/msys64/ucrt64/lib/libglfw3.dll.a"

# Compilation
cmake --build build

# Exécution
.\MiniGL\bin\MiniGL.exe
```

Ensuite, à chaque modification du code, il suffit de refaire :

```powershell
$env:PATH = "C:\msys64\ucrt64\bin;$env:PATH"
cmake --build build
.\MiniGL\bin\MiniGL.exe
```

Le `$env:PATH` est à remettre à chaque nouveau terminal. Sans lui, `cmake` est introuvable
et `MiniGL.exe` ne trouve pas `glfw3.dll`.
