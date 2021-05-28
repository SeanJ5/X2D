#include "Screen.h"

X2D_ColorPalette *palette = NULL;
X2D_Screen *screen = NULL;

void InitRetroScreen()
{
  SDL_Color c0; c0.r = 255; c0.g = 0; c0.b = 0; c0.a = 255;
	SDL_Color c1; c1.r = 0; c1.g = 255; c1.b = 0; c1.a = 255;
	SDL_Color c2; c2.r = 0; c2.g = 0; c2.b = 255; c2.a = 255;
	SDL_Color c3; c3.r = 255; c3.g = 255; c3.b = 255; c3.a = 255;

	X2D_Color colors[4];
	colors[0] = c0;
	colors[1] = c1;
	colors[2] = c2;
	colors[3] = c3;

	palette = X2D_CreateColorPalette(colors, 4);

	screen = X2D_CreateScreen("Tech Test", 256, 224, palette);
	X2D_SetScreenSize(screen, 640, 480);
}

int main(int argc, char* argv[])
{
	InitRetroScreen();

	SDL_Event e;
	Uint8 running = 1;

	while(running)
	{
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
				running = 0;
		}
		X2D_RefreshScreen(screen);
	}

	X2D_DestroyScreen(screen);
}
