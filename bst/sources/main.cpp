#include "../headers/main.h" 
#include "../headers/bst.h" 
#include "../headers/data.h" 

bstNode *ROOT = NULL;

int main(int argc, char *argv[]){
	measureTasksTime(0);
	destroyBst(ROOT);
	destroyData();
	return 0;
}



void fillBst(){
	for(int i = 0; i < elements; i++) ROOT = insertBstNode(data[i], ROOT); 
}

void fillBstList(){
	sortData();
	fillBst();
}

void insertBst(){
	for(int i = 0; i < size - elements; i++){
		insertBstNode(data[elements + i], ROOT);
	}
}

void searchBst(){
	uniform_int_distribution<int> range(0, elements - 1); //set random range
	for(int i = 0; i < size - elements; i++){
		searchBstNode(data[range(mt)], ROOT);
	}
}

void deleteBst(){
	uniform_int_distribution<int> range(0, elements - 1); //set random range
	for(int i = 0; i < size - elements; i++){
		deleteBstNode(data[range(mt)], ROOT);
	}
}

void measureTasksTime(int type){
	stringstream buffer;
	ofstream file;
	clock_t begin, end;
	buffer << "Elements " << "Create " << "Search " << "Delete " << "Insert" << endl;
	if(type == 0 || type == 2){
		for(int i = 1; i <= 10; i++){
			setSize(1000000 * i);
			generateData();
			buffer << (1000000 * i) << " ";
			begin = clock();
			if(type == 0) fillBst();
			else fillBstList();
			end = clock();
			buffer << (double(end - begin) / CLOCKS_PER_SEC) << " ";

			begin = clock();
			searchBst();
			end = clock();
			buffer << (double(end - begin) / CLOCKS_PER_SEC) << " ";

			begin = clock();
			deleteBst();
			end = clock();
			buffer << (double(end - begin) / CLOCKS_PER_SEC) << " ";

			begin = clock();
			insertBst();
			end = clock();
			buffer << (double(end - begin) / CLOCKS_PER_SEC) << " ";

			buffer << endl;
		}
	}else{
		for(int i = 1; i <= 10; i++){
			//avl measurements
			buffer << endl;
		}
	}
  	file.open ("data.txt");
  	file << buffer.rdbuf();
  	file.close();
}