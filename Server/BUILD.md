# How to build Golf-Royale Client

## Prerequisites

### MacOS and Linux

Server uses POSIX sockets api so there are no prerequisites, but be aware that this project is migratting to SDL_Net and you may need to install it. I'll write instructions about that once the migrations is done.

### Windows

WINDOWS IS NOT SUPPORTED FOR NOW (support will be added soon)

Just as for Linux and MacOS, you will need SDL_NET as DLL. I'll write detailed instructions once support is added


## Building the client

### Linux and MacOS

Run `make debug` or `make release` on this directory. The resulting binary will be available on 
`bin/Golf-Server-Debug` or `bin/Golf-Server-Release` respectively

### Windows

WINDOWS IS NOT SUPPORTED FOR NOW (support will be added soon)

The project can be build in Windows using `make`, but the project can't run in windows at the moment. Also good luck installing make in Windows. I'll write instructions here on how to do that once it is compatible.
