// Autor of the code: Borja Aguado Diez
// Last revision: 2017/03/10

#include <iostream>
using namespace std;

// Conway's game of life: https://en.wikipedia.org/wiki/Conway's_Game_of_Life
// In this program, the cells are represented with a boolean list,
// true if alive, false if dead. But coordenates are also used (row x coloumn)
// Example with a map of dimension 3 -> 9 cells, arranged in a 3x3 square:
// List --> [0,1,2,3,4,5,6,7,8]
// When printed in screen:	
// 0 1 2
// 3 4 5
// 6 7 8
// Example: index = 5 -> row = 1, col = 2
// List index to row and coloumn --> row = i/dimension, coloumn = i%dimension
// Row and coloumn to list index --> index = row*dimension + coloumn

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
	// aux[] is now a copy of list[]
	
	for(int i=0; i<dim*dim; i++){
		int row = i/dim;
		int col = i%dim;
		
		// Get the coordenates of the 8 neighbours of the current cell
		int rown1 = row-1; int coln1 = col-1;
		int rown2 = row-1; int coln2 = col;
		int rown3 = row-1; int coln3 = col+1;
		int rown4 = row; int coln4 = col+1;
		int rown5 = row+1; int coln5 = col+1;
		int rown6 = row+1; int coln6 = col;
		int rown7 = row+1; int coln7 = col-1;
		int rown8 = row; int coln8 = col-1;
		
		// Get the index of the neighbours in the list aux[]
		int in1 = rown1*dim+coln1;
		int in2 = rown2*dim+coln2;
		int in3 = rown3*dim+coln3;
		int in4 = rown4*dim+coln4;
		int in5 = rown5*dim+coln5;
		int in6 = rown6*dim+coln6;
		int in7 = rown7*dim+coln7;
		int in8 = rown8*dim+coln8;
		
		int aliveNeigh = 0;
		// Map of the neighbours (cc = current cell):
		// n1 n2 n3
		// n8 cc n4
		// n7 n6 n5
		
		// Calculate how many neighbours are alive, considering that the cells
		//		placed in the boundaries of the map have less neighbours
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
void printCells(const bool list[], const int dim, const char alive, const char dead){
	for(int rows=0; rows<dim; rows++){
		for(int cols=0; cols<dim; cols++){
			// If the cell (row x col) is alive (true in the boolean list)
			if(list[rows*dim+cols]){
				cout << " " << alive << " ";
			}
			else{
				cout << " " << dead << " ";
			}
		}
		cout << endl;
	}
}

// Pre: num >= 0, dim is the square root of the lenght of list (dim = side of
//		the square)
// Post: Returns true only if int num is in the list ini
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
	// If the cell is not already in the list, it is added
	if(!isIn(cellNum,ini,dim)){
		ini[i] = cellNum;
		ini[i+1] = '\0';
	}
}

// Prints a menu of available options
void showOptions(int& o, const bool set){
	system("CLS");
	if(!set){
		cout << "Not valid, not set" << endl;
	}
	cout<< "1. Add alive cell (row and column, starting with 0)" << endl;
	cout<< "2. Load example (when loaded, select 3 to start simulation)"<<endl;
	cout<< "3. Start simulation (press enter for each generation)" << endl;
	cout<< ">> ";
	cin >> o;
}

int main(){
	// Select characters to represent alive cells and dead cells
	const char alive = '#';
	const char dead = ' ';
	
	system("CLS");
	cout << "Welcome, to end the program at any point, press contol+c" << endl;
	cout << endl;
	// dim is the side of the square (the map)
	int dim;
	cout << "The map is a square, enter the desired size of the side: ";
	cin >> dim;
	
	// For initial list, use this distribution (example dim=3):
	//	1 2 3
	//	4 5 6
	//	7 8 9
	// If the number 2 is contained in ini[], that means the cell 2 is alive
	int ini[dim*dim] = {'\0'};
	
	// Flag to control if the user has added successfully a cell or not
	// If not, showOptions(o,cellSet) will display an error message 
	bool cellSet = true;
	int o;
	while(o!=3){
		showOptions(o,cellSet);
		if(o==1){
			int row, col;
			cout << "Enter row: ";
			cin >> row;
			cout << "Enter column: ";
			cin >> col;
			// If (0 <= row < dim) and (0 <= col < dim)
			//		(if the cell exists on the map)
			if(row<dim && col<dim && row>-1 && col>-1){
				setCell(ini,row,col,dim);
				cellSet = true;
			}
			else{
				cellSet = false;
			}
		}
		if(o==2){
			// Pick a reference to set the cells
			const int ref = dim/2-1;
			// Set a specific pattern of 5 cells
			setCell(ini,ref,ref,dim);
			setCell(ini,ref,ref+1,dim);
			setCell(ini,ref+1,ref+1,dim);
			setCell(ini,ref+1,ref+2,dim);
			setCell(ini,ref+2,ref+1,dim);
			cellSet = true;
		}
	}
	
	// If the element of the list is true, that cell is alive
	bool list[dim*dim];
	allDead(list,dim);
	
	setCells(list, dim, ini);
	int gen = 0;
	
	cin.get();
	while(true){
		system("CLS");
		printCells(list,dim,alive,dead);
		cout << "Generation " << gen << endl;
		cin.get();
		nextGen(list,dim);
		gen++;
	}
	return 0;
}