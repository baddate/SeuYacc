%token IDENTIFIER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE VOID
%token BOOL
%token ';'

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
	:  type_specifier IDENTIFIER ';'
	;


translation_unit
	: declaration
	;



%%
