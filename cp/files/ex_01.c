#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if(argc != 3) return -1;

	int fd = open(argv[1], O_RDONLY);
	int fd_copy = creat(argv[2], 0600);
	int size = 8;
	char *buf;
	int buf_size = read(fd, &buf, size);
	
	while(buf_size > 0){
		write(fd_copy, &buf, buf_size);
		buf_size = read(fd, &buf, size);
	}

	close(fd);
	close(fd_copy);

return 0;
}