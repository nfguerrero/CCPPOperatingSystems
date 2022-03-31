#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int main(int argc, char* argv[]){
  
  //open the file
  int fd = open("res.txt", O_RDWR);

  //get file attributes
  struct stat sb;
  fstat(fd, &sb);
  int fsize = sb.st_size;

  //memory map the file
  char *filedata = static_cast<char*>(mmap(NULL, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
  
  int key = 1;
  
  //main loop
  while (key){
    //Get input
    printf("Allocate more resources(y/n)? ");
    char str[256];
    fgets(str, sizeof(str), stdin);
    char in = str[0];

    //Allocate resource
    if (in == 'y'){
      //get resource and allocation input
      printf("Enter the resource number and number of resources needed: ");
      char str2[256];
      fgets(str2, sizeof(str2), stdin);
      char rec = str2[0];
      char all = str2[2];

      char c;
      char clast;
      char clast2;

      //Change string for mmap
      for (int i = 0; i < strlen(filedata); i++){
	c = filedata[i];	
	if (rec == clast2 && filedata[i+1] != 9){
	  if ((c-'0')-(all-'0') >= 0)
	    filedata[i] = (c-'0')-(all-'0')+'0';	      
	}
	clast2 = clast;
	clast = c;
      }
      msync(filedata, fsize, MS_SYNC);
    }
    else{
      key = 0;
    }
  }
  
  //sync data
  munmap(filedata, fsize);
  close(fd);
}
