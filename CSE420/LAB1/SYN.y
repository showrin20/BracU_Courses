%{

#include "symbol_info.h"

#define YYSTYPE symbol_info*

int yyparse(void);   //This line will match generated token with rules
int yylex(void);

extern FILE *yyin;  //built-in variable for input file


ofstream outlog;

int lines = 1;

// declare any other variables or functions needed here. THIS IS THE ASSIGNMENT FILE . C C++

void yyerror(const char *s)
{
    outlog << "At line " << lines << " " << s << std::endl << std::endl;
}

%}

%token IF ELSE FOR WHILE DO GOTO BREAK CONTINUE RETURN 
%token INT FLOAT CHAR VOID DOUBLE 
%token SWITCH CASE DEFAULT PRINTF 
%token ADDOP MULOP INCOP DECOP RELOP ASSIGNOP LOGICOP NOT LPAREN 
%token RPAREN LCURL RCURL LTHIRD RTHIRD COLON SEMICOLON COMMA 
%token ID CONST_INT CONST_FLOAT

// Precedence
%left LOGICOP  
%left RELOP    
%left ADDOP    
%left MULOP    


%%

//RULE PART 

start : program    
	{
		outlog<<"At line no: "<<lines<<" start : program "<<endl<<endl;
	}
	;

program : program unit    
	{
		outlog<<"At line no: "<<lines<<" program : program unit "<<endl<<endl;
		outlog<<$1->getname()+"\n"+$2->getname()<<endl<<endl;
		
		$$ = new symbol_info($1->getname()+"\n"+$2->getname(),"program");
	}
	| unit
	{
		outlog<<"At line no: "<<lines<<" program : unit "<<endl<<endl;
		outlog<<$1->getname()<<endl<<endl;
		
		$$ = new symbol_info($1->getname(),"program");

	}
	;

unit : var_declaration
    {
            outlog<<"At line no: "<<lines<<" unit : var_declaration "<<endl<<endl;
            outlog<<$1->getname()<<endl<<endl;
            
            $$ = new symbol_info($1->getname(),"unit");

        }
    | func_definition
    {
            outlog<<"At line no: "<<lines<<" unit : func_definition "<<endl<<endl;
            outlog<<$1->getname()<<endl<<endl;
            
            $$ = new symbol_info($1->getname(),"unit");

        }
    ;

func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement
		{	
			outlog<<"At line no: "<<lines<<" func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement "<<endl<<endl;
			outlog<<$1->getname()<<" "<<$2->getname()<<"("<<$4->getname()<<")\n"<<$6->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname() + " " + $2->getname() + "(" + $4->getname() + ")\n" + $6->getname(), "func_def");

		}
		| type_specifier ID LPAREN RPAREN compound_statement
		{
			
			outlog<<"At line no: "<<lines<<" func_definition : type_specifier ID LPAREN RPAREN compound_statement "<<endl<<endl;
			outlog<<$1->getname()<<" "<<$2->getname()<<"()\n"<<$5->getname()<<endl<<endl;
			
			$$ = new symbol_info($1->getname()+" "+$2->getname()+"()\n"+$5->getname(),"func_def");	
		}
 		;

parameter_list: parameter_list COMMA type_specifier ID
	{
		outlog << "At line no: " << lines << " parameter_list : parameter_list COMMA type_specifier ID " << endl << endl;
		outlog << $1->getname() << ", " << $3->getname() << " " << $4->getname() << endl << endl;
		$$ = new symbol_info($1->getname()+", "+$3->getname()+" "+$4->getname(), "param_list");
	}
	| parameter_list COMMA type_specifier
	{
		outlog << "At line no: " << lines << " parameter_list : parameter_list COMMA type_specifier " << endl << endl;
		outlog << $1->getname() << ", " << $3->getname() << endl << endl;
		$$ = new symbol_info($1->getname() + ", " + $3->getname(), "param_list");
	}
	| type_specifier ID
	{
		outlog << "At line no: " << lines << " parameter_list : type_specifier ID " << endl << endl;
		outlog << $1->getname() << " " << $2->getname() << endl << endl;
		$$ = new symbol_info($1->getname() + " " + $2->getname(), "param_list");
	}
	| type_specifier
	{
		outlog << "At line no: " << lines << " parameter_list : type_specifier " << endl << endl;
		outlog << $1->getname() << endl << endl;
		$$ = new symbol_info($1->getname(), "param_list");
	};





compound_statement: LCURL statements RCURL
    {
        outlog << "At line no: " << lines << " compound_statement : LCURL statements RCURL " << endl << endl;
        outlog << "{\n" << $2->getname() << "\n}" << endl << endl;

        $$ = new symbol_info("{\n" + $2->getname() + "\n}", "compound_statement");
    }
    | LCURL RCURL
    {
        outlog << "At line no: " << lines << " compound_statement : LCURL RCURL " << endl << endl;
        outlog << "{ }" << endl << endl;

        $$ = new symbol_info("{ }", "compound_statement");
    };

