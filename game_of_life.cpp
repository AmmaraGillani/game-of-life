#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
const int rows = 20; // for grid size
const int cols = 20; // for grid size

// Function to print the grid
    void printGrid(int grid[rows][cols]) 
    {
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j)
             {
                cout << (grid[i][j] ) << ' ';
            }
        cout << endl;
        }
    }
int main() {
    
    int generations;
    int number_of_cell;
    int cord1[number_of_cell];
    int cord2[number_of_cell];
    

    fstream file;
    file.open("game_of_life.txt", ios::out | ios::in);

    cout << "Enter number of generations: ";
    cin >> generations;
    file << generations << endl; // write on file

    cout << "Enter number of cells to be alive: ";
    cin >> number_of_cell;
    file << number_of_cell << endl; // write on file

    cout << "Enter coordinates:" << endl;
    for (int i = 0; i < number_of_cell; i++) {
        cin >> cord1[i];
        cin >> cord2[i];
        file << cord1[i] << " " << cord2[i] << endl;//write on file
    }

    cout << "Reading from file" << endl;
    file >> generations; // read on file
    file >> number_of_cell; // read on file

    cout << "Generations: " << generations << "\nNumber of cells: " << number_of_cell << endl;
    cout << "Coordinates:" << endl;
    for (int i = 0; i < number_of_cell; i++) {
        file >> cord1[i] >> cord2[i];
        
        cout << cord1[i] << " " << cord2[i] << endl;
    }
 
  
    int grid[rows][cols] = {0};
    for (int i = 0; i < number_of_cell; ++i) {
        int x = cord1[i];
        int y = cord2[i];
        if (x >= 0 && x < rows && y >= 0 && y < cols) {
            grid[x][y] = 1; // Set the cell to alive
        }
    }
    
    
printGrid(grid);


    file.close();
    return 0;
}