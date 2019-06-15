%token IDENTIFIER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE VOID
%token BOOL LE_OP NUMBER GE_OP EQ_OP NE_OP IF WHILE FOR ELSE 
%token DELIM  + - * / { } ( ) > <

%start translation_unit
%%


type_specifier
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| BOOL
	;

declaration
	:  type_specifier IDENTIFIER DELIM
	;

translation_unit
	: type_specifier IDENTIFIER ( ) { statements }
	;

statements
	: statement statements
	| statement
	;

statement
	: if_s
	| int_s
	| while_s
	| for_s
	| assignment
	;

int_s
	: type_specifier assignment DELIM
	;

assignment
	: IDENTIFIER = expression
	| IDENTIFIER
	;

expression
	: term 
	| term + term
	| term - term
	;

term
	: factor
	| factor * factor
	| factor / factor
	;

factor
	: IDENTIFIER
	| NUMBER
	| ( expression )
	;

if_s
	: IF ( expression relationcha expression ) { statements }
	| IF ( expression relationcha expression ) { statements } ELSE { statements }
	;
while_s
	: WHILE ( expression relationcha expression ) { statements }
	;

for_s
	: FOR ( assignment DELIM expression relationcha expression DELIM assignment ) { statements }
	;

relationcha
	: > 
	| < 
	| EQ_OP
	| LE_OP
	| GE_OP 
	| NE_OP
	;
%%
