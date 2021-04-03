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

void print_color(const rgb_t *rgb, uint8_t num) {
	printf("\x1B[48;2;%d;%d;%dm%*s\x1B[m", rgb->r, rgb->g, rgb->b, num, " ");
}

void print_line(uint8_t num) {
	for (int i = 0; i < num; i++) {
		printf("-");
	}
}

void print_all(const rgb_t *rgb) {
	print_rgb(rgb);
	print_hsl(rgb);
	print_hsv(rgb);
	print_cmyk(rgb);
}

bool ishex(const char *ch) {
	for (int i = 0; *ch != '\0'; i++, ch++) {
		if ((*ch < '0' || *ch > '9') &&
			(*ch < 'a' || *ch > 'f') &&
			(*ch < 'A' || *ch > 'F')) {
			return false;
		}
	}
	return true;
}

void print_hex(const rgb_t *rgb) {
	uint32_t hex = rgb->r << 16 | rgb->g << 8 | rgb->b;
	printf("#%06X", hex);
}

void print_shade(const rgb_t *rgb, uint8_t num) {
	rgb_t shades[num];
	hsl_t hsl = rgb_to_hsl(rgb);
	const float x = hsl.l / num;
	printf("\x1B[1mShades\x1B[m");
	print_line(num*8-7);
	printf("\n");
	for (int i = 0; i < num; i++) {
		hsl.l -= x;
		shades[i] = hsl_to_rgb(&hsl);
		print_color(&shades[i], 7);
		if ((shades[i].r + shades[i].g + shades[i].b) == 0) {
			break;
		}
		printf(" ");
	}
	printf("\n");
	for (int i = 0; i < num; i++) {
		print_hex(&shades[i]);
		if ((shades[i].r + shades[i].g + shades[i].b) == 0) {
			break;
		}
		printf(" ");
	}
	printf("\n");
}

void print_tint(const rgb_t *rgb, uint8_t num) {
	rgb_t shades[num];
	hsl_t hsl = rgb_to_hsl(rgb);
	const float x = (1 - hsl.l) / num;
	printf("\x1B[1mTints\x1B[m");
	print_line(num*8-6);
	printf("\n");
	for (int i = 0; i < num; i++) {
		hsl.l += x;
		shades[i] = hsl_to_rgb(&hsl);
		print_color(&shades[i], 7);
		if ((shades[i].r + shades[i].g + shades[i].b) == 765) {
			break;
		}
		printf(" ");
	}
	printf("\n");
	for (int i = 0; i < num; i++) {
		print_hex(&shades[i]);
		if ((shades[i].r + shades[i].g + shades[i].b) == 765) {
			break;
		}
		printf(" ");
	}
	printf("\n");
}

int main(int argc, char **argv) {

	arguments_t arguments;
	arguments.model = NONE;
	arguments.shade = false;
	arguments.tint = false;
	arguments.input = 0;

	argp_parse(&argp, argc, argv, ARGP_NO_HELP, 0, &arguments);

	if (strlen(arguments.input) != 6 || !ishex(arguments.input)) {
		return 1;
	}

	rgb_t rgb = init_rgb(strtol(arguments.input, NULL, 16));

	printf("\x1B[1mColor\x1B[m");
	print_line(74);
	printf("\n");
	print_color(&rgb, 7);
	printf("\n");
	print_hex(&rgb);
	printf("\n");
	switch (arguments.model) {
		case ALL:
			printf("\x1B[1mModels\x1B[m");
			print_line(73);
			printf("\n");
			print_all(&rgb);
			break;
		case RGB:
			printf("\x1B[1mModel\x1B[m");
			print_line(74);
			printf("\n");
			print_rgb(&rgb);
			break;
		case HSL:
			printf("\x1B[1mModel\x1B[m");
			print_line(74);
			printf("\n");
			print_hsl(&rgb);
			break;
		case HSV:
			printf("\x1B[1mModel\x1B[m");
			print_line(74);
			printf("\n");
			print_hsv(&rgb);
			break;
		case CMYK:
			printf("\x1B[1mModel\x1B[m");
			print_line(74);
			printf("\n");
			print_cmyk(&rgb);
			break;
		default:
			break;
	}
	if (arguments.shade) {
		print_shade(&rgb, 10);
	}
	if (arguments.tint) {
		print_tint(&rgb, 10);
	}

	return 0;
}
