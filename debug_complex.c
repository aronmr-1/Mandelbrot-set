#include <stdio.h>
#include <stdbool.h>
#include <SDL3/SDL_stdinc.h>
#include "utils.h"

int main() {
		struct complex_number z;
		struct complex_number c;
		z.a = 5.0;
		z.b = 5.0;
		c.a = 1.0;
		c.b = 0.0;
		struct complex_number res = mandelbrot_function(z,c);	
		float size = iterate_mandelbrot(c);

		printf("z = %f + i*%f \n",res.a,res.b);
		printf("z = %f + i*%f \n",res.a,res.b);
		printf("iteration: %f \n",size);
};

