#ifndef TextureH
#define TextureH

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

using namespace std;

typedef unsigned int uint;

class Texture
{
private:
    SDL_Texture* texture = nullptr;
    SDL_Renderer* renderer = nullptr;
    uint w = 0;
    uint h = 0;
    uint fw = 0; // Frame width
    uint fh = 0; // Frame height
    uint numCols = 1;
    uint numRows = 1;

public:
   Texture(SDL_Renderer* r) : renderer(r){};
   Texture(SDL_Renderer* r, string filename, uint numRows = 1, uint numCols = 1) : renderer(r) { load(filename,numRows,numCols); };
   ~Texture(){ freeMemory(); };
   void freeMemory(); // destruir/liberar la textura

   int getW() const { return w; };
   int getH() const { return h; };
   uint getNumCols() const { return numCols; };
   uint getNumRows() const { return numRows; };
   SDL_Texture* getTexture() const { return texture; };

   void load(string filename, uint numRows = 1, uint numCols = 1); // construir/cargar la textura de un fichero
   void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const; // dibujar la textura en su totalidad en la posición proporcionada
   void renderFrame(const SDL_Rect& destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const; // dibujar uno de los frames de la textura en la posición proporcionada
};

#endif