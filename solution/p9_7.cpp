#include <vector>
#include <string>
#include <sstream>
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
    Cell () : color(' '), visited(false) {}

  public:
    char color;

    Position pos;
    bool visited;
};

typedef vector<Cell> Cells;
typedef vector<Cells> Table;

bool isNeighbour(Cell const& cell1, Cell const& cell2) {
  if (cell1.pos.row == cell2.pos.row) {
    if (abs(cell1.pos.col - cell2.pos.col) == 1) return true;
  }
  else if (cell1.pos.col == cell2.pos.col) {
    if(abs(cell1.pos.row - cell2.pos.row) == 1) return true;
  }
  return false;
}

 
//  =   =   =
//|   |   |   |
//  =   =   =
//|   |   |   |
//  =   =   =
//|   |   |   |
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
          cell.color = '*';
        }
      }
    }

    Cell& getCellAtPos(Position const& pos) {
      return table[pos.row][pos.col];
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
      stringstream oss;
      oss << "| " << cell.color << " ";
      line1 += hor_yes;
      line2 += oss.str();
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

void paintFillImpl(Maze& maze, Position const& pos, char color) {
  int row = pos.row;
  int col = pos.col;
  if (row < 0 || col < 0 || row >= maze.numRows || col >= maze.numCols) return;
  Cell& currCell = maze.getCellAtPos(pos);
  if (!currCell.visited && currCell.color == color) {
    currCell.visited = true;
    currCell.color = '$';

    paintFillImpl(maze, Position(row-1, col), color);
    paintFillImpl(maze, Position(row+1, col), color);
    paintFillImpl(maze, Position(row, col-1), color);
    paintFillImpl(maze, Position(row, col+1), color);
  }
}

void paintFill(Maze& maze, Position const& pos) {
  Cell& currCell = maze.getCellAtPos(pos);
  paintFillImpl(maze, pos, currCell.color);
}

int main() {
  srand (time(NULL));
  Maze maze(8, 8);

  maze.getCellAtPos(Position (2,1)).color = ' ';
  maze.getCellAtPos(Position (2,2)).color = ' ';

  maze.getCellAtPos(Position (3,1)).color = ' ';
  maze.getCellAtPos(Position (3,2)).color = ' ';

  maze.getCellAtPos(Position (3,3)).color = ' ';
  maze.getCellAtPos(Position (3,4)).color = ' ';

  maze.getCellAtPos(Position (4,3)).color = ' ';
  maze.getCellAtPos(Position (4,4)).color = ' ';
  maze.getCellAtPos(Position (4,5)).color = ' ';

  maze.getCellAtPos(Position (5,3)).color = ' ';
  maze.getCellAtPos(Position (5,4)).color = ' ';
  maze.getCellAtPos(Position (5,5)).color = ' ';

  cout << maze << endl;
  paintFill(maze, Position(5,5));
  cout << maze << endl;

  return 0;
}
