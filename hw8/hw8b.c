#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]){
  time_t start = time(0);

  //Get input
  FILE *fp1;
  printf("File 1 name: ");
  char str1[256];
  fgets(str1, sizeof(str1), stdin);
  fp1 = fopen(str1, "r");
  FILE *fp2;
  printf("File 2 name: ");
  char str2[256];
  fgets(str2, sizeof(str2), stdin);
  fp2 = fopen(str2, "w");  

  char buf[4096];

  int i = 0;
  char c;
  while ((c = fgetc(fp1)) != EOF){
    if (c >= 'a' && c <= 'z'){
      buf[i] = c - 32;
    }
    else{
      buf[i] = c;
    }
    i++;
  }

  fwrite(buf, strlen(buf), 1, fp2);
  
  fclose(fp1);
  fclose(fp2);

  time_t end = time(0);
  int time = end - start;
  printf("RunTime: %d \n", time);
}
