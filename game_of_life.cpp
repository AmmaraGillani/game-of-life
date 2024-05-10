#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

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
void display_coordinates(coordinate coordinates[], int count);
void find_dead_neihbor(int grid[GRID_X][GRID_Y], coordinate target, coordinate* dead, int & count);
void insert_dead(int grid[GRID_X][GRID_Y], int x, int y, coordinate* dead, int & count);
int is_exist(coordinate* arr, int count, int x, int y);
int is_neighbor(int x1, int y1, int x2, int y2);
int count_neighbors(int grid[GRID_X][GRID_Y], coordinate target);
vector<coordinate> apply_rule_birth(int grid[GRID_X][GRID_Y], coordinate *dead, int dead_counter);
vector<coordinate> apply_rule_survival(int grid[GRID_X][GRID_Y], coordinate *sec, int last);
vector<coordinate> apply_rule_loneliness(int grid[GRID_X][GRID_Y], coordinate *dead, int dead_counter);
vector<coordinate> apply_rule_overcrowding(int grid[GRID_X][GRID_Y], coordinate *dead, int dead_counter);
void apply_rules (int grid[GRID_X][GRID_Y], coordinate* sec, int last, coordinate dead[],int &dead_counter);
int delete_element(coordinate arr[], int &size, coordinate x);
void delete_elements(vector<coordinate> delete_items, coordinate arr[], int &size);
void add_element(coordinate arr[], int &size, vector<coordinate>new_items);
void display_coordinate_count(int grid[GRID_X][GRID_Y], coordinate cord[], int size);
void simulate_generation(int grid[GRID_X][GRID_Y], coordinate sec[], int &last, coordinate nei[], int &nei_size, int generations);
void populated_grid(int grid[GRID_X][GRID_Y], coordinate sec[], int last);
void fill_nei(int grid[GRID_X][GRID_Y], coordinate sec[], int last, coordinate nei[], int &nei_size);

int main() {
    start();
    return 0;
}

void start() {
    int grid[GRID_X][GRID_Y] = {0};
    coordinate sec[SEC_SIZE];
    int last = 0;
    coordinate nei[NEI_SIZE];
    int nei_size = 0;
    int generation = 0;
    
    // string file_name = get_user_input();
    string file_name = "input2.txt";
    read_input_file(file_name, grid, sec, last, generation);
    populated_grid(grid, sec, last);
    fill_nei(grid, sec, last, nei, nei_size);
    cout << "Display secondary array" << endl;
    display_coordinate_count(grid, sec, last);
    cout << "Display neighbor array" << endl;
    display_coordinate_count(grid, nei, nei_size);
    cout << "Display populated grid" << endl;
    display(grid);
    simulate_generation(grid, sec, last, nei, nei_size, generation);
     
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
            //grid[x][y] = 1;
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
void display_coordinates(coordinate coordinates[], int count) {
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

vector<coordinate> apply_rule_birth(int grid[GRID_X][GRID_Y], coordinate *dead, int dead_counter)
{
    vector<coordinate> birth_result;
    for(int i = 0; i < dead_counter; i++)
    {
        int dead_neighbors = count_neighbors(grid, dead[i]);
        if (dead_neighbors == 3)
        {
            birth_result.push_back(dead[i]);
            
        }
    }
    return birth_result;
}
vector<coordinate> apply_rule_survival(int grid[GRID_X][GRID_Y], coordinate *sec, int last)
{
    vector<coordinate> survival_result;
    for(int i = 0; i < last; i++)
    {
        int sec_counter = count_neighbors(grid, sec[i]);
        if (sec_counter == 2 || sec_counter == 3)
        {
            survival_result.push_back(sec[i]);
            
        }
    
    }
    return survival_result;
}
vector<coordinate> apply_rule_loneliness(int grid[GRID_X][GRID_Y], coordinate *sec, int last)
{
    vector<coordinate> loneliness_result;
    for(int i = 0; i < last; i++)
    {
        int sec_counter = count_neighbors(grid, sec[i]);
        if (sec_counter == 0 || sec_counter == 1)
        {
            loneliness_result.push_back(sec[i]);
        }
    
    }
    return loneliness_result;
}

vector<coordinate> apply_rule_overcrowding(int grid[GRID_X][GRID_Y], coordinate *sec, int last)
{
    vector<coordinate> overcrowding_result;
    for(int i = 0; i < last; i++)
    {
        int sec_counter = count_neighbors(grid, sec[i]);
        if (sec_counter > 3)
        {
            overcrowding_result.push_back(sec[i]);
        }
    
    }
    return overcrowding_result;
}

void apply_rules (int grid[GRID_X][GRID_Y], coordinate* sec, int last, coordinate nei[],int &nei_size)
{
    vector<coordinate> birth_result = apply_rule_birth (grid, nei, nei_size);
    vector<coordinate> survival_result = apply_rule_survival(grid, sec, last);
    vector<coordinate> loneliness_result =  apply_rule_loneliness(grid, sec, last);
    vector<coordinate> overcrowding_result = apply_rule_overcrowding(grid, sec, last);
    // remove birth from neigbor array
    delete_elements(birth_result, nei, nei_size);
    add_element(sec, last, birth_result);
    // remove dead from secondary array
    delete_elements(loneliness_result, sec, last);
    // remove all element from nei -array
    nei_size = 0;
    //update grid
    populated_grid(grid, sec, last);
    display(grid);
    cout << endl; 
}
//delete 
int delete_element(coordinate arr[], int &size, coordinate x) 
{ 
    // Search x in array 
    int i; 
    for (i = 0; i < size; i++) 
        if (arr[i].x == x.x && arr[i].y == x.y) 
            break; 
  
    // If x found in array 
    if (i < size) { 
        // reduce size of array and move all 
        // elements on space ahead 
        size = size - 1; 
        for (int j = i; j < size; j++) 
            arr[j] = arr[j + 1]; 
    } 
  
    return size; 
}

void delete_elements(vector<coordinate> delete_items, coordinate arr[], int &size)
{
    for(int i = 0; i < delete_items.size(); i++)
    {
        delete_element(arr, size, delete_items.at(i));
        
    }
}

void add_element(coordinate arr[], int &size, vector<coordinate>new_items)
{
    for( int i = 0; i < new_items.size(); i++)
    {
        arr[size++] = new_items.at(i);
    }
}

void display_coordinate_count(int grid[GRID_X][GRID_Y], coordinate cord[], int size)
{
     for (int i = 0; i < size; i++)
      {
        int count = count_neighbors(grid, cord[i]);
        cout << "(" << cord[i].x << ", " << cord[i].y << "): " << count << "\t";
        
      }
      cout << endl;
}

void simulate_generation(int grid[GRID_X][GRID_Y], coordinate sec[], int &last, coordinate nei[], int &nei_size, int generations)
{
    for (int i = 0; i < 1; i++)
    {
        cout << "Generation " << i + 1 << endl;
        apply_rules(grid, sec, last, nei, nei_size);
    }
    
}

void populated_grid(int grid[GRID_X][GRID_Y], coordinate sec[], int last)
{
    for(int i = 0; i < GRID_X; i++)
    {
        for(int j = 0; j < GRID_Y; j++)
        {
            grid[i][j] = 0;
        }
    }
    for (int i = 0; i < last; i++)
    {
            coordinate alive;
            grid[sec[i].x][sec[i].y] = 1;
    }
}

void fill_nei(int grid[GRID_X][GRID_Y], coordinate sec[], int last, coordinate nei[], int &nei_size)
{
    for(int i = 0; i < last; i++) 
    {
        find_dead_neihbor(grid, sec[i], nei, nei_size);
    }
}
