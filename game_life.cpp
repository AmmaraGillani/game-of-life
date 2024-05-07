#include <iostream>
#include <fstream>
using namespace std;



// Function prototypes
void generations(int& gen_num); // Pass by reference to modify the original value
void number_of_cells(int& cell_num); // Pass by reference to modify the original value
void coordinates(int coord[][9], int number_of_cell);
void create_file(int coord[][9], int, int);
void grid_display (int coord[][9], int grid[20][20], int);
void neighborhood(int coord[][9],int nei[][9], int, int grid[20][20]);
void secondary(int coord[][9],int number_of_cell);
void start(); // start game




// Function for starting the game
void start() {
    
    const int MAX_SIZE = 100; // Maximum size for the 2D array
    int coord[MAX_SIZE][9]; // 2D array to store coordinates
    int nei[MAX_SIZE][9]; // 2D array to store neighbor coordinates
    int sec[MAX_SIZE][9]; // 2D array to store live cell's coordinates
    int grid[20][20] = {0};
    int gen_num;
    int cell_num;
    generations(gen_num);
    number_of_cells(cell_num);
    coordinates(coord, cell_num);
    create_file(coord, gen_num, cell_num);
    grid_display(coord, grid, cell_num);
    neighborhood(coord, nei, cell_num, grid);
    secondary(coord, cell_num);
}


// Function for entering the number of generations
void generations(int& gen_num) {
    cout << "Enter number of generations: ";
    cin >> gen_num;
}



// Function for entering the number of cells
void number_of_cells(int& cell_num) {
    cout << "Enter number of cells: ";
    cin >> cell_num;
}



// Function for entering the coordinates
void coordinates (int coord[][9],int number_of_cell){
    // Input coordinates
    cout << "Enter x and y coordinate: "  <<endl;
    for (int i = 0; i < number_of_cell; i++) {
        
        cin >> coord[i][0] >> coord[i][1]; // Store x and y coordinate
        
    }
    // Output coordinates
    cout << "\nCoordinates stored in the array:\n";
    for (int i = 0; i < number_of_cell; i++) {
        cout << "(" << coord[i][0] << ", " << coord[i][1] << ")\n";
    }
}



// Function for create, read and write file 
void create_file(int coord[][9], int gen_num, int cell_num)
{
    fstream file;
    file.open("game_of_life.txt", ios::out | ios::in);
    file << gen_num << endl; // write on file
    file << cell_num << endl; // write on file
     for (int i = 0; i < cell_num; i++) {
        
        file << coord[i][0] << coord[i][1]; // write x and y coordinate
        
    }
    file >> gen_num; // read on file
    file >> cell_num; // read on file
    for (int i = 0; i < cell_num; i++) {
        
        file >> coord[i][0] >> coord[i][1]; // read x and y coordinate
        
    }
    cout << "Data written to game_of_life.txt\n";
    file.close();
    
}

//Function for display grid
void grid_display(int coord[][9], int grid[20][20], int cell_num)
{
     int rows = 20 , cols = 20;
    for (int i = 0; i < cell_num; ++i) {
        int x = coord[i][0];
        int y = coord[i][1];
        if (x >= 0 && x < rows && y >= 0 && y < cols) {
            grid[x][y] = 1; // Set the cell to alive
        }
    }

    for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++)
             {
                
                cout << (grid[i][j] ) << ' '; // display grid
            }
        cout << endl;
        }
}


// Function for neighborhood cells
void neighborhood(int coord[][9], int nei[][9], int cell_num, int grid[20][20]) {
    const int rows = 20;
    const int cols = 20;
    for (int i = 0; i < cell_num; ++i) {
        int x = coord[i][0];
        int y = coord[i][1];
        if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1) {
            // Iterate over the 8 neighbors
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                        nei[i][0] = nx;
                        nei[i][1] = ny;
                    }
                }
            }
        }
    }   
}
 
// Function for secondary array of live cells
 void secondary (int coord[][9],int number_of_cell)
 {
    
    // Output coordinates
    cout << "\nCoordinates stored in the array:\n";
    for (int i = 0; i < number_of_cell; i++) {
        cout << "(" << coord[i][0] << ", " << coord[i][1] << ")\n";
    }
}   



int main() {
    start();
    return 0;
}
