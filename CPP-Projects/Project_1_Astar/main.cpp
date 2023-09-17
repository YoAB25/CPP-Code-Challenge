#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::abs;
using std::endl;
using std::sort;

enum class State {kStart, kFinish, kEmpty, kObstacle, kClosed, kPath};

// directional deltas, up,left,down,right
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};


vector<State> ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    vector<State> row;
    while (sline >> n >> c && c == ',') {
      if (n == 0) {
        row.push_back(State::kEmpty);
      } else {
        row.push_back(State::kObstacle);
      }
    }
    return row;
}


vector<vector<State>> ReadBoardFile(string path) {
  ifstream myfile (path);
  vector<vector<State>> board{};
  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}

// TODO: Write function to compare the f-value of two nodes here
//It should return a boolean true if the f-value of the first argument is greater than the f-value of the second,
bool Compare(vector<int> node1, vector<int> node2){
    int f1 = node1[2] + node1[3];
    int f2 = node2[2] + node2[3];
    if (f1 > f2){
        return true;
    } else {
        return false;
    }
}

/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(vector<vector<int>> *v) {
  sort(v->begin(), v->end(), Compare);
}


int Heuristic(int x1, int y1, int x2, int y2){
    return abs(x2-x1)+abs(y2-y1);
}

// TODO: Write CheckValidCell here. Check that the
// cell is on the grid and not an obstacle (i.e. equals kEmpty).
bool CheckValidCell(int x, int y, vector<vector<State>> &grid) {
    bool on_grid_x = (x >= 0 && x < grid.size());
    bool on_grid_y = (y >= 0 && y < grid[0].size());
    if (on_grid_x && on_grid_y)
        return grid[x][y] == State::kEmpty;
    return false;
}


void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &open_nodes, vector<vector<State>> &grid){
    vector<int> node{x,y,g,h};
    open_nodes.push_back(node);
    grid[x][y] = State::kClosed;
}

void ExpandNeighbors(vector<int> curr_node, int goal[2], vector<vector<int>> &open_vector, vector<vector<State>> &grid){
    int currX = curr_node[0];
    int currY = curr_node[1];
    int currg = curr_node[2];
    int currh = curr_node[3];
    for (int i=0; i<4; i++){
        int potX = currX + delta[i][0];
        int potY = currY + delta[i][1];
        if (CheckValidCell(potX,potY,grid)){
            int nextH = Heuristic(potX, potY, goal[0], goal[1]);
            int nextG = currg + 1;
            AddToOpen(potX,potY,nextG,nextH,open_vector,grid);
        }
    }
}

vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2]) {
  // Create the vector of open nodes.
  vector<vector<int>> open {};

  // Initialize the starting node.
  int x = init[0];
  int y = init[1];
  int g = 0;
  int h = Heuristic(x, y, goal[0],goal[1]);
  AddToOpen(x, y, g, h, open, grid);


  while (open.size() > 0) {
    // Get the next node
    CellSort(&open);
    auto current = open.back();
    open.pop_back();
    x = current[0];
    y = current[1];
    grid[x][y] = State::kPath;

    // Check if we're done.
    if (x == goal[0] && y == goal[1]) {
      // TODO: Set the init grid cell to kStart, and
      // set the goal grid cell to kFinish before returning the grid.
      grid[init[0]][init[1]] = State::kStart;
      grid[goal[0]][goal[1]] = State::kFinish;

      return grid;
    }

    // If we're not done, expand search to current node's neighbors.
    ExpandNeighbors(current, goal, open, grid);
  }

  // We've run out of new nodes to explore and haven't found a path.
  cout << "No path found!" << "\n";
  return std::vector<vector<State>>{};
}


string CellString(State cell) {
  switch(cell) {
    case State::kObstacle: return "⛰️   ";
    case State::kStart: return "🚦   ";
    case State::kFinish: return "🏁   ";
    case State::kPath: return "🚗   ";
    case State::kEmpty: return "E   ";
    case State::kClosed: return "C   ";
    default: return "0   ";
  }
}


void PrintBoard(const vector<vector<State>> board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << CellString(board[i][j]);
    }
    cout << "\n";
  }
}

#include "test.cpp"

int main() {
    int init[2]{0,0};
    int goal[2]{4,5};
    vector<vector<State>> board = ReadBoardFile("1.board");
    auto solution = Search(board, init, goal);
    PrintBoard(solution);
    TestHeuristic();
    TestAddToOpen();
    TestCompare();
    TestSearch();
    TestCheckValidCell();
    TestExpandNeighbors();
}





