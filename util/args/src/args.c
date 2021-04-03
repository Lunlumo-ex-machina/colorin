#include "args.h"
#include <argp.h>

error_t parse_opt(int key, char *arg, struct argp_state *state) {
	arguments_t *arguments = state->input;
	switch (key) {
		case 'h':
			argp_state_help(state, stdout, ARGP_HELP_LONG | ARGP_HELP_DOC | ARGP_HELP_BUG_ADDR | ARGP_HELP_EXIT_OK);
			break;
		case 'u':
			argp_usage(state);
			break;
		case 'm':
			if (!strcmp("all", arg)) {
				arguments->model = ALL;
			} else if (!strcmp("rgb", arg)) {
				arguments->model = RGB;
			} else if (!strcmp("hsl", arg)) {
				arguments->model = HSL;
			} else if (!strcmp("hsv", arg)) {
				arguments->model = HSV;
			} else if (!strcmp("cmyk", arg)) {
				arguments->model = CMYK;
			} else if (!strcmp("none", arg)){
				arguments->model = NONE;
			} else {
				argp_usage(state);
			}
			break;
		case 's':
			arguments->shade = true;
			break;
		case 't':
			arguments->tint = true;
			break;
		case ARGP_KEY_ARG:
			if (state->arg_num > 1) {
				argp_usage(state);
			}
			arguments->input = arg;
			break;
		case ARGP_KEY_ERROR:
			break;
		case ARGP_KEY_NO_ARGS:
			argp_usage(state);
		case ARGP_KEY_END:
			if (state->arg_num < 0) {
				argp_usage(state);
			}
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}
