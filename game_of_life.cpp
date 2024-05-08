#include <iostream>
#include <fstream>
#include <string.h>

#define GRID_X  20;
#define GRID_Y  20;

using namespace std;

struct coordinate {
    int x;
    int y;
};

void start();
void read_input_file(string file_name, int grid[20][20], coordinate* sec, int& last);
string get_user_input();
void display(int grid[20][20]);
void init_sec(coordinate[100], int last); 
void display_coordinates(coordinate* coordinates, int count);
void find_dead_neihbor(int grid[20][20],coordinate target ,coordinate* dead, int & count);
void insert_dead(int grid[20][20], int x, int y, coordinate* dead, int & count);


int main()
{
    start();
    return 0;
}

void start()
{
    int grid[20][20] = {0};
    coordinate sec[100];
    int last = 0;
    coordinate dead[300];
    int dead_counter = 0; 
    string file_name = get_user_input();
    read_input_file(file_name, grid, sec, last);
    display(grid);
    display_coordinates(sec,last);
    for(int i = 0; i < last; i++)
    {
        find_dead_neihbor(grid,sec[i],dead,dead_counter);
    }
    display_coordinates(dead, dead_counter);
}

// get input file name from the user
string get_user_input()
{
    string file_name;
    cout << "Enter file name: ";
    cin >> file_name;
    cout << file_name << endl;
    return file_name;
}

// read input from file
void read_input_file(string file_name, int grid[20][20], coordinate* sec, int& last)
{
    ifstream file;
    int generation;
    int number_of_cell;
    file.open(file_name.c_str());

    if (file.is_open())
    {
        int x, y; 
        file >> generation;
        file >> number_of_cell;
        for (int i = 0; i < number_of_cell; i++)
        {
            coordinate alive;
            file >> x;
            file >> y;
            grid[x][y] = 1;
            alive.x = x;
            alive.y = y;
            sec[i] = alive;
            last++;  
        }
    }
    file.close(); 
}
// display grid
void display(int grid[20][20])
{
    for (int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            cout << grid[i][j] << "\t";
        }
        cout << endl;
    }
}
// initialize secondary array
void init_sec(coordinate[100], int last)
{

} 
// function for display secondary and neighbor array 
void display_coordinates(coordinate* coordinates, int count)
{
    for(int i = 0; i < count; i++)
    {
        cout << "{" << coordinates[i].x << ", " << coordinates[i].y << "}";
    }
    cout << endl;
}
// function for finding dead neighborhood
void find_dead_neihbor(int grid[20][20], coordinate target, coordinate* dead, int & count)
{
    insert_dead(grid, target.x - 1, target.y - 1,dead,count);
    int x = target.x - 1;
    int y = target.y - 1;
   if (grid[x][y] == 0 && x >= 0 && y >= 0)
   {
        coordinate die;
        die.x = x;
        die.y = y;
        dead[count++] = die;
        
   } 
   if (grid[target.x][target.y - 1] == 0 && (target.x) >= 0 && (target.y - 1) >= 0)
   {
        coordinate die;
        die.x = target.x;
        die.y = target.y - 1;
        dead[count++] = die;
        
   } 
   if (grid[target.x + 1][target.y - 1] == 0 && (target.x + 1) >= 0 && (target.y - 1) >= 0)
   {
        coordinate die;
        die.x = target.x + 1;
        die.y = target.y - 1;
        dead[count++] = die;
        
   } 
   if (grid[target.x - 1][target.y] == 0 && (target.x - 1) >= 0 && (target.y) >= 0)
   {
        coordinate die;
        die.x = target.x - 1;
        die.y = target.y;
        dead[count++] = die;
        
   } 
   if (grid[target.x + 1][target.y] == 0 && (target.x + 1) >= 0 && (target.y) >= 0)
   {
        coordinate die;
        die.x = target.x + 1;
        die.y = target.y;
        dead[count++] = die;
        
   } 
   if (grid[target.x - 1][target.y + 1] == 0 && (target.x - 1) >= 0 && (target.y + 1) >= 0)
   {
        coordinate die;
        die.x = target.x - 1;
        die.y = target.y + 1;
        dead[count++] = die;
        
   } 
   if (grid[target.x][target.y + 1] == 0 && (target.x) >= 0 && (target.y + 1) >= 0)
   {
        coordinate die;
        die.x = target.x;
        die.y = target.y + 1;
        dead[count++] = die;
        
   } 
   if (grid[target.x + 1][target.y + 1] == 0 && (target.x + 1) >= 0 && (target.y + 1) >= 0)
   {
        coordinate die;
        die.x = target.x + 1;
        die.y = target.y + 1;
        dead[count++] = die;
        
   } 
}

void insert_dead(int grid[20][20], int x, int y, coordinate* dead, int & count)
{
    if (grid[x][y] == 0 && x >= 0 && y >= 0)
   {
        coordinate die;
        die.x = x;
        die.y = y;
        dead[count++] = die;
        
   }
}
