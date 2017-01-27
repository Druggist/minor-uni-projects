#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if(argc < 2) return -1;

	for(int i = 1; i < argc; i++){
		int fd = open(argv[i], O_RDONLY);
		int size = 8;
		char buf;
		int buf_size = read(fd, &buf, size);
		int file_size = 0;
		while(buf_size > 0) {
			file_size += buf_size;
			buf_size = read(fd, &buf, size);
		}
		close(fd);
		printf("%s %d bytes.\n", argv[i], file_size);
	}
return 0;
}