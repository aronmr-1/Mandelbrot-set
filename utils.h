#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL3/SDL_stdinc.h>

#define ITERATIONS 100
#define THRESHOLD 10000.0

struct complex_number {
		float a;
		float b;
};

float complex_absolute_value(struct complex_number z) {
		return SDL_sqrtf((z.a)*(z.a)+(z.b)*(z.b));
};

void display_complex(struct complex_number z) {
		printf("z = %f + i*%f \n",z.a,z.b);
};


struct complex_number mandelbrot_function(struct complex_number z, struct complex_number c) {	
		struct complex_number result;
		result.a = (z.a*z.a)-(z.b*z.b)+c.a;
		result.b = 2*z.a*z.b+c.b;
		return result;
};

float iterate_mandelbrot(struct complex_number c) {	
		int i;
		struct complex_number z;
		z.a=0.0;
		z.b=0.0;
		
		for (i=0; i<=ITERATIONS;i++) {		
				z = mandelbrot_function(z, c);
				if (complex_absolute_value(z)>=THRESHOLD) {
						break;
				}
		};
				
		return complex_absolute_value(z);
};

int complex_debug() {
		struct complex_number z;
		struct complex_number c;
		z.a = 5.0;
		z.b = 5.0;
		c.a = 1.0;
		c.b = 0.0;
		struct complex_number res = mandelbrot_function(z,c);	

		printf("z = %f + i*%f \n",res.a,res.b);
		printf("z = %f + i*%f \n",res.a,res.b);
};

