#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Position {
  Position() : row(0), col(0) {}
  Position(int row, int col) : row(row), col(col) {}

  int row;
  int col;
};

bool operator==(Position const& pos1, Position const& pos2) {
  return pos1.row == pos2.row && pos1.col == pos2.col;
}

bool operator!=(Position const& pos1, Position const& pos2) {
  return !(pos1 == pos2);
}

ostream& operator<<(ostream& oss, Position const& pos) {
  oss << "(" << pos.row << "," << pos.col << ")";
  return oss;
}

typedef vector<Position> Path;

struct Maze {
  Maze(int num_rows, int num_cols) {

    table.resize(num_rows);
    for (int i=0; i<table.size(); ++i) {
      table[i].resize(num_cols);
    }
  }

  void putObstacles(Path const& path) {
    for (int i=0; i<path.size(); ++i) {
      Position const& pos = path[i];
      if (pos.row >= 0 && pos.row < numRows() &&
          pos.col >= 0 && pos.col < numCols()) {
        table[pos.row][pos.col] = 1;
      }
    }
  }

  bool hasObstacle(Position const& pos) const {
    if (pos.row >= 0 && pos.row < numRows() &&
        pos.col >= 0 && pos.col < numCols()) {
      return table[pos.row][pos.col] == 1;
    }
    return true;
  }
  int numRows() const { return table.size(); }
  int numCols() const { return table[0].size(); }

  vector<vector<int> > table;
};


void printVec(Path const& path) {
  for (int i=0; i<path.size(); ++i) {
    cout << path[i] << " ";
  }

  cout << endl;
}

bool isValidPosition(Maze const& maze, Position const& pos) {
  if (pos.row < 0 || pos.col < 0) return false;
  if (pos.row >= maze.numRows() || pos.col >= maze.numCols()) return false;

  if (maze.hasObstacle(pos)) return false;
  return true;
}

void getNextPossiblePositions(Maze const& maze, Path const& curr_path, Position const& curr_pos, Path& next_positions) {
  //cout << "next pos at " << curr_pos << endl;
  Path possible_path;
  {
    Position new_pos(curr_pos.row - 1, curr_pos.col);
    possible_path.push_back(new_pos);
  }
  {
    Position new_pos(curr_pos.row, curr_pos.col-1);
    possible_path.push_back(new_pos);
  }
  {
    Position new_pos(curr_pos.row, curr_pos.col+1);
    possible_path.push_back(new_pos);
  }
  {
    Position new_pos(curr_pos.row + 1, curr_pos.col);
    possible_path.push_back(new_pos);
  }
  for (int i=0; i<possible_path.size(); ++i) {
    Position const& new_pos = possible_path[i];
    if (curr_pos != new_pos && isValidPosition(maze, new_pos)) {
      if (find(curr_path.begin(), curr_path.end(), new_pos) == curr_path.end()) { //if not already visited
        //cout << "Found Pos " << new_pos << endl;
        next_positions.push_back(new_pos);
      }
    }
  }
}

void findTargetImpl(Maze const& maze, Position const& target, Path& curr_path, vector<Path>& agg_success_paths) {
  int size = curr_path.size();

  if (curr_path[size-1] == target) {
    agg_success_paths.push_back(curr_path);
  }
  else {
    const Position& curr_pos = curr_path[size-1];
    Path next_positions;
    getNextPossiblePositions(maze, curr_path, curr_pos, next_positions);

    for (int i=0; i<next_positions.size(); ++i) {
      Path next_path(curr_path);
      next_path.push_back(next_positions[i]);
      findTargetImpl(maze, target, next_path, agg_success_paths);
    }
  }
}

void findTarget(Maze const& maze, Position const& start, Position const& target) {
  vector<Path> agg_success_paths;
  Path curr_path;
  curr_path.push_back(start);

  findTargetImpl(maze, target, curr_path, agg_success_paths);

  cout << "Possible paths:" << endl;
  for (int i=0; i<agg_success_paths.size(); ++i) {
    printVec(agg_success_paths[i]);
  }
}

void fillObstacles(Path& path) {
  path.push_back(Position (0,1));
  path.push_back(Position (1,1));
  path.push_back(Position (2,1));
  path.push_back(Position (3,1));

  path.push_back(Position (0,2));
  path.push_back(Position (0,3));
  //path.push_back(Position (1,3));

  path.push_back(Position (4,4));
  path.push_back(Position (3,4));
  path.push_back(Position (4,3));
  path.push_back(Position (3,3));
}

int main() {
  Maze maze(5, 5);
  Position start(0,0);
  Position target(2,4);

  Path obstacles;
  fillObstacles(obstacles);
  maze.putObstacles(obstacles);

  findTarget(maze, start, target);

  return 0;
}
