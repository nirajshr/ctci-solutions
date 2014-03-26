#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <time.h>

#include <stdlib.h>

using namespace std;


struct Position {
  Position () : row(0), col(0) {}
  Position (int row, int col) : row(row), col(col) {}
  int row;
  int col;
};

ostream& operator<<(ostream& oss, Position const& pos) {
  oss << "(" << pos.row << "," << pos.col << ")";
  return oss;
}

struct Cell {
  public:
    enum Wall { ON, OFF, BORDER };

    Cell () : wallUp(ON), wallRt(ON), wallDn(ON), wallLf(ON), visited(false) {}

  public:
    Wall wallUp;
    Wall wallRt;
    Wall wallDn;
    Wall wallLf;

    Position pos;
    bool visited;
};

typedef vector<Cell> Cells;
typedef vector<Cells> Table;

enum NeighbourType { NO, ROW, COL };

NeighbourType isNeighbour(Cell const& cell1, Cell const& cell2) {
  if (cell1.pos.row == cell2.pos.row) {
    if (abs(cell1.pos.col - cell2.pos.col) == 1) return ROW;
  }
  else if (cell1.pos.col == cell2.pos.col) {
    if(abs(cell1.pos.row - cell2.pos.row) == 1) return COL;
  }
  return NO;
}

 
//  =   =   =
//|   |   |   |
//  =   =   =
//|   |   |   |
//  =   =   =
//|   |   |   |
//  =   =   =

//  =   =   =
//|   |       |
//
//|   |   |   |
//
//|       |   |
//  =   =   =
class Maze {
  public:
    Maze(int rows, int cols) : numRows(rows), numCols(cols) {
      table.resize(rows);
      for (int i=0; i<rows; ++i) {
        table[i].resize(cols);
      }


      //init
      for (int i=0; i<numRows; ++i) {
        string line1, line2;
        for (int j=0; j<numCols; ++j) {
          Cell& cell = table[i][j];
          cell.pos.row = i;
          cell.pos.col = j;
        }
      }
    }

    Cell& getCellAtPos(Position const& pos) {
      return table[pos.row][pos.col];
    }

    void dropWallAtPos(Position const& pos1, Position const& pos2) {
      dropWall(table[pos1.row][pos1.col], table[pos2.row][pos2.col]); 
    }

    vector<Position> getNeighbours(Position const& pos) {
      Cell const& cell = getCellAtPos(pos);
      int row = pos.row;
      int col = pos.col;
      vector<Position> neighbours;

      if (row >= 0 && row < numRows && col >= 0 && col < numCols) {
        int c_row, c_col;
        if (row > 0)          { 
          c_row=row-1; c_col=col; 
          Position pos(c_row, c_col); if (!getCellAtPos(pos).visited) { neighbours.push_back(pos); }
        }
        if (row < numRows-1)  { 
          c_row=row+1; c_col=col; 
          Position pos(c_row, c_col); if (!getCellAtPos(pos).visited) { neighbours.push_back(pos); }
        }

        if (col > 0)          { 
          c_row=row; c_col=col-1; 
          Position pos(c_row, c_col); if (!getCellAtPos(pos).visited) { neighbours.push_back(pos); }
        }

        if (col < numCols-1)  { 
          c_row=row; c_col=col+1; 
          Position pos(c_row, c_col); if (!getCellAtPos(pos).visited) { neighbours.push_back(pos); }
        }
      }

      return neighbours;
    }

    static void dropWall(Cell& cell1, Cell& cell2) {
      NeighbourType type = isNeighbour(cell1, cell2);
      cout << "type: " << type << endl;
      cout << "Dropping wall between " << cell1.pos << " and " << cell2.pos << endl;
      if (type == ROW) {
        if (cell1.pos.col < cell2.pos.col) {
          cell1.wallRt = Cell::OFF;
          cell2.wallLf = Cell::OFF;
        }
        else {
          cell2.wallRt = Cell::OFF;
          cell1.wallLf = Cell::OFF;
        }
      }
      else if (type == COL) {
        if (cell1.pos.row < cell2.pos.row) {
          cell1.wallDn = Cell::OFF;
          cell2.wallUp = Cell::OFF;
        }
        else {
          cell2.wallDn = Cell::OFF;
          cell1.wallUp = Cell::OFF;
        }
      }
      else {
        cout << "not a neighbour" << endl;
      }
    }


  public:
    int numRows;
    int numCols;
    Table table;
};

const char* hor_yes = "  = ";
const char* hor_no  = "    ";
const char* ver_yes = "|   ";
const char* ver_no  = "    ";

ostream& operator<< (ostream& oss, Maze const& maze) {
  for (int i=0; i<maze.numRows; ++i) {
    string line1, line2;
    for (int j=0; j<maze.numCols; ++j) {
      const Cell& cell = maze.table[i][j];

      line1 += cell.wallUp == Cell::ON ? hor_yes : hor_no;
      line2 += cell.wallLf == Cell::ON ? ver_yes : ver_no;
    }

    // print right border
    line2 += ver_yes; 
    cout << line1 << endl << line2 << endl;

  }
  // print bottom floor border
  if (maze.numRows > 0) {
    string line1;
    for (int j=0; j<maze.numCols; ++j) {
      line1 += hor_yes;
    }
    cout << line1 << endl;
  }

  return oss;
}

typedef stack<Position> CellStack;
void breakWallDPS2(Maze& maze, Position const& start_pos) {

  CellStack pos_stack;
  int total_cells = maze.numRows * maze.numCols;
  Position curr_pos = start_pos;
  int visited_cells = 1;

  while (visited_cells < total_cells) {
    vector<Position> neighbour = maze.getNeighbours(curr_pos);
    if (neighbour.size() > 0) {
      cout << "Current cell " << curr_pos << endl;
      Position& next_pos = neighbour[rand() % neighbour.size()];
      cout << "Picking neighbour " << curr_pos << endl;
      maze.dropWallAtPos(curr_pos, next_pos); 

      Cell& curr_cell = maze.getCellAtPos(curr_pos);
      Cell& next_cell = maze.getCellAtPos(next_pos);
      curr_cell.visited = true;
      next_cell.visited = true;

      pos_stack.push(curr_pos);

      curr_pos = next_pos;
      visited_cells++;
    }
    else {
      if (!pos_stack.empty()) {
        Position pos = pos_stack.top();
        curr_pos = pos;
        cout << "popping stack " << pos << endl;
        pos_stack.pop();
      }
    }
  }
}
void breakWallDPS(Maze& maze, Position const& pos) {
  Cell& currCell = maze.getCellAtPos(pos);
  if (currCell.visited) return;

  currCell.visited = true;
  vector<Position> neighbours = maze.getNeighbours(currCell.pos);
  cout << "neighbors size:" << neighbours.size() << endl;

  if (neighbours.size() > 0) {
    for (int i=0; i<neighbours.size(); ++i) {
      if (maze.getCellAtPos(neighbours[i]).visited == false) {
        maze.dropWallAtPos(currCell.pos, neighbours[i]);
        breakWallDPS(maze, neighbours[i]);
        break;
      }
      else {
        cout << "Already visited " <<  neighbours[i] << endl;
      }
    }
  }
}

void breakRandomWalls(Maze& maze) {
  //maze.dropWallAtPos(Position(6,6), Position(5,6));
  //maze.dropWallAtPos(Position(5,6), Position(4,6));

  breakWallDPS2(maze, Position(4, 4));
}

int main() {
  srand (time(NULL));
  Maze maze(8, 8);

  cout << maze << endl;
  breakRandomWalls(maze);
  cout << maze << endl;

  return 0;
}
