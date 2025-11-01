#include "Scanner.h"
#include <cctype>
static Token finalCase(int state, char *lexeme, int lineNum);
static bool checkKeyword(char *lexeme);
static void invalidCase(int state, char currentChar);
static void errorCase(int state, char currentChar);
static void checkIfValidIDTK(char *lexeme);

enum CharacterType {
	LETTER = 1,
	DIGIT,
	QUESTIONMARK,
	SLASH,
	STAR,
	OPERATOR,
	DELIM,
	EOFCHAR,
	SPACE,
	INIT
};

const char *tokenNames[]= {"Identifier", "Number", "Operator", "Delimiter", "EOF", "Keyword"};


Scanner::Scanner(const char *strPtr) {
	int i = 0;
	int len = strlen(strPtr);
	for(; i <= len; i++) {   // <= because i want to include the \0 or EOF
		textBuffer[i] = strPtr[i];
	}	
	lookaheadPlace = textBuffer;
}

int Scanner::filter() {
	//lookahead = fgetc(filePtr);
	incrementCharPtr();


	if(lookahead == '@') {
		do {
			incrementCharPtr();
		} while(lookahead != '@');
	}

	if(isalpha(lookahead)){
		//printf("filter: returning letter\n");
		return LETTER;
	}
	if(isdigit(lookahead)){
		//printf("filter: returning digit\n");
		return DIGIT;
	}

	switch (lookahead) {
		case ' ': 
			//printf("filter: returning space\n");
			return SPACE;
		case '\n':
			//printf("filter: got newline returning space\n\n\n\n\n");
			return SPACE;
		case '\t':
			return SPACE;
		case '\0':
			//printf("filter: returning EOFCHAR got backslash 0\n"); 
			return EOFCHAR;
		case EOF: 
			//printf("filter: returning EOFCHAR got EOF\n");
			return EOFCHAR;
		case '?': 
			//printf("filter: returning ?\n");
			return QUESTIONMARK;
		case '/': 
			//printf("filter: returning /\n");
			return SLASH;
		case '*': 
			//printf("filter: returning *\n");
			return STAR;
		case '(': 
			//printf("filter: returning (\n");
			return DELIM;
		case ')': 
			//printf("filter: returning )\n");
			return DELIM;
		case '{': 
			//printf("filter: returning {\n");
			return DELIM;
		case '}': 
			//printf("filter: returning }\n");
			return DELIM;
		case '[': 
			//printf("filter: returning [\n"); 
			return DELIM;
		case ']': 
			//printf("filter: returning ]\n");
			return DELIM;
		case ';': 
			//printf("filter: returning ;\n");
			return DELIM;
		case ':': 
			//printf("filter: returning :\n");
			return OPERATOR;
		case '+': 
			//printf("filter: returning +\n");
			return OPERATOR;
		case '-': 
			//printf("filter: returning -\n");
			return OPERATOR;
		case '=': 
			//printf("filter: returning =\n");
			return OPERATOR;
	}

	return 0; // Stands for invalid char in the table
	
	
}

Token Scanner::scanToken() {
	char lexeme[9] = "";
	int state = 0;
	int lexemeIndex = 0;
	bool isFirstCharScanned = false;
	bool useLookahead = false;
	bool lineCountToBeIncremented = false;
	if(charGroup != -1) {
		useLookahead = true;
	}

	do {
		// logic to handle the fact that we always get an extra character when checking if the state is final so we use the last char group we got from the last token for the JUST the first character
		if (!useLookahead) {
			charGroup = filter();
		}
		useLookahead = false;

		// Get the state from the Finite Automata Table
		state = FATable[state][charGroup];

		// From the enums
		if(state >= -1000 && state < -997) {
			errorCase(state, lookahead);
			exit(1);
		}
		else if (state >= -2000 && state < -1996) {
			invalidCase(state, lookahead);
			exit(1);
		} 
		else if (state >= 1000 && state < 1005) {
			lexeme[lexemeIndex] = '\0';
			if(lineCountToBeIncremented) { // to increment line count AFTER the last token in the old line
				lineCount++;
			}
			Token tk = finalCase(state, lexeme, lineCount);
			return tk;
		}
		else if (state >= 0 && state < 13) {
			if (lexemeIndex == 8) {
				printf("Error too many characters there should be nothing more than 8 characters in a token\n");
				exit(1);
			}
			if (lookahead != ' ' && lookahead != '\n' && lookahead != '\t') { // To prevent spaces going into lexemes
				lexeme[lexemeIndex++] = lookahead;
			}
			if (lookahead == '\n') {
				lineCountToBeIncremented = true;
			}
			continue;
		}

	} while(charGroup != EOFCHAR);
	printf("Total line count: %d\n", lineCount);
	Token t;
	t.lineNum = lineCount;
	t.tokenID = EOFTK;
	return t;
	
}

/*
 *struct token {
	TokenID tokenID;
	char *lexeme;
	int lineNum;
};
*/
void Scanner::incrementCharPtr() {
	if(*lookaheadPlace == '\0') {
		printf("*lookaheadPlace is backslash 0\n");
		lookahead = '\0';
		return;
	}
	lookahead = *lookaheadPlace++;
}

static Token finalCase(int state, char *lexeme, int lineNumber) {
	Token token;
	token.lineNum = lineNumber;
	strcpy(token.lexeme, lexeme);
	switch (state) {
		case IDTK:
			if(checkKeyword(lexeme) == true) {
				token.tokenID = KEYWORD;
			} else {
				checkIfValidIDTK(lexeme);
				token.tokenID = IDTK;
			}
			return token;
		case NUMTK:
			token.tokenID = NUMTK;
			return token;
		case OPTK:
			token.tokenID = OPTK;
			return token;
		case DELIMTK:
			token.tokenID = DELIMTK;
			return token;
		case EOFTK:
			token.tokenID = EOFTK;
			return token;
	}
	token.tokenID = EOFTK;
	return token;
}


static void checkIfValidIDTK(char *lexeme){
	if(lexeme[0] != 'x') {
		printf("Error: All ID tokens must start with the letter x got: %c\n", lexeme[0]);
		exit(1);
	}
}


static bool checkKeyword(char *lexeme) {
	const char *keywords[] = {"go", "op", "loop", "int", "exit", "scan", "output", "cond", "then", "set", "func", "program"};
	int arrayLen = sizeof(keywords) / sizeof(keywords[0]);
	for (int i = 0; i < arrayLen; i++) {
		if(strcmp(lexeme, keywords[i]) == 0) {
			return true;
		}
	}
	return false;
}

static void invalidCase(int state, char currentChar) {
	switch (state) {
		case INVALID:
			printf("Invalid char found %c\n", currentChar);
			break;
		case INVDLETTER:
			printf("Invalid char %c found on line %d expected letter\n", currentChar, 0);
			break;
		case INVDSLASH:
			printf("Invalid char %c found on line %d expected /\n", currentChar , 0);
			break;
		case INVDSTAR:
			printf("Invalid char %c found on line %d expected *\n", currentChar ,0);
			break;
		default:
			printf("invalid char %c found on line %d default case\n", currentChar, 0);
	}
}

static void errorCase(int state, char currentChar) {
	switch(state) {
		case EXPLETTER:
			printf("Error expected letter on line: %d got %c\n", 0, currentChar);
			break;
		case EXPSLASH:
			printf("Error: expected / on line: %d got %c\n", 0, currentChar);
			break;
		case EXPSTAR:
			printf("Error: expected * on line: %d got %c\n", 0, currentChar);
			break;
		default:
			printf("default case error char on line %d got %c\n", 0, currentChar);
	}

	return;
	
}
