#include "../headers/main.h" 
#include "../headers/bst.h" 
#include "../headers/data.h" 

bstNode *ROOT = NULL;
string FILENAME = "bstlist.txt";
int main(int argc, char *argv[]){
	measureTasksTime(2);
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

void fillAvl(){
	sortData();
	ROOT = insertAvlNode(0, elements-1, ROOT);
}

void balanceAvl(){
	inOrder(ROOT, -1);
	postOrder(ROOT);
	fillAvl();
}


void insertBst(){
	for(int i = 0; i < size - elements; i++){
		insertBstNode(data[elements + i], ROOT);
	}
	elements += (size - elements);
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
	elements -= (size - elements);
}

void measureTasksTime(int type){
	stringstream buffer;
	ofstream file;
	clock_t begin, end;
	
	buffer << "Elements " << "Create " << "Search " << "Delete " << "Insert " << "Height " << endl;
		
	if(type == 0 || type == 2){
		for(int i = 1; i <= 10; i++){
			setSize(100000 * i);
			generateData();
			buffer << (100000 * i) << " ";
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

			//buffer << height(ROOT);
			buffer << endl;
		}
	}else{
		//Avl
		for(int i = 1; i <= 10; i++){
			setSize(100000 * i);
			generateData();
			buffer << (100000 * i) << " ";
			
			begin = clock();
			fillAvl();
			end = clock();
			buffer << (double(end - begin) / CLOCKS_PER_SEC) << " ";
			
			begin = clock();
			searchBst();
			end = clock();
			buffer << (double(end - begin) / CLOCKS_PER_SEC) << " ";

			begin = clock();
			deleteBst();
			balanceAvl();
			end = clock();
			buffer << (double(end - begin) / CLOCKS_PER_SEC) << " ";
			
			setSize(1000000 * i);
			generateData();
			
			begin = clock();
			insertBst();
			balanceAvl();
			end = clock();
			buffer << (double(end - begin) / CLOCKS_PER_SEC) << " ";

			buffer << endl;
		}
	}
  	file.open (FILENAME);
  	file << buffer.rdbuf();
  	file.close();
}