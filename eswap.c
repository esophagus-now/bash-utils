#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

//These variables hang onto the old tty state so we can return to it when 
//quitting
static int changed = 0;
static struct termios old;

void term_init() {
    //Check if we are outputting to a TTY
    if (isatty(0) == 0) {
		return;
    }

    //Check if we have already init'd the term
    if (changed) {
        return;
    }
    //Get current TTY attributes and save in old
    tcgetattr(0, &old);
    //Keep track of the fact that we are changing the tty settings
    changed = 1;
    //Copy the old settings and modify to turn off "cooked" mode and echoing
    struct termios mod = old;
    mod.c_lflag &= (~ECHO & ~ICANON);
    tcsetattr(0, TCSANOW, &mod);
}

void clean_screen() {
    if (changed) {
        tcsetattr(0, TCSANOW, &old);
        changed = 0;
    }
}

void rev4(char c[4]) {
		char tmp;
		tmp = c[0]; c[0] = c[3]; c[3] = tmp;
		tmp = c[1]; c[1] = c[2]; c[2] = tmp;
}

//Returns 0 on end-of-stream or <0 on error
int read_word(char *u) {
    int num_read = 0;
    //Read in a loop until word is filled, or end-of-stream
    char *pos = u;
    int rc;
    while (num_read < 4) {
        rc = read(STDIN_FILENO, pos + num_read, 4 - num_read);
        if (rc <= 0) break;
        num_read += rc;
    }
    
    return rc;
}


int main() {
	char c[4];
	
	term_init();

	while (read_word(c) > 0) {
		rev4(c);
		write(STDOUT_FILENO, c, 4);
	}
	
	clean_screen();
	
	return 0;
}
