#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if(argc != 3) return -1;

	int fd = open(argv[1], O_RDONLY);
	int fd_temp = creat(argv[2], 0600);
	int size = 1;
	char buf;
	int buf_size = read(fd, &buf, size);
	int length = 0;
	while(buf_size >= 0) {
		length++;
		if(buf_size == 0) {
			write(fd_temp, &buf, 1);
			for(int i = length; i > 1; i--) {
				lseek(fd, -2, SEEK_CUR);
				read(fd, &buf, 1);
				write(fd_temp, &buf, 1);
			}
			buf_size = -1;
		} else if(buf == '\n') {
			for(int i = length; i > 1; i--) {
				lseek(fd, -2, SEEK_CUR);
				read(fd, &buf, 1);
				write(fd_temp, &buf, 1);
			}
			lseek(fd, length, SEEK_CUR);
			buf = '\n';
			write(fd_temp, &buf, 1);
			length = 1;
			buf_size = read(fd, &buf, size);
		} else buf_size = read(fd, &buf, size);
	}

	close(fd);
	close(fd_temp);

return 0;
}