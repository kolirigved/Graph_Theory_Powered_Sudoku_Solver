// Graph_Theory_Powered_Sudoku_solver

#include <bits/stdc++.h>
using namespace std;

void print_sudoku_board(int* color);

// Function to check if two nodes are neighbors in the graph
bool isneighour(vector<int>* graph, int node1, int node2){ 
    for(int i=0;i<graph[node1].size();i++){
        if(graph[node1][i]==node2) return true;
    }
    return false;
}

// Function to add an edge between two nodes in the graph
void add_edge(vector<int>* graph, int node1, int node2){
    if(!isneighour(graph,node1,node2)){
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }
    return;
}

// Function to create connections between nodes in the Sudoku puzzle
void make_sudoku_connections(vector<int>* graph){
    int rows = 9, cols = 9;

    // Connect nodes in the same row
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            for(int k = j + 1; k < cols; ++k) {
                add_edge(graph, i * cols + j, i * cols + k);
            }
        }
    }

    // Connect nodes in the same column
    for(int j = 0; j < cols; ++j) {
        for(int i = 0; i < rows; ++i) {
            for(int k = i + 1; k < rows; ++k) {
                add_edge(graph, i * cols + j, k * cols + j);
            }
        }
    }

    // Connect nodes in the same grid
    int grid_size = 3;
    for(int i = 0; i < rows; i += grid_size) {
        for(int j = 0; j < cols; j += grid_size) {
            for(int r1 = i; r1 < i + grid_size; ++r1) {
                for(int c1 = j; c1 < j + grid_size; ++c1) {
                    for(int r2 = i; r2 < i + grid_size; ++r2) {
                        for(int c2 = j; c2 < j + grid_size; ++c2) {
                            if(!(r1 == r2 && c1 == c2)) {
                                add_edge(graph, r1 * cols + c1, r2 * cols + c2);
                            }
                        }
                    }
                }
            }
        }
    }
}

// Function to dynamically allocate memory for the Sudoku board
int** create_sudoku_board() {
    // Allocate memory for the rows (an array of int pointers)
    int** sudoku_board = new int*[9];

    // Allocate memory for each row (an array of ints)
    for(int i = 0; i < 9; ++i) {
        sudoku_board[i] = new int[9];
    }

    // Initialize the board with the given values
    int board[9][9] = {
        {0,0,0, 4,0,0, 0,0,0},
        {4,0,9, 0,0,6, 8,7,0},
        {0,0,0, 9,0,0, 1,0,0},

        {5,0,4, 0,2,0, 0,0,9},
        {0,7,0, 8,0,4, 0,6,0},
        {6,0,0, 0,3,0, 5,0,2},

        {0,0,1, 0,0,7, 0,0,0},
        {0,4,3, 2,0,0, 6,0,5},
        {0,0,0, 0,0,5, 0,0,0}
    };

    // Copy values from the static board to the dynamic board
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            sudoku_board[i][j] = board[i][j];
        }
    }

    return sudoku_board;
}

// Function to convert the Sudoku board to a one-dimensional array of colors
void convert_sudoku_board_to_color(int** sudoku_board, int* color){
    int index = 0;
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            color[index++] = sudoku_board[i][j];
        }
    }
}

// Brief explanation for function to check if assigning a color to a node is valid
/* 
It uses adjacency list of the graph to check the color for neighbouring nodes, we check every neighbour of every node
graph[node][i] will return the neighbouring nodes and color of that node will be given by color[graph[node][i]]
If any neighbour has the same color, return false 
else return true
*/

bool isValid(vector<int>* graph, int node, int color_to_check, int* color){
    // Iterate through neighbors of 'node' in 'graph'
    for(int i=0;i<graph[node].size();i++){
        // Check if any neighbor has the same 'color_to_check'
        if(color[graph[node][i]]==color_to_check) return false;  
    }
    // If yes, return false; otherwise, return true
    return true;
}


// Brief explanation for function to solve the Sudoku puzzle using backtracking
/* Similar approach as graph colouring problem */

void solve_sudoku(vector<int>* graph, int node, int* color){
    // Base case: if all nodes are colored (node == 81), print the solution
    if(node>=81){
        print_sudoku_board(color);
        return;
    }
    // Recursive case: if node is already colored, move to the next node
    if(color[node]){
        solve_sudoku(graph,node+1,color);
        return;
    }
    // For each possible color (1 to 9), check if it's valid to assign to 'node'
    for(int i=1;i<=9;i++){
        if(isValid(graph,node,i,color)){
            // If valid, assign the color, recursively solve the next node, then backtrack
            color[node]=i;
            solve_sudoku(graph,node+1,color);
            color[node]=0;
        }
    }
    return;
}


// Function to print the Sudoku board
void print_sudoku_board(int* color) {
    cout << "+-------+-------+-------+" << endl;
    for (int i = 0; i < 9; ++i) {
        cout << "| ";
        for (int j = 0; j < 9; ++j) {
            if (color[i * 9 + j] != 0) {
                cout << color[i * 9 + j] << " ";
            } else {
                cout << ". ";
            }
            if ((j + 1) % 3 == 0) cout << "| ";
        }
        cout << endl;
        if ((i + 1) % 3 == 0) {
            cout << "+-------+-------+-------+" << endl;
        }
    }
    cout << endl;
}

int main(){
    int total_nodes = 81;
    vector<int> graph[total_nodes];
    make_sudoku_connections(graph);
    int color[81];
    int** sudoku_board = create_sudoku_board();
    convert_sudoku_board_to_color(sudoku_board, color);
    cout << "Challenge..." << endl;
    print_sudoku_board(color);
    // Call solve_sudoku function here to solve the Sudoku puzzle
    solve_sudoku(graph, 0, color);
    return 0;
}
