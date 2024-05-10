#include <iostream>
#include <fstream>
#include <string.h>

#define GRID_X  20
#define GRID_Y  20
#define SEC_SIZE 100
#define NEI_SIZE 300

using namespace std;

struct coordinate {
    int x;
    int y;
};

void start();
void read_input_file(string file_name, int grid[GRID_X][GRID_Y], coordinate* sec, int& last, int& generation);
string get_user_input();
void display(int grid[GRID_X][GRID_Y]);
void display_coordinates(coordinate* coordinates, int count);
void find_dead_neihbor(int grid[GRID_X][GRID_Y], coordinate target, coordinate* dead, int & count);
void insert_dead(int grid[GRID_X][GRID_Y], int x, int y, coordinate* dead, int & count);
int is_exist(coordinate* arr, int count, int x, int y);
int is_neighbor(int x1, int y1, int x2, int y2);
int count_neighbors(int grid[GRID_X][GRID_Y], coordinate target);
void apply_rule_birth(int grid[GRID_X][GRID_Y], coordinate* dead, int dead_counter, coordinate *birth_result, int birth_result_counter);
void apply_rule_survival(int grid[GRID_X][GRID_Y], coordinate *dead, int dead_counter);
void apply_rule_loneliness(int grid[GRID_X][GRID_Y], coordinate *dead, int dead_counter);
void apply_rule_overcrowding(int grid[GRID_X][GRID_Y], coordinate *dead, int dead_counter);
void apply_rules (int grid[GRID_X][GRID_Y], coordinate* sec, int last, coordinate *dead,int dead_counter);

int main() {
    start();
    return 0;
}

void start() {
    int grid[GRID_X][GRID_Y] = {0};
    coordinate sec[SEC_SIZE];
    int last = 0;
    coordinate dead[NEI_SIZE];
    int dead_counter = 0;
    int live_count[SEC_SIZE];
    int live_counter = 0;
    int generation = 0;
    
    // string file_name = get_user_input();
    string file_name = "input2.txt";
    read_input_file(file_name, grid, sec, last, generation);
    display(grid);
    display_coordinates(sec, last);
    for(int i = 0; i < last; i++) 
    {
        find_dead_neihbor(grid, sec[i], dead, dead_counter);
    }
    display_coordinates(dead, dead_counter);
    for (int i = 0; i < last; i++) {
        live_count[i] = count_neighbors(grid, sec[i]);
        live_counter++;
        
    }

     cout << " Display of Secondary-array and count" << endl;
    for (int i = 0; i < live_counter; i++) {
        cout<< "(" << sec[i].x << ", " << sec[i].y << "): " << live_count[i] << "\t";
        
    }
    cout<< endl;
    cout << " Display of Neighbor-array and count" << endl;
     for (int i = 0; i < dead_counter; i++)
      {
        int dead_neighbors = count_neighbors(grid, dead[i]);
        cout << "(" << dead[i].x << ", " << dead[i].y << "): " << dead_neighbors << "\t";
        
      }
    cout << endl;
    for (int i = 0; i < 1; i++)
    {
        apply_rules(grid, sec, last, dead, dead_counter);
    }
     
}

// get input file name from the user
string get_user_input() {
    string file_name;
    cout << "Enter file name: ";
    cin >> file_name;
    cout << file_name << endl;
    return file_name;
}

