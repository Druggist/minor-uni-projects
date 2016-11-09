#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if(argc != 2) return -1;

	int fd = open(argv[1], O_RDONLY);
	int size = 1;
	char buf;
	int buf_size = read(fd, &buf, size);
	int length = 0;
	int max = 0;
	while(buf_size >= 0) {
		length++;
		if(buf_size == 0) {
			max = (max > length)?(max):(length);
			buf_size = -1;
		} else if(buf == '\n') {
			max = (max > length)?(max):(length);
			length = 1;
			buf_size = read(fd, &buf, size);
		} else buf_size = read(fd, &buf, size);
	}
	close(fd);
	printf("Longest line has: %d chars.\n", max);

return 0;
}