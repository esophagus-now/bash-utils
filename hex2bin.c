#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

typedef enum _state_t {
	NO_DIGITS,
	ONE_DIGIT
} state_t;

char nybble_from_char(char c) {
	if (isdigit(c)) return c - '0';
	else return (toupper(c) - 'A') + 10;
}

int get_char(int mode, char *c) {
	if (mode > 1) return read(STDIN_FILENO, c, 1);
	else return fread(c, 1, 1, stdin);
}

void put_char(int mode, char *c) {
	if (mode > 1) write(STDOUT_FILENO, c, 1);
	else fwrite(c, 1, 1, stdout);
}

int main(int argc, char **argv) {
	char c;
	state_t state = NO_DIGITS;
	char curval = 0;
	while(get_char(argc, &c) > 0) {
		if (isxdigit(c)) {
			curval <<= 4;
			curval |= nybble_from_char(c);
			if (state == NO_DIGITS) state = ONE_DIGIT;
			else {
				put_char(argc, &curval);
				curval = 0;
				state = NO_DIGITS;
			}
		}
		else if (isspace(c)) continue;
		else {
			fprintf(stderr, "Invalid char in stream: %c%c%c (%d)\n",
					isprint(c) ? '\'' : '<',
					isprint(c) ?    c : '?',
					isprint(c) ? '\'' : '>',
					c
			);
			return -1;
		}
	}

	return 0;
}
