#include <stdio.h>
#include <unistd.h>

int main() {
	int rc;
	char line[80];
	while ((rc = read(STDIN_FILENO, line, sizeof(line))) > 0) {
		write(STDOUT_FILENO, line, rc);
	}
}
