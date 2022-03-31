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
  int fd1;
  int fd2;
  printf("File 1 name: ");
  char str1[256];
  fgets(str1, sizeof(str1), stdin);
  fd1 = open(str1, O_RDWR);
  printf("File 2 name: ");
  char str2[256];
  fgets(str2, sizeof(str2), stdin);
  fd2 = open(str2, O_RDWR);

  //define file attributes
  char buf1[4098];
  char buf2[4098];
  size_t nbytes_r;
  size_t nbytes_w;
  ssize_t bytes_read;
  ssize_t bytes_written;

  nbytes_r = sizeof(buf1);
  bytes_read = read(fd1, buf1, nbytes_r);

  //copy and capitalize all characters
  for (int i = 0; buf1[i] != '\0'; i++){    
    if (buf1[i] >= 'a' && buf1[i] <= 'z'){
      buf2[i] = buf1[i] - 32;
    }
    else{
      buf2[i] = buf1[i];
    }
  }
  
  nbytes_w = strlen(buf2);
  bytes_written = write(fd2, buf2, nbytes_w);

  close(fd1);
  close(fd2);

  time_t end = time(0);
  int time = end - start;
  printf("RunTime: %d \n", time);
}
