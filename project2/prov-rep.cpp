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
#include <time.h>

//Function to wait for x amount of seconds
void waitFor(unsigned int secs){
  unsigned int retTime = time(0) + secs;
  while(time(0) < retTime);  
}

int main(int argc, char* argv[]){
  
  //open the file
  int fd = open("res.txt", O_RDWR);

  //get file attributes
  struct stat sb;
  fstat(fd, &sb);
  int fsize = sb.st_size;
  unsigned char *vec;
  const size_t ps = sysconf(_SC_PAGESIZE);

  //memory map the file
  char *filedata = static_cast<char*>(mmap(NULL, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

  //create child process
  int pid;
  pid = fork();  

  int key = 1;
  //main loop
  while (key){
    if (pid == 0){//parent process
      //Get input
      printf("Provide more resources(y/n)? ");
      char str[256];
      fgets(str, sizeof(str), stdin);
      char in = str[0];
      
      //provide resource
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
	    if (c+all-'0' <= '9')
	      filedata[i] = c+all-'0';	      
	  }
	  clast2 = clast;
	  clast = c;
	}
	//sync data
	msync(filedata, fsize, MS_SYNC);
      }
      else{
	key = 0;
      }
    }
    else{//child process
      printf("\nReport:\n");
      printf("Page Size: %d\n", getpagesize());
      printf("%s\n", filedata);
      vec = static_cast<unsigned char*>(calloc(1, (fsize+ps-1)/ps));
      if (!mincore(filedata, fsize, vec))
	printf("Status of pages in main memory: Page 0: Resident\n");
      else
	printf("mincore() call failed\n");
      waitFor(10);
    }
  }
  
  //sync data
  munmap(filedata, fsize);
  close(fd);
}