// read input from file
void read_input_file(string file_name, int grid[GRID_X][GRID_Y], coordinate* sec, int& last, int & generation) {
    ifstream file;
    int number_of_cell;
    file.open(file_name.c_str());

    if (file.is_open()) {
        int x, y;
        file >> generation;
        file >> number_of_cell;
        for (int i = 0; i < number_of_cell; i++) {
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
void display(int grid[GRID_X][GRID_Y]) {
    for (int i = 0; i < GRID_X; i++) {
        for(int j = 0; j < GRID_Y; j++) {
            cout << grid[i][j] << "\t";
        }
        cout << endl;
    }
}



// function for display secondary and neighbor array
void display_coordinates(coordinate* coordinates, int count) {
    for(int i = 0; i < count; i++) {
        cout << "{" << coordinates[i].x << ", " << coordinates[i].y << "}";
    }
    cout << endl;
}

// function for finding dead neighborhood
void find_dead_neihbor(int grid[GRID_X][GRID_Y], coordinate target, coordinate* dead, int & count) {
    insert_dead(grid, target.x - 1, target.y - 1, dead, count);
    insert_dead(grid, target.x, target.y - 1, dead, count);
    insert_dead(grid, target.x + 1, target.y - 1, dead, count);
    insert_dead(grid, target.x - 1, target.y, dead, count);
    insert_dead(grid, target.x + 1, target.y, dead, count);
    insert_dead(grid, target.x - 1, target.y + 1, dead, count);
    insert_dead(grid, target.x, target.y + 1, dead, count);
    insert_dead(grid, target.x + 1, target.y + 1, dead, count);
}

void insert_dead(int grid[GRID_X][GRID_Y], int x, int y, coordinate* dead, int & count) {
    if (grid[x][y] == 0 && x >= 0 && y >= 0 && is_exist(dead, count, x, y) == 1) {
        coordinate die;
        die.x = x;
        die.y = y;
        dead[count++] = die;
    }
}

int is_exist(coordinate* arr, int count, int x, int y) {
    for(int i = 0; i < count; i++) {
        if(arr[i].x == x && arr[i].y == y) {
            return 0;
        }
    }
    return 1;
}

int is_neighbor(int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) {
        return 1;
    }
    if (abs(x1 - x2) < 2 && abs(y1 -y2)) {
        return 0;
    }
    else {
        return 1;
    }
}

// Count neighbors for sec-array and nei-array
int count_neighbors(int grid[GRID_X][GRID_Y], coordinate target) {
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int nx = target.x + dx;
            int ny = target.y + dy;
            if (nx >= 0 && nx < GRID_X && ny >= 0 && ny < GRID_Y && !(dx == 0 && dy == 0)) {
                count += grid[nx][ny];
            }
        }
    }
    return count;
}

void apply_rule_birth(int grid[GRID_X][GRID_Y], coordinate *dead, int dead_counter, coordinate *birth_result, int birth_result_count)
{
    for(int i = 0; i < dead_counter; i++)
    {
        int dead_neighbors = count_neighbors(grid, dead[i]);
        if (dead_neighbors == 3)
        {
            cout << dead[i].x << "," << dead[i].y << endl;
            birth_result_count++;
        }
    
    }
}
void apply_rule_survival(int grid[GRID_X][GRID_Y], coordinate *sec, int last)
{
    for(int i = 0; i < last; i++)
    {
        int sec_counter = count_neighbors(grid, sec[i]);
        if (sec_counter == 2 || sec_counter == 3)
        {
            cout << sec[i].x << "," << sec[i].y << endl;
        }
    
    }
}
void apply_rule_loneliness(int grid[GRID_X][GRID_Y], coordinate *sec, int last)
{
    for(int i = 0; i < last; i++)
    {
        int sec_counter = count_neighbors(grid, sec[i]);
        if (sec_counter == 0 || sec_counter == 1)
        {
            cout << sec[i].x << "," << sec[i].y << endl;
        }
    
    }
}

void apply_rule_overcrowding(int grid[GRID_X][GRID_Y], coordinate *sec, int last)
{
    for(int i = 0; i < last; i++)
    {
        int sec_counter = count_neighbors(grid, sec[i]);
        if (sec_counter > 3)
        {
            cout << sec[i].x << "," << sec[i].y << endl;
        }
    
    }
}

void apply_rules (int grid[GRID_X][GRID_Y], coordinate* sec, int last, coordinate *dead,int dead_counter)
{
    coordinate *birth_result;
    int birth_result_count = 0;
    
    apply_rule_birth(grid, dead, dead_counter, birth_result, birth_result_count);
    apply_rule_survival(grid, sec, last);
    apply_rule_loneliness(grid, sec, last);
    apply_rule_overcrowding(grid, sec, last);
}