var_declaration: type_specifier declaration_list SEMICOLON
    {
        outlog << "At line no: " << lines << " var_declaration : type_specifier declaration_list SEMICOLON " << endl << endl;
        outlog << $1->getname() << " " << $2->getname() << ";" << endl << endl;

        $$ = new symbol_info($1->getname() + " " + $2->getname() + ";", "var_declaration");
    };

type_specifier: INT
    {   
        outlog<<"At line no: "<< lines <<" type_specifier : INT "<<endl<<endl;
		outlog<<"int"<<endl<<endl;
        $$ = new symbol_info("int", "type_specifier");
    }
    | FLOAT
    {   
        outlog<<"At line no: "<< lines <<" type_specifier: FLOAT "<<endl<<endl;
		outlog<<"float"<<endl<<endl;

        $$ = new symbol_info("float", "type_specifier");
    }
    | VOID
    {   
        outlog<<"At line no: "<< lines <<" type_specifier: VOID "<<endl<<endl;
		outlog<<"void"<<endl<<endl;
        $$ = new symbol_info("void", "type_specifier");
    };

declaration_list: declaration_list COMMA ID
    {
        outlog << "At line no: " << lines << " declaration_list : declaration_list COMMA ID " << endl << endl;
        outlog << $1->getname() << ", " << $3->getname() << endl << endl;

        $$ = new symbol_info($1->getname() + ", " + $3->getname(), "declaration_list");
    }
    | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
    {
        outlog << "At line no: " << lines << " declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD " << endl << endl;
        outlog << $1->getname() << ", " << $3->getname() << "[" << $5->getname() << "]" << endl << endl;

        $$ = new symbol_info($1->getname() + ", " + $3->getname() + "[" + $5->getname() + "]", "declaration_list");
    }
    | ID
    {
        outlog << "At line no: " << lines << " declaration_list : ID " << endl << endl;
        outlog << $1->getname() << endl << endl;

        $$ = new symbol_info($1->getname(), "declaration_list");
    }
    | ID LTHIRD CONST_INT RTHIRD
    {
        outlog << "At line no: " << lines << " declaration_list : ID LTHIRD CONST_INT RTHIRD " << endl << endl;
        outlog << $1->getname() << "[" << $3->getname() << "]" << endl << endl;

        $$ = new symbol_info($1->getname() + "[" + $3->getname() + "]", "declaration_list");
    };

statements: statement
    {   outlog << "At line no: " << lines << " statements : statement " << endl << endl;
        outlog << $1->getname() << endl << endl;
        $$ = new symbol_info($1->getname(), "statements");
    }
    | statements statement
    {
        outlog << "At line no: " << lines << " statements : statements statement " << endl << endl;
        outlog << $1->getname() + $2->getname() << endl << endl;

        $$ = new symbol_info($1->getname() +  $2->getname(), "statements");
    };


statement: var_declaration
    {
        outlog << "At line no: " << lines << " statement : var_declaration " << endl << endl;
        outlog << $1->getname() << endl << endl;

        $$ = new symbol_info($1->getname(), "stmnt");
    }
    | expression_statement
    {
        outlog << "At line no: " << lines << " statement : expression_statement " << endl << endl;
        outlog << $1->getname() << endl << endl;

        $$ = new symbol_info($1->getname(), "stmnt");
    }
    | compound_statement
    {
        outlog << "At line no: " << lines << " statement : compound_statement " << endl << endl;
        outlog << $1->getname() << endl << endl;

        $$ = new symbol_info($1->getname(), "stmnt");
    }
    | FOR LPAREN expression_statement expression_statement expression RPAREN statement
    {
        outlog << "At line no: " << lines << " statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement " << endl << endl;
        outlog << "for(" << $3->getname() << $4->getname() << $5->getname() << ")\n" << $7->getname() << endl << endl;

        $$ = new symbol_info("for(" + $3->getname() + $4->getname() + $5->getname() + ")\n" + $7->getname(), "stmnt");
    }
    | IF LPAREN expression RPAREN statement ELSE statement
    {
        outlog << "At line no: " << lines << " statement : IF LPAREN expression RPAREN statement ELSE statement " << endl << endl;
        outlog << "if(" << $3->getname() << ")\n" << $5->getname() << "\nelse\n" << $7->getname() << endl << endl;

        $$ = new symbol_info("if(" + $3->getname() + ")\n" + $5->getname() + "\nelse\n" + $7->getname(), "stmnt");
    }
    | WHILE LPAREN expression RPAREN statement
    {
        outlog << "At line no: " << lines << " statement : WHILE LPAREN expression RPAREN statement " << endl << endl;
        outlog << "while(" << $3->getname() << ")\n" << $5->getname() << endl << endl;

        $$ = new symbol_info("while(" + $3->getname() + ")\n" + $5->getname(), "stmnt");
    }
	| GOTO ID SEMICOLON
    {
        outlog << "At line no: " << lines << " statement : GOTO ID SEMICOLON " << std::endl;
        $$ = new symbol_info("goto " + $2->getname(), "stmt");
	}
    | PRINTF LPAREN ID RPAREN SEMICOLON
    {
        outlog << "At line no: " << lines << " statement : PRINTF LPAREN ID RPAREN SEMICOLON " << endl << endl;
        outlog << "printf(" << $3->getname() << ");" << endl << endl;

        $$ = new symbol_info("printf(" + $3->getname() + ");", "stmnt");
    }
    | RETURN expression SEMICOLON
    {
        outlog << "At line no: " << lines << " statement : RETURN expression SEMICOLON " << endl << endl;
        outlog << "return " << $2->getname() << ";" << endl << endl;

        $$ = new symbol_info("return " + $2->getname() + ";", "stmnt");
    };

