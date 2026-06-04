// aronmr-1 Github.com
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "utils.h" 

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1280

#define REAL_AXIS 2.0
#define COMPLEX_AXIS 2.0

SDL_Texture *texture;

void calculate_and_draw(SDL_Surface *surface) {
		int x,y;
		struct complex_number z,c;
		float size;
		for (x=0;x<=WINDOW_WIDTH;x++) {
				for (y=0;y<=WINDOW_HEIGHT;y++) {
						c.a = (float) (REAL_AXIS*(x-WINDOW_WIDTH/2.0)/(WINDOW_WIDTH/2.0));
						c.b = (float) (COMPLEX_AXIS*(WINDOW_HEIGHT/2.0-y)/(WINDOW_HEIGHT/2.0));
						size=iterate_mandelbrot(c);
						//display_complex(c);

						SDL_WriteSurfacePixel(surface, x, y, 0, 0, SDL_min(255*(int)(size/THRESHOLD),255), 255);
				};
		};
};

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_Surface *surface = SDL_CreateSurface(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_PIXELFORMAT_RGBA8888);
		calculate_and_draw(surface);

    SDL_SetAppMetadata("Mandelbrot set", "1.0", "com.draw-mandelbrot");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/points", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL) {
			SDL_Log("CreateTextureFromSurface failed: %s", SDL_GetError());
		}
     return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
		if (!(SDL_RenderTexture(renderer, texture, NULL, NULL))) {
        SDL_Log("Failed to render texture: %s", SDL_GetError());
		};

    /* You can also draw single points with SDL_RenderPoint(), but it's
       cheaper (sometimes significantly so) to do them all at once. */

    SDL_RenderPresent(renderer);  /* put it all on the screen! */

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}
