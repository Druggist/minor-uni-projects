#include "../headers/graphs.h"

int main(int argc, char *argv[]) {
clock_t begin, end;
    int n = atoi(argv[1]);
	int mode =  atoi(argv[2]);
	
	
	for(int i=1; i<=1; i++){
		begin = clock();
		Graph obj(n*i);
		
		switch(mode){
			case 1:
				obj.AM_DFS(0);
			break;
			case 2:
				obj.ASSCL_DFS(0);
			break;
			case 3:
				obj.EL_DFS(0);
			break;
			case 4:
				obj.AM_BFS(0);
			break;
			case 5:
				obj.ASSCL_BFS(0);
			break;
			case 6:
				obj.EL_BFS(0);
			break;
		}
		end = clock();
		
		cout << n*i << " " << (double(end - begin) / CLOCKS_PER_SEC) << endl;
	}
	return 0;
}