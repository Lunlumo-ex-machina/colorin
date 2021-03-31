#ifndef ARGS_H
#define ARGS_H

#include <argp.h> // Arguments parser
#include <string.h> // strcmp
#include <stdlib.h> // isnum
#include <stdint.h> // int types

typedef enum {
	ALL,
	RGB,
	HSL,
	HSV,
	CMYK
} model_t;

typedef struct {
	model_t model;
	uint32_t input;
} arguments_t;

const static char doc[] = "Colorin\n"
						  "Usage:\n"
						  "  colorin [-m]\n"
						  "\n"
						  "Options:\n"
						  "\v"
						  "Examples:\n"
						  "  colorin aabbcc // Prints the color RGB #aabbcc in differents models (HSL, HSV and CMYK).\n"
						  "  colorin -m cmyk 79 56 147// Prints only the cmyk model.\n"
						  "\n"
						  "Models avaliable: cmyk, hsl and hsv.\n"
						  "\n"
						  "MIT License Copyright (c) 2021 Lunlumo";
const static char arg_doc[] = "[OPTIONS...]";
const struct argp_option options[] = {
	{"help",   'h', 0,        0, "Display the help page.", -1},
	{"usage",  'u', 0,        0, "Display usage.", -1},
	{"model",  'm', "MODEL",  0, "Select the output model."},
	{0}
};

error_t parse_opt(int key, char *arg, struct argp_state *state);

struct argp argp = {options, parse_opt, arg_doc, doc};

uint32_t str_to_uint(const char *str, int len);

#endif // ARGS_H
