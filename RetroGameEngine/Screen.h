#ifndef X2D_SCREEN_H
#define X2D_SCREEN_H

#include "SDL2/SDL.h"

#define X2D_Color SDL_Color

typedef struct
{
	SDL_Palette* palette;   // SDL_PALETTE (COLOR PALETTE)
	X2D_Color* colors;      // X2D_COLOR (MACRO FOR SDL_COLOR)
	Uint8 numColors;          // NUMBER OF COLORS IN PALETTE OF COLORS
	Uint8 background_index;
} X2D_ColorPalette;

X2D_ColorPalette* X2D_CreateColorPalette(X2D_Color* c, int num);

void X2D_DestroyColorPalette(X2D_ColorPalette* p);

typedef struct
{
	Uint16 raster_w;                // WIDTH  OF RASTER (GAME RESOLUTION)
	Uint16 raster_h;                // HEIGHT OF RASTER (GAME RESOLUTION)

	Uint16 window_w;                // WIDTH  OF WINDOW (WINDOW RESOLUTION)
	Uint16 window_h;                // HEIGHT OF WINDOW (WINDOW RESOLUTION)

	SDL_Window *window;             // SDL_WINDOW USED TO DISPLAY GAME
	SDL_Renderer *renderer;         // USED TO RENDER NEXT FRAME
	SDL_Surface *surface;           // USED AS A RASTER TO DRAW TO
	SDL_Texture *texture;           // USED TO DRAW NEXT FRAME OF GAME

	Uint8 *pixels;                  // POINTER TO RASTER PIXEL DATA

} X2D_Screen;

X2D_Screen* X2D_CreateScreen(const char* t, Uint16 w, Uint16 h, X2D_ColorPalette *p);
void X2D_DestroyScreen(X2D_Screen *s);
void X2D_SetScreenSize(X2D_Screen* s, int w, int h);
void X2D_RefreshScreen(X2D_Screen* s);

#endif /* X2D_SCREEN_H */