expression_statement: SEMICOLON
    {
        outlog << "At line no: " << lines << " expression_statement : SEMICOLON " << endl << endl;

        $$ = new symbol_info(";\n", "expression_statement");
    }
    | expression SEMICOLON
    {
        outlog << "At line no: " << lines << " expression_statement : expression SEMICOLON " << endl << endl;
        outlog << $1->getname() << ";" << endl << endl;

        $$ = new symbol_info($1->getname() + ";\n", "expression_statement");
    };

variable: ID
    {
        outlog << "At line no: " << lines << " variable : ID " << endl << endl;
        outlog << $1->getname() << endl << endl;

        $$ = new symbol_info($1->getname(), "variable");
    }
    | ID LTHIRD expression RTHIRD
    {
        outlog << "At line no: " << lines << " variable : ID LTHIRD expression RTHIRD " << endl << endl;
        outlog << $1->getname() << "[" << $3->getname() << "]" << endl << endl;

        $$ = new symbol_info($1->getname() + "[" + $3->getname() + "]", "variable");
    };

expression: logic_expression
    {
        outlog << "At line no: " << lines << " expression : logic_expression " << endl << endl;
        outlog << $1->getname() << endl << endl;

        $$ = new symbol_info($1->getname(), "expression");
    }
    | variable ASSIGNOP logic_expression
    {
        outlog << "At line no: " << lines << " expression : variable ASSIGNOP logic_expression " << endl << endl;
        outlog << $1->getname() << "=" << $3->getname() << endl << endl;

        $$ = new symbol_info($1->getname() + "=" + $3->getname(), "expression");
    };

logic_expression: rel_expression
    {
        outlog << "At line no: " << lines << " logic_expression : rel_expression " << endl << endl;
        outlog << $1->getname() << endl << endl;

        $$ = new symbol_info($1->getname(), "logic_expression");
    }
    | rel_expression LOGICOP rel_expression
    {
        outlog << "At line no: " << lines << " logic_expression : rel_expression LOGICOP rel_expression " << endl << endl;
        outlog << $1->getname() << " " << $2->getname() << " " << $3->getname() << endl << endl;

        $$ = new symbol_info($1->getname() + " " + $2->getname() + " " + $3->getname(), "logic_expression");
    };

rel_expression: simple_expression
    {
        outlog << "At line no: " << lines << " rel_expression : simple_expression " << endl << endl;
        outlog << $1->getname() << endl << endl;

        $$ = new symbol_info($1->getname(), "rel_expression");
    }
    | simple_expression RELOP simple_expression
    {
        outlog << "At line no: " << lines << " rel_expression : simple_expression RELOP simple_expression " << endl << endl;
        outlog << $1->getname() << $2->getname() <<  $3->getname() << endl << endl;

        $$ = new symbol_info($1->getname() +  $2->getname() +  $3->getname(), "rel_expression");
    };

simple_expression: term
    {
        outlog << "At line no: " << lines << " simple_expression : term " << endl << endl;
        outlog << $1->getname() << endl << endl;

        $$ = new symbol_info($1->getname(), "simple_expression");
    }
    | simple_expression ADDOP term
    {
        outlog << "At line no: " << lines << " simple_expression : simple_expression ADDOP term " << endl << endl;
        outlog << $1->getname() << " " << $2->getname() << " " << $3->getname() << endl << endl;

        $$ = new symbol_info($1->getname() + " " + $2->getname() + " " + $3->getname(), "simple_expression");
    };

