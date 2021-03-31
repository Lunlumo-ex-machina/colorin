#ifndef MODELS_H
#define MODELS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
	uint8_t r; // Red
	uint8_t g; // Green
	uint8_t b; // Blue
} rgb_t;

typedef struct {
	float c; // Cyan
	float m; // Magenta
	float y; // Yellow
	float k; // Key
} cmyk_t;

typedef struct {
	float h; // Hue
	float s; // Saturation
	float l; // Light
} hsl_t;

typedef struct {
	float h; // Hue
	float s; // Saturation
	float v; // Value
} hsv_t;

rgb_t init_rgb(uint32_t hex);
hsl_t rgb_to_hsl(const rgb_t *rgb);
hsv_t rgb_to_hsv(const rgb_t *rgb);
cmyk_t rgb_to_cmyk(const rgb_t *rgb);

#endif
