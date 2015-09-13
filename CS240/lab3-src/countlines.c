
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
	int c;
	int lines=0;

 	// Add your implementation here
         printf("Program that counts lines.\n");
         char * fName = argv[1];
         FILE * fd = fopen(fName, "r");
	 if(fd == NULL){
	 printf("Could not open file %s\n",fName);
	 exit(1);
	 }
	 
	 while((c=fgetc(fd))!= -1)
	 {
	 if(c=='\n')
	 {
	 lines++;
	 }
	 }
	printf("Total lines: %d\n",lines);
	fclose(fd);
}
