#ifndef SCANNER_H
#define SCANNER_H
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string.h>

enum TokenID {
	IDTK = 1000,
	NUMTK,
	OPTK,
	DELIMTK,
	EOFTK,
	KEYWORD,
	DELOPTK,
	LEOPTK,
	GEOPTK,
	LTOPTK,
	GTOPTK,
	NEOPTK,
	EQOPTK,
	ASSIGNOPTK,
	DBLESTAR,
	DBLESLASH,
	LFTPARENDELIM,
	RGHTPARENDELIM,
	LFTCURLYDELIM,
	RGHTCURLYDELIM,
	LFTSQREDELIM,
	RGHTSQREDELIM,
	SEMICOLON
};


struct Token {
	TokenID tokenID;
	char lexeme[9];
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
};


enum INVALIDS {
	INVALID = -2000,
	INVDLETTER,
	INVDSLASH,
	INVDSTAR,
	
};


class Scanner {
	private:
		char lookahead;
		int lineCount = 1;
		int charGroup = -1; // init used as a flag to determine whether the scanner is on the first char of the first token
		char textBuffer[1024];
		char *lookaheadPlace;
		static const int NUMOFSTATES = 13;
		static const int NUMOFCOLUMNS = 10;

		
		void incrementCharPtr();
		
// right now the invalid column for eof is still eof may cause probs i feel it will actually fix them
		const int FATable[NUMOFSTATES][NUMOFCOLUMNS] = {
			{INVALID, S2, S3, S4, S7, S9, S11, S12, S13, S1},
			{IDTK, S2, S2, IDTK, IDTK, IDTK, IDTK, IDTK, IDTK, IDTK},
			{NUMTK, NUMTK, S3, NUMTK, NUMTK, NUMTK, NUMTK, NUMTK, NUMTK, NUMTK},
			{INVDLETTER, S5, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER},
			{INVDLETTER, S6, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER, EXPLETTER},
			{OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK},
			{INVDSLASH, EXPSLASH, EXPSLASH, EXPSLASH, S8, EXPSLASH, EXPSLASH, EXPSLASH, EXPSLASH, EXPSLASH},
			{OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK},
			{INVDSLASH, EXPSTAR, EXPSTAR, EXPSTAR, EXPSTAR, S10, EXPSTAR, EXPSTAR, EXPSTAR, EXPSTAR},
			{OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK},
			{OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK, OPTK},
			{OPTK, DELIMTK, DELIMTK, DELIMTK, DELIMTK, DELIMTK, DELIMTK, DELIMTK, DELIMTK, DELIMTK},
			{EOFTK, EOFTK, EOFTK, EOFTK, EOFTK, EOFTK, EOFTK, EOFTK, EOFTK, EOFTK}
		};
	public:
		Scanner(const char *);
		
		int filter();

		Token scanToken();
		
};


#endif

