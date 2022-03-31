#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXCHAR 1000

int display(int row, int col, int matrix[row][col]){
  for (int ro = 0; ro < row; ro++){
    for (int co = 0; co < row; co++){
      printf("%d ", matrix[ro][co]);
    }
    printf("\n");
  }
}

int sorted(int ro, int co, int matrix[ro][co]){
  int row = 0;
  for (row = 0; row < ro-1; row++){
    for (int col = 0; col < co; col++){
      for (int last = 0; last < co; last++){
	//printf("test:%d\n",matrix[ro-1][last]);
	if (matrix[row][col] > matrix[ro-1][last]){
	  //printf("test:%d\n",matrix[ro-1][last]);
	  return 0;
	}
      }
    }
  }
  if (row%2 == 0){
    for (int right = 0; right < ro-1; right++){
      if (matrix[ro-1][right] > matrix[ro-1][right+1])
	return 0;
    }
  }
  else{
    for (int left = sizeof(matrix[0])/sizeof(matrix[0][0])-1; left > 0; left--){
      if (matrix[ro-1][left] > matrix[ro-1][left-1])
	return 0;
    }
  }
  return 1;
}

int main(){
  FILE *fp;
  //char str[MAXCHAR];
  char c;
  int i;
  char* filename = "input.txt";

  fp = fopen(filename, "r");
  if (fp == NULL){
    printf("Could not open file %s", filename);
    return 1;
  }
  /**
  while ((c = fgetc(fp)) != EOF){
    //printf("%s", str);
    printf("%c", c);
    if (c == '\n')
      printf("n");
  }
  */
  /**
  while (fgets(str, MAXCHAR, fp) != NULL){
    int num = atoi(str);
    printf("%d", num);
  }
  */
  int rows = 0;
  
  int col = 0;
  int row = 0;
  while (c != '\n'){
    fscanf(fp, "%d", &i);
    if (!feof(fp))
      //printf("%d ", i);
    col++;
    
    c = fgetc(fp);
    if (c == '\n'){
      row++;
      //printf(" <%d,%d>\n", col, row);
      rows = col;
      col = 0;
    }
  }
  fclose(fp);
  fp = fopen(filename, "r");

  int matrix[rows][rows];

  col = 0;
  row = 0;
  while (!feof(fp)){    
    fscanf(fp, "%d", &i);
    if (!feof(fp)){
      //printf("%d ", i);
      matrix[row][col] = i;
    }
    col++;
    
    c = fgetc(fp);
    if (c == '\n'){
      row++;
      //printf(" <%d,%d>\n", col, row);
      col = 0;
    }
  }
  /**
  if (row == rows)
    printf("yes\n");
  else
    printf("no\n");
  */
  fclose(fp);
 
  for (int ro = 0; ro < rows; ro++){
    for (int co = 0; co < rows; co++){
      printf("%d ", matrix[ro][co]);
    }
    printf("\n");
  }

  //double phase = log(rows)/log(2);
  //phase = ceil(phase) + 1;
  
  if (sorted(row, row, matrix))
    printf("Sorted\n");
  else
    printf("\nNot sorted\n\n");
  

  //SORT
  int phase = 1;
  int count = 0;
  while(!sorted(row, row, matrix) && count < 1000x000){
    if (phase){
      for (int r = 0; r < row; r++){
	if (r%2==0){
	  for (int c1 = 0; c1 < row-1; c1++){
	    int min = c1;
	    for (int c2 = c1+1; c2 < row; c2++){
	      if (matrix[r][c2] < matrix[r][min]){
		min = c2;
	      }
	    }
	    int temp = matrix[r][min];
	    matrix[r][min] = matrix[r][c1];
	    matrix[r][c1] = temp;
	  }
	}
	else{
	  for (int c1 = row-1; c1 > 0; c1--){
	    int min = c1;
	    for (int c2 = c1-1; c2 >= 0; c2--){
	      if (matrix[r][c2] < matrix[r][min]){
		min = c2;
	      }
	    }
	    int temp = matrix[r][min];
	    matrix[r][min] = matrix[r][c1];
	    matrix[r][c1] = temp;
	  }
	}
      }
      phase = 0;
    }
    else{
      for (int c = 0; c < row; c++){
	for (int r1 = 0; r1 < row-1; r1++){
	  int min = r1;
	  for (int r2 = r1+1; r2 < row; r2++){
	    if (matrix[r2][c] < matrix[min][c]){
	      min = r2;
	    }
	  }
	  int temp = matrix[min][c];
	  matrix[min][c] = matrix[r1][c];
	  matrix[r1][c] = temp;
	}
      }
      phase = 1;
    }
    count++;
    display(row, row, matrix);
    printf("\n");
  }

  if (sorted(row, row, matrix))
    printf("Sorted\n");
  else
    printf("Not sorted\n");
  
  return 0;
}
