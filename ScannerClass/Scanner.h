#ifndef SCANNER_H
#define SCANNER_H
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string.h>

class Scanner {
	private:	
		char *baseFileName;
		FILE *filePtr = NULL;
	public:
		Scanner(char *fileName) {
			root = nullptr;
			if(fileName == nullptr){
				baseFileName = "out";
			} else {
				baseFileName = fileName;
			}
			
		}
		~Scanner() {
			if(filePtr != NULL) {
				fclose(filePtr);
			}
		}	


		
};


#endif

