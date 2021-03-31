#include "colorin.h"

void print_spaces(int n) {
	printf("%*s", n, " ");
}

void print_rgb(const rgb_t *rgb) {
	printf("r: %u, g: %u, b: %u\n", rgb->r, rgb->g, rgb->b);
}

void print_hsl(const rgb_t *rgb) {
	hsl_t hsl = rgb_to_hsl(rgb);
	printf("h: %.f, s: %.2f%%, l: %.2f%%\n", hsl.h, hsl.s*100, hsl.l*100);
}

void print_hsv(const rgb_t *rgb) {
	hsv_t hsv = rgb_to_hsv(rgb);
	printf("h: %.f, s: %.2f%%, v: %.2f%%\n", hsv.h, hsv.s*100, hsv.v*100);
}

void print_cmyk(const rgb_t *rgb) {
	cmyk_t cmyk = rgb_to_cmyk(rgb);
	printf("c: %.2f%%, m: %.2f%%, y: %.2f%%, k:%.2f%%\n", cmyk.c*100, cmyk.m*100, cmyk.y*100, cmyk.k*100);
}

void print_color(const rgb_t *rgb) {
	printf("\x1B[48;2;%d;%d;%dm%*s\x1B[m\n", rgb->r, rgb->g, rgb->b, 6, " ");
}

void print_all(const rgb_t *rgb) {
	print_rgb(rgb);
	print_hsl(rgb);
	print_hsv(rgb);
	print_cmyk(rgb);
}


int main(int argc, char **argv) {

	arguments_t arguments;
	arguments.model = ALL;
	arguments.input = 0;

	argp_parse(&argp, argc, argv, ARGP_NO_HELP, 0, &arguments);

	rgb_t rgb = init_rgb(arguments.input);

	switch (arguments.model) {
		case RGB:
			print_rgb(&rgb);
			break;
		case HSL:
			print_hsl(&rgb);
			break;
		case HSV:
			print_hsv(&rgb);
			break;
		case CMYK:
			print_cmyk(&rgb);
			break;
		default:
			print_all(&rgb);
			break;
	}
	print_color(&rgb);

	return 0;
}