term: unary_expression
    {
        outlog << "At line no: " << lines << " term : unary_expression " << endl << endl;
        outlog << $1->getname() << endl << endl;

        $$ = new symbol_info($1->getname(), "term");
    }
    | term MULOP unary_expression
    {
        outlog << "At line no: " << lines << " term : term MULOP unary_expression " << endl << endl;
        outlog << $1->getname()  << $2->getname() <<  $3->getname() << endl << endl;

        $$ = new symbol_info($1->getname()  + $2->getname() +  $3->getname(), "term");
    };

unary_expression: ADDOP unary_expression
    {
        outlog << "At line no: " << lines << " unary_expression : ADDOP unary_expression " << endl << endl;
        outlog << $1->getname() << $2->getname() << endl << endl;

        $$ = new symbol_info($1->getname() + $2->getname(), "unary_expression");
    }
    | NOT unary_expression
    {
        outlog << "At line no: " << lines << " unary_expression : NOT unary_expression " << endl << endl;
        outlog << $1->getname() << $2->getname() << endl << endl;

        $$ = new symbol_info($1->getname() + $2->getname(), "unary_expression");
    }
    | factor
    {
        outlog << "At line no: " << lines << " unary_expression : factor " << endl << endl;
        outlog << $1->getname() << endl << endl;

        $$ = new symbol_info($1->getname(), "unary_expression");
    };

factor: variable
    {
        outlog << "At line no: " << lines << " factor : variable " << endl << endl;
        outlog << $1->getname() << endl << endl;

        $$ = new symbol_info($1->getname(), "factor");
    }
    | ID LPAREN argument_list RPAREN
    {
        outlog << "At line no: " << lines << " factor : ID LPAREN argument_list RPAREN " << endl << endl;
        outlog << $1->getname() << "(" << $3->getname() << ")" << endl << endl;

        $$ = new symbol_info($1->getname() + "(" + $3->getname() + ")", "factor");
    }
    | LPAREN expression RPAREN
    {
        outlog << "At line no: " << lines << " factor : LPAREN expression RPAREN " << endl << endl;
        outlog << "(" << $2->getname() << ")" << endl << endl;

        $$ = new symbol_info("(" + $2->getname() + ")", "factor");
    }
    | CONST_INT
    {
        outlog << "At line no: " << lines << " factor : CONST_INT " << endl << endl;
        outlog << $1->getname() << endl << endl;

        $$ = new symbol_info($1->getname(), "factor");
    }
    | CONST_FLOAT
    {
        outlog << "At line no: " << lines << " factor : CONST_FLOAT " << endl << endl;
        outlog << $1->getname() << endl << endl;

        $$ = new symbol_info($1->getname(), "factor");
    }
    | variable INCOP
    {
        outlog << "At line no: " << lines << " factor : variable INCOP " << endl << endl;
        outlog << $1->getname() << "++" << endl << endl;

        $$ = new symbol_info($1->getname() + "++", "factor");
    }
    | variable DECOP
    {
        outlog << "At line no: " << lines << " factor : variable DECOP " << endl << endl;
        outlog << $1->getname() << "--" << endl << endl;

        $$ = new symbol_info($1->getname() + "--", "factor");
    };

argument_list: arguments
    {
        outlog << "At line no: " << lines << " argument_list : arguments " << endl << endl;
        outlog << $1->getname() << endl << endl;

        $$ = new symbol_info($1->getname(), "argument_list");
    }
    |
    {
        outlog << "At line no: " << lines << " argument_list : " << endl << endl;

        $$ = new symbol_info("", "argument_list");
    };

arguments: arguments COMMA logic_expression
    {
        outlog << "At line no: " << lines << " arguments : arguments COMMA logic_expression " << endl << endl;
        outlog << $1->getname() << ", " << $3->getname() << endl << endl;

        $$ = new symbol_info($1->getname() + ", " + $3->getname(), "arguments");
    }
    | logic_expression
    {
        outlog << "At line no: " << lines << " arguments : logic_expression " << endl << endl;
        outlog << $1->getname() << endl << endl;

        $$ = new symbol_info($1->getname(), "arguments");
    };



%%


int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (yyin == nullptr) {
        cerr << "Error: Could not open file " << argv[1] << endl;
        return 1;
    }

    outlog.open("my_log.txt", ios::trunc);  // opens the file in truncate mode
    if (!outlog) {
        cerr << "Error: Could not create log file" << endl;
        fclose(yyin);
        return 1;
    }

    yyparse();

    // Append total lines parsed to the log file
    outlog << "Total lines: " << lines << endl;

    outlog.close();
    fclose(yyin);

    return 0;
}
