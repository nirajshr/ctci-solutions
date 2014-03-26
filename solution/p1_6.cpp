#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<char> > Matrix;
typedef vector<char> MRow;
typedef vector<char> MCol;

void populateMatrix(Matrix& matrix, size_t size) {
  char my_char = 'A';
  for(int r=0; r<size; ++r) {
    vector<char> row;
    for(int c=0; c<size; ++c) {
      row.push_back(my_char++);
    }
    matrix.push_back(row);
  }
}

void printMatrix(Matrix const& matrix, size_t size) {
  for(int r=0; r<size; ++r) {
    for(int c=0; c<size; ++c) {
      cout << matrix[r][c] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void insertRow(Matrix& matrix, MRow const& row, size_t row_num, size_t start_col) { 
  for(int i=0; i<row.size(); ++i) {
    matrix[row_num][start_col+i] = row[i];
  }
}
void insertCol(Matrix& matrix, MCol const& col, size_t col_num, size_t start_row) {
  for(int i=0; i<col.size(); ++i) {
    matrix[start_row+i][col_num] = col[i];
  }
}

MRow  getRow(Matrix const& matrix, size_t num, size_t start_ind, size_t end_ind) {
  MRow row;
  for(int c=start_ind; c<end_ind; ++c) {
    row.push_back(matrix[num][c]);
  }
  return row;
}

MCol  getCol(Matrix const& matrix, size_t num, size_t start_ind, size_t end_ind) {
  MCol col;
  for(int r=start_ind; r<end_ind; ++r) {
    col.push_back(matrix[r][num]);
  }
  return col;
}

void rotateOuterElementsOld(Matrix& matrix, int start_ind, int end_ind) {
  size_t n = end_ind - start_ind + 1;
  MRow top_row = getRow(matrix, start_ind, start_ind, end_ind);
  MRow bot_row = getRow(matrix, end_ind, start_ind, end_ind);
  MCol lef_col = getCol(matrix, start_ind, start_ind, end_ind);
  MCol rig_col = getCol(matrix, end_ind, start_ind, end_ind);

  MRow& tar_top_row = lef_col;
  MRow& tar_bot_row = rig_col;
  MRow& tar_lef_col = bot_row;
  MRow& tar_rig_col = top_row;

  insertRow(matrix, tar_top_row, start_ind, start_ind);
  insertRow(matrix, tar_bot_row, end_ind, start_ind);
  insertCol(matrix, tar_lef_col, start_ind, start_ind);
  insertCol(matrix, tar_rig_col, end_ind, start_ind);
}

struct MAddress {
  size_t r;
  size_t c;

  MAddress(int row, int col) : r(row), c(col) {}
};

ostream& operator<<(ostream& os, MAddress const& add) {
  os << "(" << add.r << "," << add.c << ")";
  return os;
}

MAddress rotateSquare(int n, int offset, MAddress const& add1) {
  int end_ind = offset + n-1;
  int r1 = add1.r;
  int c1 = add1.c;

  int r2, c2;
  if (r1 == offset && c1 != end_ind) {
    c2 = end_ind;
    r2 = c1;
  }
  else if (c1 == end_ind  && r1 != end_ind) {
    r2 = end_ind;
    c2 = end_ind - r1 + offset;
  }
  else if (r1 == end_ind && c1 != offset) {
    c2 = offset;
    r2 = c1;
  }
  else {
    cerr << "bad bad" << endl;
  }

  return MAddress(r2, c2);
}

void swap(Matrix& matrix, MAddress const& add1, MAddress const& add2) {
  char temp = matrix[add1.r][add1.c];
  matrix[add1.r][add1.c] = matrix[add2.r][add2.c];
  matrix[add2.r][add2.c] = temp;
}

void rotateOuterElements(Matrix& matrix, int start_ind, int end_ind) {
  size_t n = end_ind - start_ind + 1;
  //cout << "Entering:" << start_ind << "-" << end_ind  << endl;
  for (int i=start_ind; i<end_ind; ++i) {
    MAddress point1(start_ind, start_ind + i - start_ind);
    MAddress point2 = rotateSquare(n, start_ind, point1);
    MAddress point3 = rotateSquare(n, start_ind, point2);
    MAddress point4 = rotateSquare(n, start_ind, point3);

    //cout << point1 << "-" << point2 << endl;
    //cout << point4 << "-" << point3 << endl;
    //cout << endl;

    swap(matrix, point1, point2);
    swap(matrix, point3, point4);
    swap(matrix, point1, point3);
  }
}

void rotateMatrixRecur(Matrix& matrix, int start_ind, int end_ind) {
  if (start_ind >= end_ind) return;

  rotateOuterElements(matrix, start_ind, end_ind);
  rotateMatrixRecur(matrix, ++start_ind, --end_ind);
}

void rotateMatrix(Matrix& matrix, size_t size) {
  rotateMatrixRecur(matrix, 0, size-1);
}

int main() {
  Matrix matrix1;
  Matrix matrix2;
  Matrix matrix3;
  Matrix matrix4;
  Matrix matrix5;

  populateMatrix(matrix1, 1);
  populateMatrix(matrix2, 2);
  populateMatrix(matrix3, 3);
  populateMatrix(matrix4, 4);
  populateMatrix(matrix5, 5);

  printMatrix(matrix1, 1);
  printMatrix(matrix2, 2);
  printMatrix(matrix3, 3);
  printMatrix(matrix4, 4);
  printMatrix(matrix5, 5);

  rotateMatrix(matrix1, 1); cout << endl;
  rotateMatrix(matrix2, 2); cout << endl;
  rotateMatrix(matrix3, 3); cout << endl;
  rotateMatrix(matrix4, 4); cout << endl;
  rotateMatrix(matrix5, 5);

  cout << "After rotate:" << endl;

  printMatrix(matrix1, 1);
  printMatrix(matrix2, 2);
  printMatrix(matrix3, 3);
  printMatrix(matrix4, 4);
  printMatrix(matrix5, 5);

  return 0;
}
