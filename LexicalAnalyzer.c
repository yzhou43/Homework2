/*This file is a lexical analyzer system for simple arithmetic expressions

Addition				+
Subtraction				-
Multiplication			*
Division				/
Module					%
Less than				<
Greater than			>
Equal To				=
Not Equal To			!

IDENT = [a-zA-Z]+[ a-zA-Z0-9]*
INT_LIT = [0-9]+
FLOAT_LIT = [0-9]+. [0-9]+

*/


#include <stdio.h>
#include <ctype.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
//Store the tokens for following syntax analyzer
int tokens[100];
int i = 0;
//Check if there are invalid characters in the string
int length;
int validLength = 0;

FILE *in_fp;

/* Function declarations */
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);

/* Character classes */
#define LETTER 1
#define DIGIT 2
#define DECI_POINT 3
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define FLOAT_LIT 12
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define MOD_OP 25
#define LEFT_PAREN 26
#define RIGHT_PAREN 27
#define EQU_OP 28
#define UNE_OP 29
#define LES_OP 30
#define GRE_OP 31
#define SEMI 32
#define LEFT_BRAC 33
#define RIGHT_BRAC 34

/******************************************************/
/* main driver */
int main(void) {
	/* Open the input data file and process its contents */
	//This program needs an input file named "input.txt"	
	if ((in_fp = fopen("input.txt", "r")) == NULL)
		printf("ERROR - cannot open front.in \n");
	else {
		fseek(in_fp, 0, SEEK_END);
		length  = ftell(in_fp);
//		printf("%d",length);
		in_fp = fopen("input.txt", "r");
		printf("Lexical Analysis\n\n");
		getChar();
		do {
			lex();
		} while (nextToken != EOF);
	}
//	 printf("%d\n",validLength);
	if (validLength == length - 1) {
		printf("\nNo lexical error\n");
	} else
		printf("\nERROR!\n");
//	 for (int k = 0; k<100; k++){
//	 	printf("%d",tokens[k]);
//	 }
	return 0;
}
/******************************************************/
/* lookup - a function to look up operators and
 parentheses and return the token */
int lookup(char ch) {
	switch (ch) {
		case '(':
			addChar();
			nextToken = LEFT_PAREN;
			break;
		case ')':
			addChar();
			nextToken = RIGHT_PAREN;
			break;
		case '+':
			addChar();
			nextToken = ADD_OP;
			break;
		case '-':
			addChar();
			nextToken = SUB_OP;
			break;
		case '*':
			addChar();
			nextToken = MULT_OP;
			break;
		case '/':
			addChar();
			nextToken = DIV_OP;
			break;
		case '%':
			addChar();
			nextToken = MOD_OP;
			break;
		case '=':
			addChar();
			nextToken = EQU_OP;
			break;
		case '!':
			addChar();
			nextToken = UNE_OP;
			break;
		case '<':
			addChar();
			nextToken = LES_OP;
			break;
		case '>':
			addChar();
			nextToken = GRE_OP;
			break;
		case ';':
			addChar();
			nextToken = SEMI;
			break;
		default:
			addChar();
			nextToken = EOF;
			break;
	}
	return nextToken;
}

/******************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar(void) {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = '\0';
	} else
		printf("Error - lexeme is too long \n");
}


/******************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar(void) {
	if ((nextChar = getc(in_fp)) != EOF) {
		validLength++;
		if (isalpha(nextChar))
			charClass = LETTER;
		else if (isdigit(nextChar))
			charClass = DIGIT;
		else if (nextChar == '.')
			charClass = DECI_POINT;
		else
			charClass = UNKNOWN;
	} else
		charClass = EOF;
}


/******************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank(void) {
	while (isspace(nextChar))
		getChar();
}

/******************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex(void) {
	lexLen = 0;
	getNonBlank();
	switch (charClass) {
		/* Identifiers */
		case LETTER:
			addChar();
			getChar();
			while (charClass == LETTER || charClass == DIGIT) {
				addChar();
				getChar();
			}
			nextToken = IDENT;
			break;
		/* Integer literals */
		case DIGIT:
			addChar();
			getChar();
			while (charClass == DIGIT) {
				addChar();
				getChar();
			}
			nextToken = INT_LIT;
			// Floating point literals
			if (charClass == DECI_POINT) {
				addChar();
				getChar();
				while (charClass == DIGIT) {
					addChar();
					getChar();
				}
				nextToken = FLOAT_LIT;
			}
			break;
		/* Parentheses and operators */
		case UNKNOWN:
			lookup(nextChar);
			getChar();
			break;
		/* EOF */
		case EOF:
			nextToken = EOF;
			lexeme[0] = 'E';
			lexeme[1] = 'O';
			lexeme[2] = 'F';
			lexeme[3] = '\0';
			break;
	} /* End of switch */
	printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
	tokens[i] = nextToken;
	i = i + 1;
	return nextToken;
} /* End of function lex */
