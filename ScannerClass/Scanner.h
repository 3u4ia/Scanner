#ifndef SCANNER_H
#define SCANNER_H
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string.h>


enum TokenID {
	IDENT_tk,
	NUM_tk,
	KW_tk,
	OP_tk,
	DELIM_tk
};


struct token {
	TokenID tokenID;
	char *lexeme;
	int lineNum;
};


extern const char *tokenNames[];

enum States {
	S1,
	S2,
	S3,
	S4,
	S5,
	S6,		
	S7,
	S8,
	S9,
	S10,
	S11,
	S12,
	S13
};

enum Errors {
	EXPLETTER = -1000,
	EXPSLASH,
	EXPSTAR,
	UNKNOWNCHAR
};

enum FINALS {
	IDTK = 1000,
	NUMTK,
	OPTK,
	DELIMTK,
	EOFTK
};

enum INVALIDS {
	INVALID = -2000,
	INVDLETTER,
	INVDSLASH,
	INVDSTAR,
	
}


class Scanner {
	private:
		char currChar;
		int lineCount = 0;
		char textBuffer[1024];
		char *currCharPlace;
		static const int NUMOFSTATES = 13;
		static const int NUMOFCOLUMNS = 10;


		
		void incrementCharPtr();
		
// right now the invalid column for eof is still eof may cause probs i feel it will actually fix them
		const int FATable[NUMOFSTATES][NUMOFCOLUMNS] = {
			{INVALID, S2, S3, S4, S7, S9, S11, S12, S13, S1},
			{INVALID, S2, S2, IDTK, IDTK, IDTK, IDTK, IDTK, IDTK, IDTK},
			{INVALID, NUMTK, S3, NUMTK, NUMTK, NUMTK, NUMTK, NUMTK, NUMTK, NUMTK},
			{S5, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER},
			{S6, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER},
			{INVALID, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK},
			{EXPSLASH, EXPSLASH, EXPSLASH, S8, EXPSLASH, EXPSLASH, EXPSLASH, EXPSLASH, EXPSLASH},
			{INVALID, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK},
			{EXPSTAR, EXPSTAR, EXPSTAR, EXPSTAR, S10, EXPSTAR, EXPSTAR, EXPSTAR, EXPSTAR},
			{INVALID, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK},
			{INVALID, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK},
			{INVALID, DELIMTK, DELIMTK, DELIMTK, DELIMTK, DELIMTK, DELIMTK, DELIMTK, DELIMTK, DELIMTK},
			{EOFTK, EOFTK, EOFTK, EOFTK, EOFTK, EOFTK, EOFTK, EOFTK, EOFTK, EOFTK}	
		};
	public:
		Scanner(const char *);
		
		int filter();

		void scanToken();
		
};


#endif

