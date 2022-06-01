#include "Texture.h"
#include <iostream>

using namespace std;

void Texture::freeMemory()
{
   SDL_DestroyTexture(texture);
   texture = nullptr;
   w = h = 0;
}

void Texture::load(string filename, uint nRows, uint nCols)
{
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (tempSurface == nullptr) throw string("Error loading surface from " + filename);
	freeMemory();
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (texture == nullptr) throw string("Error loading texture from " + filename);
	numRows = nRows;
	numCols = nCols;
	w = tempSurface->w;
	h = tempSurface->h;
	fw = w / numCols;
	fh = h / numRows;
	SDL_FreeSurface(tempSurface);
	this->filename = filename;
}

void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const
{
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, flip);
}

void Texture::render(const SDL_Rect& destRect, int angle, SDL_RendererFlip flip) const
{
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
}

void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const
{
	SDL_Rect srcRect;
	srcRect.x = fw * col;
	srcRect.y = fh * row;
	srcRect.w = fw;
	srcRect.h = fh;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
}

Texture* Texture::getClone()
{
	Texture* t = new Texture(renderer);
	t->load(filename, numRows, numCols);
	return t;
}