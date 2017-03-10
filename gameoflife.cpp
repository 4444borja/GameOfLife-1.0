// Autor of the code: Borja Aguado Diez
// Last revision: 

#include <iostream>
using namespace std;

// Conway's game of life: https://en.wikipedia.org/wiki/Conway's_Game_of_Life
// In this program, the cells are represented with a boolean list,
// true if alive, false if dead. But coordenates are also used (row x coloumn)
// Example with a map of dimension 3 -> 9 cells, arranged in a 3x3 square:
// List --> [0,1,2,3,4,5,6,7,8]
// When printed in screen:	0 1 2	Example: index=5 - 	row = 1
//							3 4 5						col = 2
// 							6 7 8
// List index to row and coloumn --> row = i/dim, coloumn = i%dim
// Row and coloumn to list index --> index = row*dim + coloumn
// (In the example, dim = 3)

// Pre: dim is the square root of the lenght of list (dim = side of the square)
// Post: Aux contains a replica of list
void copyList(const bool list[], bool aux[], const int dim){
	for(int i=0; i<dim*dim; i++){
		aux[i] = list[i];
	}
}

// Pre: dim is the square root of the lenght of list (dim = side of the square)
// Post: Edits the list of alive/dead cells to get the next generation
void nextGen(bool list[], const int dim){
	bool aux[dim*dim];
	copyList(list, aux, dim);
	for(int i=0; i<dim*dim; i++){
		int row = i/dim;
		int col = i%dim;
		
		int rown1 = row-1; int coln1 = col-1;
		int rown2 = row-1; int coln2 = col;
		int rown3 = row-1; int coln3 = col+1;
		int rown4 = row; int coln4 = col+1;
		int rown5 = row+1; int coln5 = col+1;
		int rown6 = row+1; int coln6 = col;
		int rown7 = row+1; int coln7 = col-1;
		int rown8 = row; int coln8 = col-1;
		
		int in1 = rown1*dim+coln1;
		int in2 = rown2*dim+coln2;
		int in3 = rown3*dim+coln3;
		int in4 = rown4*dim+coln4;
		int in5 = rown5*dim+coln5;
		int in6 = rown6*dim+coln6;
		int in7 = rown7*dim+coln7;
		int in8 = rown8*dim+coln8;
		
		int aliveNeigh = 0;
		
		if(row!=0){
			if(col!=0){
				if(aux[in1]){aliveNeigh++;}
			}
			if(aux[in2]){aliveNeigh++;}
			if(col!=dim-1){
				if(aux[in3]){aliveNeigh++;}
			}
		}
		if(col!=dim-1){
			if(aux[in4]){aliveNeigh++;}
		}
		if(row!=dim-1){
			if(col!=dim-1){
				if(aux[in5]){aliveNeigh++;}
			}
			if(aux[in6]){aliveNeigh++;}
			if(col!=0){
				if(aux[in7]){aliveNeigh++;}
			}
		}
		if(col!=0){
			if(aux[in8]){aliveNeigh++;}
		}
		
		// If the cell is alive
		if(aux[i]){
			// and has not 2 or 3 neighbours alive, it dies
			if(!(aliveNeigh==2 || aliveNeigh==3)){
				list[i] = false;
			}
		}
		// If teh cell is dead
		else{
			// and has 3 alive neighbours, it is born
			if(aliveNeigh==3){
				list[i]=true;
			}
		}
	}
}

// Pre: dim is the square root of the lenght of list (dim = side of the square)
// Post: Print the cells on the screen drawing a square of size dim x dim
void printCells(const bool list[], const int dim){
	for(int rows=0; rows<dim; rows++){
		for(int cols=0; cols<dim; cols++){
			
			if(list[rows*dim+cols]){
				cout << " # ";
			}
			else{
				cout << " . ";
			}
		}
		cout << endl;
	}
}

// Pre: num >= 0, dim is the square root of the lenght of list (dim = side of
//		the square)
// Returns true only if int num is in the list ini
bool isIn(const int num, const int ini[], const int dim){
	for(int j=0; j<dim*dim; j++){
		if(num==ini[j]){
			return true;
		}
	}
	return false;
}

// Pre: dim is the square root of the lenght of list, ini[] contains the number
//		of the cells which are alive
// Post: Modifies the list[], to set which cells are alive at the start
void setCells(bool list[], const int dim, const int ini[]){
	for(int i=0; i<dim*dim; i++){
		if(isIn(i+1, ini, dim)){
			list[i] = true;
		}
	}
}

// Pre: dim is the square root of the lenght of list (dim = side of the square)
// Post: Set all the elements of the list to false
void allDead(bool list[], const int dim){
	for(int i=0; i<dim*dim; i++){
		list[i] = false;
	}
}

// Pre: dim is the side of the list, row < dim, col < dim
// Post: ini contains the index of the cell (row x col) plus 1
void setCell(int ini[], const int row, const int col, const int dim){
	// CellNum = index + 1
	int cellNum = row*dim + col + 1;
	int i=0;
	while(ini[i]!='\0'){
		i++;
	}
	ini[i] = cellNum;
	ini[i+1] = '\0';
}

// Prints a menu of available options
void showOptions(int& o, const bool set){
	system("CLS");
	if(!set){
		cout << "Not valid, not set" << endl;
	}
	cout << "1. Add alive cell (row and column, starting with 0)" << endl;
	cout << "2. Start simulation (press enter for each generation)" << endl;
	cout << ">> ";
	cin >> o;
}

int main(){
	system("CLS");
	cout << "Welcome, to end the program at any point, press contol+c" << endl;
	cout << endl;
	// dim is the side of the square (the map)
	int dim;
	cout << "The map is a square, enter the desired size of the side: ";
	cin >> dim;
	
	// For ini, use this distribution (example dim=3):
	//	1 2 3
	//	4 5 6
	//	7 8 9
	// If the number 2 is contained in ini[], that means the cell 2 is alive
	int ini[dim*dim] = {'\0'};
	
	int o;
	bool cellSet = true;
	while(o!=2){
		showOptions(o,cellSet);
		if(o==1){
			int row, col;
			cout << "Enter row: ";
			cin >> row;
			cout << "Enter column: ";
			cin >> col;
			if(row<dim && col<dim && row>-1 && col>-1){
				setCell(ini,row,col,dim);
				cellSet = true;
			}
			else{
				cellSet = false;
			}
		}
	}
	
	// If the element of the list is true, that cell is alive
	bool list[dim*dim];
	allDead(list,dim);
	
	setCells(list, dim, ini);
	
	cin.get();
	while(true){
		system("CLS");
		printCells(list,dim);
		cin.get();
		nextGen(list,dim);
	}
	return 0;
}