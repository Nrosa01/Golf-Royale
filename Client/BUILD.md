# How to build Golf-Royale Client

## Prerequisites

### MacOS

This guide asumes you have [Homebrew](https://brew.sh/) installed on your 
machine as your main package manager

```sh
brew install SDL2 SDL2_Image SDL2_TTF SDL2_Mixer
```

### Linux

This guide assumes your distro uses `apt` as your main package manager.

```sh
sudo apt install libsdl2-dev libsdl2-2.0-0
```

```sh
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0
```

```sh
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0
```

```sh
sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0
```

### Windows

WINDOWS IS NOT SUPPORTED FOR NOW (support will be added soon)

Just as for Linux and MacOS, you will need SDL2, SDL2_Image, SDL2_TTF, SDL2_Mixer and SDL_NET as DLLs. I'll write detailed instructions once support is added


## Building the client

### Linux and MacOS

Run `make debug` or `make release` on this directory. The resulting binary will be available on 
`bin/Golf-Royale-Debug` or `bin/Golf-Royale-Release` respectively

### Windows

WINDOWS IS NOT SUPPORTED FOR NOW (support will be added soon)

The project can be build in Windows using `make`, but the project can't run in windows at the moment. Also good luck installing make in Windows. I'll write instructions here on how to do that once it is compatible.
