#include "models.h"

float max(float n1, float n2, float n3) {
	if (n1 > n2) {
		return (n1 > n3)? n1: n3;
	} else {
		return (n2 > n3)? n2: n3;
	}
}

float min(float n1, float n2, float n3) {
	if (n1 < n2) {
		return (n1 < n3)? n1: n3;
	} else {
		return (n2 < n3)? n2: n3;
	}
}

rgb_t init_rgb(uint32_t hex) {
	rgb_t rgb;
	rgb.b = hex & 0xFF;
	hex >>= 8;
	rgb.g = hex & 0xFF;
	hex >>= 8;
	rgb.r = hex & 0xFF; return rgb;
}

float get_hue(float r, float g, float b, float m, float M) {
	float h = 0;
	float c = M - m;
	if (c == 0) {
		h = 0;
	} else if (M == r) {
		h = ((g - b) / c);
	} else if (M == g) {
		h = ((b - r) / c) + 2;
	} else {
		h = ((r - g) / c) + 4;
	}
	h *= 60;
	return (h < 0)? h + 360: h;
}

hsl_t rgb_to_hsl(const rgb_t *rgb) {
	hsl_t hsl;
	float r = rgb->r / 255.0;
	float g = rgb->g / 255.0;
	float b = rgb->b / 255.0;
	float M = max(r, g, b);
	float m = min(r, g, b);
	float c = M - m;

	hsl.h = get_hue(r, g, b, m, M);
	hsl.l = (M + m) / 2;

	if (hsl.l == 1 || hsl.l == 0 || c == 0) {
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

	hsv.h = get_hue(r, g, b, m, M);
	hsv.v = M;
	hsv.s = (hsv.v == 0 || c == 0)? 0: c / hsv.v;

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

rgb_t hsl_to_rgb(const hsl_t *hsl) {
	float r, g, b;
	float c = (1 - fabsf(2*hsl->l-1)) * hsl->s;
	float h = hsl->h / 60;
	float x = c * (1 - fabsf(fmodf(h, 2) - 1));
	float m = hsl->l - c / 2;

	if (h < 1) {
		r = c;
		g = x;
		b = 0;
	} else if (h < 2) {
		r = x;
		g = c;
		b = 0;
	} else if (h < 3) {
		r = 0;
		g = c;
		b = x;
	} else if (h < 4) {
		r = 0;
		g = x;
		b = c;
	} else if (h < 5) {
		r = x;
		g = 0;
		b = c;
	} else if (h < 6) {
		r = c;
		g = 0;
		b = x;
	} else {
		r = 0;
		g = 0;
		b = 0;
	}

	return (rgb_t){(r + m)*255, (g + m)*255, (b + m)*255};
}
