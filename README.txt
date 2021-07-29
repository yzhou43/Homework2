Homework2


Addition			+
Subtraction			-
Multiplication			*
Division			/
Module				% 
Less than			<
Greater than			>
Equal To			= 
Not Equal To			!
	
IDENT = [a-zA-Z]+[ a-zA-Z0-9]*
INT_LIT = [0-9]+
FLOAT_LIT = [0-9]+. [0-9]+


<PROGRAM> ---> "{"  <STMT_LIST>   "}"
<STMT_LIST> ---> < STMT >{ \n < STMT >}
< STMT > --->  < EXPR > {(">"| "<" |"="|"!") < EXPR > }
< EXPR > --->  < TERM >  {("+"|"-") < TERM >}
< TERM > ---> < FACTOR > {("*"|"/"|"%") < FACTOR >}
< FACTOR > --> IDENT | INT_LIT | FLOAT_LIT | "(" < STMT > ")"
