#include "../headers/graphs.h"

int main(int argc, char *argv[]) {
clock_t begin, end;
    int n = atoi(argv[1]);
	int mode =  atoi(argv[2]);
	
	
	for(int i=1; i<=1; i++){
		begin = clock();
		Graph obj(n*i);
		obj.sort(mode);
		end = clock();
		
		cout << n*i << " " << (double(end - begin) / CLOCKS_PER_SEC) << endl;
	}
	return 0;
}