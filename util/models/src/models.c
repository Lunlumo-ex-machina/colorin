#include "models.h"

rgb_t init_rgb(uint32_t hex) {
	rgb_t rgb;
	rgb.b = hex & 0xFF;
	hex >>= 8;
	rgb.g = hex & 0xFF;
	hex >>= 8;
	rgb.r = hex & 0xFF;
	return rgb;
}

float max(float n1, float n2, float n3) {
	if (n1 > n2) {
		return n1 > n3? n1: n3;
	} else {
		return n2 > n3? n2: n3;
	}
}

float min(float n1, float n2, float n3) {
	if (n1 < n2) {
		return n1 < n3? n1: n3;
	} else {
		return n2 < n3? n2: n3;
	}
}

hsl_t rgb_to_hsl(const rgb_t *rgb) {
	hsl_t hsl;
	float r = rgb->r / 255.0;
	float g = rgb->g / 255.0;
	float b = rgb->b / 255.0;
	float M = max(r, g, b);
	float m = min(r, g, b);
	float c = M - m;

	if (c == 0) {
		hsl.h = 0;
	} else if (M == r) {
		hsl.h = fmodf(((g - b) / c), 6);
	} else if (M == g) {
		hsl.h = ((b - r) / c) + 2;
	} else {
		hsl.h = ((r - g) / c) + 4;
	}
	hsl.h *= 60;

	if (hsl.h < 0) {
		hsl.h += 360;
	}

	hsl.l = (M + m) / 2;

	if ((hsl.l == 1) || (hsl.l == 0)) {
		hsl.s = 0;
	} else if (c == 0) {
		hsl.s = 0;
	} else {
		hsl.s = c / (1 - fabsf(2*hsl.l-1));
	}

	return hsl;
}

hsv_t rgb_to_hsv(const rgb_t *rgb) {
	hsv_t hsv;
	float r = rgb->r / 255.0;
	float g = rgb->g / 255.0;
	float b = rgb->b / 255.0;
	float M = max(r, g, b);
	float m = min(r, g, b);
	float c = M - m;

	if (c == 0) {
		hsv.h = 0;
	} else if (M == r) {
		hsv.h = fmodf(((g - b) / c), 6);
	} else if (M == g) {
		hsv.h = ((b - r) / c) + 2;
	} else {
		hsv.h = ((r - g) / c) + 4;
	}
	hsv.h *= 60;

	if (hsv.h < 0) {
		hsv.h += 360;
	}

	hsv.v = M;

	if ((hsv.v == 1) || (hsv.v == 0)) {
		hsv.s = 0;
	} else if (c == 0) {
		hsv.s = 0;
	} else {
		hsv.s = c / (1 - fabsf(2*hsv.v-1));
	}

	return hsv;
}

cmyk_t rgb_to_cmyk(const rgb_t *rgb) {
	cmyk_t cmyk;
	cmyk.k = 1 - (max(rgb->r, rgb->g, rgb->b) / 255.f);
	float k = 1 - cmyk.k;
	cmyk.c = (1 - rgb->r / 255.f - cmyk.k) / k;
	cmyk.m = (1 - rgb->g / 255.f - cmyk.k) / k;
	cmyk.y = (1 - rgb->b / 255.f - cmyk.k) / k;
	return cmyk;
}
