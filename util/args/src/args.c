#include "args.h"

int allnum(const char *str) {
	for (int i = 0; *str != '\0'; i++, str++) {
		if (!isdigit(*str)) {
			return 0;
		}
	}
	return 1;
}

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
			if (!strcmp("rgb", arg)) {
				arguments->model = RGB;
			} else if (!strcmp("hsl", arg)) {
				arguments->model = HSL;
			} else if (!strcmp("hsv", arg)) {
				arguments->model = HSV;
			} else if (!strcmp("cmyk", arg)) {
				arguments->model = CMYK;
			} else {
				argp_usage(state);
			}
			break;
		case ARGP_KEY_ARG:
			if (state->arg_num > 1) {
				argp_usage(state);
			}
			int len = strlen(arg);
			if (len != 3 && len != 6) {
				return EINVAL;
			}
			arguments->input = strtol(arg, NULL, 16);
			break;
		case ARGP_KEY_END:
			if (state->arg_num < 0) {
				argp_usage(state);
			}
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}
