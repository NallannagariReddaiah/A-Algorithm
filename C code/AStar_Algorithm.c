#include<stdio.h>
#include<stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
typedef struct {
	int parent_i, parent_j;
	double f, g, h;
} cell;

typedef struct {
	int first, second;
} Pair;

bool isValid(int ROW,int COL,int row, int col) {
	return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

bool isUnBlocked(int ROW,int COL,int grid[][COL], int row, int col) {
	return (grid[row][col] == 1);
}

bool isDestination(int row, int col, Pair dest) {
	return (row == dest.first && col == dest.second);
}

double calculateHValue(int row, int col, Pair dest) {
	return sqrt((row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second));
}

void tracePath(int ROW,int COL,cell cellDetails[][COL], Pair dest) {
	printf("\nThe Path is ");
	int row = dest.first;
	int col = dest.second;

	while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
		printf("-> (%d,%d) ", row, col);
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	printf("-> (%d,%d) ", row, col);
}

void aStarSearch(int ROW,int COL,int grid[][COL], Pair src, Pair dest) {
	if (!isValid(ROW,COL,src.first, src.second)) {
		printf("Source is invalid\n");
		return;
	}
	if (!isValid(ROW,COL,dest.first, dest.second)) {
		printf("destination is invalid\n");
		return;
	}

	if (!isUnBlocked(ROW,COL,grid, src.first, src.second) || !isUnBlocked(ROW,COL,grid, dest.first, dest.second)) {
		printf("Source or destination is blocked\n");
		return;
	}

	if (isDestination(src.first, src.second, dest)) {
		printf("We are already at the destination\n");
		return;
	}

	bool closedList[ROW][COL];
	cell cellDetails[ROW][COL];

	int i, j;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			cellDetails[i][j].f = DBL_MAX;
			cellDetails[i][j].g = DBL_MAX;
			cellDetails[i][j].h = DBL_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
			closedList[i][j] = false;
		}
	}

	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	bool foundDest = false;

	while (true) {
		double min_f = DBL_MAX;
		int min_i = -1, min_j = -1;

		for (i = 0; i < ROW; i++) {
			for (j = 0; j < COL; j++) {
				if (cellDetails[i][j].f < min_f && !closedList[i][j]) {
					min_f = cellDetails[i][j].f;
					min_i = i;
					min_j = j;
				}
			}
		}

		if (min_i == -1 || min_j == -1) {
			break;
		}

		i = min_i, j = min_j;
		closedList[i][j] = true;

		if (isDestination(i, j, dest)) {
			printf("The destination cell is found\n");
			tracePath(ROW,COL,cellDetails, dest);
			foundDest = true;
			break;
		}

		double gNew, hNew, fNew;

		if (isValid(ROW,COL,i - 1, j) && isUnBlocked(ROW,COL,grid, i - 1, j)) {
			gNew = cellDetails[i][j].g + 1.0;
			hNew = calculateHValue(i - 1, j, dest);
			fNew = gNew + hNew;

			if (cellDetails[i - 1][j].f == DBL_MAX || cellDetails[i - 1][j].f > fNew) {
				cellDetails[i - 1][j].f = fNew;
				cellDetails[i - 1][j].g = gNew;
				cellDetails[i - 1][j].h = hNew;
				cellDetails[i - 1][j].parent_i = i;
				cellDetails[i - 1][j].parent_j = j;
			}
		}

		if (isValid(ROW,COL,i + 1, j) && isUnBlocked(ROW,COL,grid, i + 1, j)) {
			gNew = cellDetails[i][j].g + 1.0;
			hNew = calculateHValue(i + 1, j, dest);
			fNew = gNew + hNew;

			if (cellDetails[i + 1][j].f == DBL_MAX || cellDetails[i + 1][j].f > fNew) {
				cellDetails[i + 1][j].f = fNew;
				cellDetails[i + 1][j].g = gNew;
				cellDetails[i + 1][j].h = hNew;
				cellDetails[i + 1][j].parent_i = i;
				cellDetails[i + 1][j].parent_j = j;
			}
		}

		if (isValid(ROW,COL,i, j + 1) && isUnBlocked(ROW,COL,grid, i, j + 1)) {
			gNew = cellDetails[i][j].g + 1.0;
			hNew = calculateHValue(i, j + 1, dest);
			fNew = gNew + hNew;

			if (cellDetails[i][j + 1].f == DBL_MAX || cellDetails[i][j + 1].f > fNew) {
				cellDetails[i][j + 1].f = fNew;
				cellDetails[i][j + 1].g = gNew;
				cellDetails[i][j + 1].h = hNew;
				cellDetails[i][j + 1].parent_i = i;
				cellDetails[i][j + 1].parent_j = j;
			}
		}

		if (isValid(ROW,COL,i, j - 1) && isUnBlocked(ROW,COL,grid, i, j - 1)) {
			gNew = cellDetails[i][j].g + 1.0;
			hNew = calculateHValue(i, j - 1, dest);
			fNew = gNew + hNew;

			if (cellDetails[i][j - 1].f == DBL_MAX || cellDetails[i][j - 1].f > fNew) {
				cellDetails[i][j - 1].f = fNew;
				cellDetails[i][j - 1].g = gNew;
				cellDetails[i][j - 1].h = hNew;
				cellDetails[i][j - 1].parent_i = i;
				cellDetails[i][j - 1].parent_j = j;
			}
		}
	}

	if (!foundDest) {
		printf("Failed to find the destination cell\n");
	}
}

int main() {
    int ROW,COL,p,i,j,ritr=0,citr,src_row,src_col,dest_row,dest_col;
    FILE *fp;
    char file_name[30];
    printf("Enter the txt file name:");
    scanf("%s",file_name);
    fp=fopen(file_name,"r");
    ROW=9;
    COL=10;
    int grid[ROW][COL];
    int input_pos=0;
    char myString[100];
    char num[10];
  while(fgets(myString, 100,fp)) {
      if(input_pos==0){
          p=0;
          for(i=0;i<myString[i]!='\0';i++){
              if(myString[i]==','){
                  num[p]='\0';
                  ROW=atoi(num);
                  p=0;
              }
              else
              {
                  num[p++]=myString[i];
              }
          }
          COL=atoi(num);
          input_pos+=1;
      }
      else if(input_pos==1){
          citr=0;
          for(i=0;i<myString[i]!='\0';i++){
              if(myString[i]=='0'){
                  grid[ritr][citr]=0;
                  citr+=1;
              }
              else if(myString[i]=='1'){
                  grid[ritr][citr]=1;
                   citr+=1;
              }
          }
        //   printf("%d\n",ritr);
          ritr+=1;
          if(ritr>=ROW){
              input_pos+=1;
          }
      }
       else if(input_pos==2){
          p=0;
          for(i=0;i<myString[i]!='\0';i++){
              if(myString[i]==','){
                  num[p]='\0';
                  src_row=atoi(num);
                  p=0;
              }
              else
              {
                  num[p++]=myString[i];
              }
          }
          src_col=atoi(num);
          input_pos+=1;
      }
       else if(input_pos==3){
          p=0;
          for(i=0;i<myString[i]!='\0';i++){
              if(myString[i]==','){
                  num[p]='\0';
                  dest_row=atoi(num);
                  p=0;
              }
              else
              {
                  num[p++]=myString[i];
              }
          }
          dest_col=atoi(num);
          input_pos+=1;
      }
  }
	Pair src = {src_row,src_col};
	Pair dest = {dest_row,dest_col};
	aStarSearch(ROW,COL,grid,src,dest);
	return 0;
}
