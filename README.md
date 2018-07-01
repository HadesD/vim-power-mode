# Vim Power Mode

Power mode for Vimmers

## How it work

![](https://i.imgur.com/Z6nP3wO.gif)

## Usage

```vim
:PowerModeOn
:PowerModeOff
```

## TODO

- Will be working on Linux/Unix

## Installation

### Clone project

Pathogen

```bash
git clone https://HadesD@github.com/HadesD/vim-power-mode.git ~/.vim/bundle/vim-power-mode
```

### Build

#### cl.exe (Visual Studio)

- Make cl.bat in C:/Windows (Change 12.0 to your VS Version)

```bat
@echo off
%comspec% /c ""c:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86 && cl.exe %*"
```

- Run

```bash
cl -EHsc -Feparticle particle.cpp
```

#### Msys2

```bash
make
```

#### G++

```
Updating...
```

## Better with Async

- https://github.com/skywind3000/asyncrun.vim

## Idea

- https://github.com/JoelBesada/activate-power-mode
- Yasuhiro Matsumoto (a.k.a mattn) https://github.com/mattn/vim-particle

## License

- MIT License
- Copyright (c) Dark.Hades (a.k.a HaiLe)

