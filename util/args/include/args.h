#ifndef ARGS_H
#define ARGS_H

#include <argp.h> // Arguments parser
#include <stdbool.h>
#include <string.h> // strcmp
#include <stdint.h> // int types

typedef enum {
	NONE,
	ALL,
	RGB,
	HSL,
	HSV,
	CMYK
} model_t;

typedef struct {
	model_t model;
	bool shade;
	bool tint;
	char *input;
} arguments_t;

const static char doc[] = "Colorin\n"
						  "\n"
						  "Usage:\n"
						  "  colorin [OPTIONS] <rgb hex>\n"
						  "\n"
						  "Options:\n"
						  "\v"
						  "Examples:\n"
						  "  colorin aabbcc // Prints the color RGB #aabbcc in differents models.\n"
						  "  colorin -m cmyk aabbcc// Prints only the cmyk model.\n"
						  "\n"
						  "Models available: cmyk, hsl and hsv.\n"
						  "\n"
						  "MIT License Copyright (c) 2021 Lunlumo";
const static char arg_doc[] = "<rgb hex>";
const struct argp_option options[] = {
	{"help",   'h', 0,        0, "Display the help page.", -1},
	{"usage",  'u', 0,        0, "Display usage.", -1},
	{"shade",  's', 0, 		  0, "Print shades."},
	{"tint",   't', 0, 		  0, "Print tint."},
	{"model",  'm', "MODEL",  0, "Select the output model."},
	{0}
};

error_t parse_opt(int key, char *arg, struct argp_state *state);

struct argp argp = {options, parse_opt, arg_doc, doc};

uint32_t str_to_uint(const char *str, int len);

#endif // ARGS_H
