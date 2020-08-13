#include <stdio.h>
#include <stdlib.h>
#define ROW 5
#define COL 5
#define IDENT 0

// Create a Matrix
int **generateMatrix(int row, int col){
  int **mat;
  mat=(int**)malloc(sizeof(int*)*row);
  if(mat==NULL){
    printf("Insufficient Memory...");
    return 0;
  }
  for(int r=0;r<row;r++){
    mat[r]=(int*)malloc(sizeof(int)*col);
  }
  return mat;
}

// Transform Filter
int transformFilter(int x, int y, int **i, int **j, int **k){
  int limX=x+2;
  int limY=y+2;
  for(int r=0;r<3;r++){
      for(int c=0;c<3;c++){
        i[r][c]=j[x-1][y-1]*k[r][c];
        if(y<limY){
          y++;
        }else{
          y=limY-2;
        }
    }
    if(x<limX){
      x++;
    }else{
      x=limX-2;
    }
  }
  return **i;
}

// Load a Matrix
int loadMatrix(int **x, int row, int col, int ran){
  for(int r=0;r<row;r++){
      for(int c=0;c<col;c++){
        x[r][c]=rand()%ran;
    }
  }
  return **x;
}

// Print a Matrix
void printMatrix(int **x, int row, int col){
  for(int r=0;r<row;r++){
    for(int c=0;c<col;c++){
      printf("\t%d", x[r][c]);
    }
    printf("\n");
  }
}

int main(){
  int **matrix, **kernel, **conv;

  // Create the Matrix
  matrix=generateMatrix(ROW, COL);
  kernel=generateMatrix(3,3);
  conv=generateMatrix(3,3);

  // Load the Matrix
  loadMatrix(matrix, ROW, COL, 15);
  loadMatrix(kernel, 3, 3, 2);

  // Print Matrix
  printf("Matrix\n");
  printMatrix(matrix, ROW, COL);
  printf("\n");

  // Apply the filter on Matrix
  for(int kX=1;kX<(ROW-1);kX++){
    for(int kY=1;kY<(COL-1);kY++){
      int x=kX;
      int y=kY;
      int sum=0;
      if(matrix[kX][kY]==IDENT){
        transformFilter(x,y,conv,matrix,kernel);
        for(int r=0;r<3;r++){
          for(int c=0;c<3;c++){
            sum+=conv[r][c];
          }
          matrix[kX][kY]=sum;
        }
      }
    }
  }

  // Print Kernel
  printf("Kernel\n");
  printMatrix(kernel, 3, 3);
  printf("\n");

  // Print Matrix Convolved
  printf("Matrix Convolved\n");
  printMatrix(matrix, ROW, COL);
  printf("\n");

  free(matrix);
  free(kernel);
  free(conv);
}
