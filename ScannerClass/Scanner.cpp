#include "Scanner.h"
#include <cctype>

// FILE filePtr
// character currChar
// int lineCount
// char *currCharPlace
//
//enum TokenID {
//	IDENT_tk,
//	NUM_tk,
//	KW_tk,
//	OP_tk,
//	DELIM_tk
//};
//
enum CharacterType {
	LETTER = 1,
	DIGIT,
	QUESTIONMARK,
	SLASH,
	STAR,
	OPERATOR,
	DELIM,
	EOFCHAR,
	SPACE
};

const char *tokenNames[]= {"Identifier", "Number", "Keyword", "Operator", "Delimiter"};


Scanner::Scanner(const char *strPtr) {
	for(int i = 0; i <= strlen(strPtr); i++) {   // <= because i want to include the \0 or EOF
		textBuffer[i] = strPtr[i];
	}
	currCharPlace = textBuffer;
}

int Scanner::filter() {
	//currChar = fgetc(filePtr);
	incrementCharPtr();


	if(currChar == '@') {
		do {
			incrementCharPtr();
		} while(currChar != '@');
	}

	if(isalpha(currChar)){
		return LETTER;
	}
	if(isdigit(currChar)){
		return DIGIT;
	}

	switch (currChar) {
		case ' ': return SPACE;
		case '\0': return EOFCHAR;
		case '?': return QUESTIONMARK;
		case '/': return SLASH;
		case '*': return STAR;
		case '(': return DELIM;
		case ')': return DELIM;
		case '{': return DELIM;
		case '}': return DELIM;
		case '[': return DELIM;
		case ']': return DELIM;
		case ';': return DELIM;
		case ':': return OPERATOR;
		case '+': return OPERATOR;
		case '-': return OPERATOR;
		case '=': return OPERATOR;
	}
	return 0; // Stands for invalid char in the table
	
	
}

void Scanner::scanToken() {
	int charGroup;
	char lexeme[8] = "";
	printf("here!!!\n");
	while(charGroup != EOF) {
		charGroup = filter();
		printf("%c: %d\n", currChar, charGroup);
	}
	printf("Total line count: %d\n", lineCount);
	
}


void Scanner::incrementCharPtr() {
	currChar = *currCharPlace++;
}
