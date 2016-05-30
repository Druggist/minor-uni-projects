#include "../headers/graphs.h"
#include "../headers/cycles.h"

int main(int argc, char *argv[]) {
clock_t begin, end;
	if(argc < 2) return 1;
    int n = atoi(argv[1]);
	int mode =  atoi(argv[2]);
	bool execMode = (argc == 2)?(true):(atoi(argv[3])); //1 - graph sort; 0 - cycle algorithms;
	
	if(execMode){
		for(int i=1; i<=10; i++){
			begin = clock();
			Graph obj(n*i);
			obj.sort(mode);
			end = clock();
			
			cout << n*i << " " << (double(end - begin) / CLOCKS_PER_SEC) << endl;
		}
	}else{
		for(int i=1; i<=10; i++){
			begin = clock();
			Cycles obj(n*i, 0.7, mode);
			obj.findHamiltonCycle(0);
			end = clock();
			
			cout << n*i << " " << (double(end - begin) / CLOCKS_PER_SEC) << endl;
		}
	}
	return 0;
}