#include "Screen.h"

X2D_ColorPalette* X2D_CreateColorPalette(X2D_Color* c, Uint8 num, Uint8 index)
{
	// ALLOCATE X2D_COLORPALETTE IN HEAP MEMORY
	X2D_ColorPalette* p = malloc(sizeof(X2D_ColorPalette));


	p->palette = SDL_AllocPalette(num);
	p->colors = c;
	p->numColors = num;
	p->background_index = index;

	if(p->numColors > 256 || p->numColors <= 0)
	{
		SDL_Log("PLEASE ENTER A VALID # OF COLORS (1-256)");
		return NULL;
	}

	SDL_SetPaletteColors(p->palette, p->colors, 0, num);

	return p;
}

void X2D_DestroyColorPalette(X2D_ColorPalette* p)
{
	SDL_FreePalette(p->palette);
	free(p);
}

X2D_Screen* X2D_CreateScreen(const char* t, Uint16 w, Uint16 h, X2D_ColorPalette *p)
{
	// CHECK IF X2D_COLORPALETTE WAS INITIALIZED PROPERLY
	if(p == NULL)
	{
		printf("X2D_COLORPALETTE IS NOT USABLE");
	}
	else // CONTINUE IF X2D_COLORPALETTE INITIALIZATION WAS SUCCESSFUL
	{
		// ALLOC MEMORY FOR X2D_SCREEN ON HEAP
		X2D_Screen* scrn = malloc(sizeof(X2D_Screen));

		// INIT WIDTH AND HEIGHT OF X2D_SCREEN
		scrn->raster_w = w;
		scrn->raster_h = h;

		// POSITION OF SDL_WINDOW
		Uint32 w_pos = SDL_WINDOWPOS_CENTERED;

		// CREATE NEW SDL_WINDOW AND SAVE REFERENCE IN X2D_SCREEN
		scrn->window = SDL_CreateWindow(t, w_pos, w_pos, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

		// CHECK IF SDL_WINDOW INITIALIZATION WAS SUCCESSFUL
		if(scrn->window == NULL)
		{
			SDL_Log("UNABLE TO INITIALIZE WINDOW: %s", SDL_GetError());
		}
		else // CONTINUE IF SDL_WINDOW INITIALIZATION SUCCESSFUL
		{
			// CREATE NEW SDL_RENDERER AND SAVE REFERENCE IN X2D_SCREEN
			scrn->renderer = SDL_CreateRenderer(scrn->window, -1, SDL_RENDERER_ACCELERATED);

			// CHECK IF SDL_RENDERER INITIALIZATION SUCCESSFUL
			if(scrn->renderer == NULL)
			{
				SDL_Log("UNABLE TO INITIALIZE RENDERER: %s", SDL_GetError());
			}
			else // CONTINUE IF SDL_RENDERER INITIALIZATION SUCCESSFUL
			{
				// RENDERS GAME TO FIT DIMENSIONS OF SDL_WINDOW WHILE KEEPING ORIGINAL RATIO OF GAME
				SDL_RenderSetLogicalSize(scrn->renderer, scrn->raster_w, scrn->raster_h);

				// CREATE ARRAY OF RGBA MASKS FOR SDL_SURFACE
				Uint32 m[4] /* MASKS */ = { 0 /* R */, 0 /* G */, 0 /* B */, 0 /* A */ };

				// SET MASK ARRAY ELEMENTS DEPENDING ON BIG/LITTLE ENDIAN
				if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				{
					m[0] = 0xFF000000;	// RED
					m[1] = 0x00FF0000;	// GREEN
					m[2] = 0x0000FF00;	// BLUE
					m[3] = 0x000000FF;	// ALPHA
				}
				else
				{
					m[0] = 0x000000FF;	// RED
					m[1] = 0x0000FF00;	// GREEN
					m[2] = 0x00FF0000;	// BLUE
					m[3] = 0xFF000000;	// ALPHA
				}

				// CREATE NEW SDL_SURFACE AND SAVE REFERENCE IN X2D_SCREEN
				scrn->surface = SDL_CreateRGBSurface(0, scrn->raster_w, scrn->raster_h, 8, 0, 0, 0, 0);

				// CHECK IF SDL_SURFACE INITIALIZATION SUCCESSFUL
				if(scrn->surface == NULL)
				{
					SDL_Log("UNABLE TO INITIALIZE SURFACE: %s", SDL_GetError());
				}
				else // CONTINUE IF SDL_SURFACE INITIALIZATION SUCCESSFUL
				{
					// SET SDL_SURFACE COLOR PALETTE TO X2D_COLORPALETTE
					scrn->surface->format->palette = p->palette;

					// SAVE REFERENCE TO PIXEL BUFFER FROM SDL_SURFACE
					// THIS IS WHAT WILL BE DIRECTLY DRAWN ON
					scrn->pixels = scrn->surface->pixels;

					// AND FINALLY RETURN THE COMPLETED SCREEN
					return scrn;
				}
			}
		}
	}
	// IF SOMETHING WENT WRONG THIS WILL EXECUTE
	return NULL;
}

void X2D_DestroyScreen(X2D_Screen *s)
{
	SDL_DestroyWindow(s->window);
	SDL_DestroyRenderer(s->renderer);
	SDL_FreeSurface(s->surface);

	free(s);
}

void X2D_SetScreenSize(X2D_Screen* s, int w, int h)
{
	SDL_SetWindowSize(s->window, w, h);
}

void X2D_RefreshScreen(X2D_Screen* s)
{
	s->pixels[0] = 2;

	s->texture = SDL_CreateTextureFromSurface(s->renderer, s->surface);
	SDL_RenderCopy(s->renderer, s->texture, NULL, NULL);

	SDL_RenderPresent(s->renderer);

	SDL_DestroyTexture(s->texture);
	s->texture = NULL;
}
