#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <cstdint>
#include <cstddef>

using namespace std;

static uint64_t genFunc(uint64_t fileDisc){
	uint64_t buffSize = 32768;
	char buff[buffSize];
	ssize_t numRead;

	//assures that read does not through an error
	while((numRead = read(fileDisc, buff, sizeof buff)) > 0){
	  ssize_t writTotal = 0;
		//writTotal checks to make sure the total bytes printed does not exceed bytes read
	   //writTotal also insures in write that we never go over our buffer
		while(writTotal < numRead){
		     ssize_t newWrit = write(STDOUT_FILENO, buff + writTotal, numRead - writTotal);
             if(newWrit < 1)
             	return -1;
		     writTotal += newWrit;		
		 }
	}
	close(fileDisc);
	//assures checks 
	return numRead == 0 ? 0 : -1;
}


int main(int argc, char **argv)
{
	//checks if there are no args
	if(argc == 1){
		genFunc(STDOUT_FILENO);
	}
	else{
		//main loop for args, iterates through and checks for "-"
		//if hyphen then it sends signal to read from stdin
		//if no hyphen then retrieves file descriptor and sends to genFunc
		for(size_t i = 1; i< argc; i++){
    		if(strcmp("-", argv[i]) == 0){
    			genFunc(STDOUT_FILENO);
    		}
    		else{
    			uint64_t fileDisc = open(argv[i], O_RDONLY);
    			genFunc(fileDisc);	
    		}
    	}
	}
    return 0;
}

