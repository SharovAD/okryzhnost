
#include <iostream>
#include <memory>
#include <cmath>
#include <algorithm>
#include <cmath>

#include <SDL2/SDL.h>

constexpr double Pi = acos(-1.);

#ifdef _WIN32
# include <SDL2/SDL_main.h>
#endif

constexpr int WIDTH = 800, HEIGHT = 600;

int main(int, char**)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	auto win = std::shared_ptr<SDL_Window>(
			SDL_CreateWindow(
						"Okryzhnoct'",
						SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
						WIDTH, HEIGHT,
						SDL_WINDOW_SHOWN),
			SDL_DestroyWindow);
	if (win == nullptr) {
		std::cerr << "При создании окна произошла ошибка: " <<
				SDL_GetError() << std::endl;
		return 1;
	}

	auto ren = std::shared_ptr<SDL_Renderer>(
			SDL_CreateRenderer(win.get(), -1,
					SDL_RENDERER_ACCELERATED |
					SDL_RENDERER_PRESENTVSYNC),
			SDL_DestroyRenderer);
	if (ren == nullptr) {
		std::cerr << "При создании renderer-а произошла ошибка: " <<
				SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Event event;

	for (;;) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) return 0;
		}

		SDL_SetRenderDrawColor(ren.get(), 0, 48, 64, 255);
		SDL_RenderClear(ren.get());

		SDL_SetRenderDrawColor(ren.get(), 255, 255, 255, 255);
//Окружность
	int R=200;
	int X1=300;
	int Y1=300;
	int x = 0;
   int y = R;
   int delta = 1 - 2 * R;
   int error = 0;
   while (y >= 0){
	   SDL_RenderDrawPoint(ren.get(), X1 + x, Y1 + y);
	   SDL_RenderDrawPoint(ren.get(), X1 + x, Y1 - y);
	   SDL_RenderDrawPoint(ren.get(), X1 - x, Y1 + y);
	   SDL_RenderDrawPoint(ren.get(), X1 - x, Y1 - y);
       error = 2 * (delta + y) - 1;
       if ((delta < 0) && (error <= 0)){
    	   delta += 2 * ++x + 1;
           continue;}
       if ((delta > 0) && (error > 0)){
           delta -= 2 * --y + 1;
           continue;}
       delta += 2 * (++x - --y);
   }

		SDL_RenderPresent(ren.get());

}


	return 0;
}
