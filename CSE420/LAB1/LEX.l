%option noyywrap

%{
#include "symbol_info.h"

#define YYSTYPE symbol_info*

extern ofstream outlog; // output filestream for log file
string loglist = "";    // list of tokens along with line numbers

#include "y.tab.h"

extern YYSTYPE yylval;
extern int lines;
void yyerror(char *);
%}

/* Regular Definitions */

delim   [ \t\v\r]      // defining whitespace delimiters

ws      [ \t]+
newline \n

letter  [A-Za-z_]
digit   [0-9]

id      {letter}({letter}|{digit})*
int     {digit}+
float   ({digit}+(\.{digit}*)?|\.[0-9]+)([eE][-+]?[0-9]+)?


%%

{ws}          { /* Ignore whitespace */ }

{newline}     { lines++; }

if            {
                loglist = "Line no " + to_string(lines) + ": Token <IF> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return IF;
            }

while         {
                loglist = "Line no " + to_string(lines) + ": Token <WHILE> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return WHILE;
            }

for           {
                loglist = "Line no " + to_string(lines) + ": Token <FOR> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return FOR;
            }

do            {
                loglist = "Line no " + to_string(lines) + ": Token <DO> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return DO;
            }

int           {
                loglist = "Line no " + to_string(lines) + ": Token <INT> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return INT;
            }

float         {
                loglist = "Line no " + to_string(lines) + ": Token <FLOAT> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return FLOAT;
            }

void          {
                loglist = "Line no " + to_string(lines) + ": Token <VOID> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return VOID;
            }

switch        {
                loglist = "Line no " + to_string(lines) + ": Token <SWITCH> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return SWITCH;
            }

goto          {
                loglist = "Line no " + to_string(lines) + ": Token <GOTO> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return GOTO;
            }

else          {
                loglist = "Line no " + to_string(lines) + ": Token <ELSE> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return ELSE;
            }

break         {
                loglist = "Line no " + to_string(lines) + ": Token <BREAK> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return BREAK;
            }

double        {
                loglist = "Line no " + to_string(lines) + ": Token <DOUBLE> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return DOUBLE;
            }

char          {
                loglist = "Line no " + to_string(lines) + ": Token <CHAR> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return CHAR;
            }

return        {
                loglist = "Line no " + to_string(lines) + ": Token <RETURN> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return RETURN;
            }

case          {
                loglist = "Line no " + to_string(lines) + ": Token <CASE> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return CASE;
            }

continue      {
                loglist = "Line no " + to_string(lines) + ": Token <CONTINUE> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return CONTINUE;
            }

printf        {
                loglist = "Line no " + to_string(lines) + ": Token <PRINTF> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return PRINTF;
            }



{id}          {
                symbol_info *s = new symbol_info((string)yytext, "ID");
                yylval = (YYSTYPE)s;
                loglist = "Line no " + to_string(lines) + ": Token <ID> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return ID;
            }

{int}         {
                symbol_info *s = new symbol_info((string)yytext, "CONST_INT");
                yylval = (YYSTYPE)s;
                loglist = "Line no " + to_string(lines) + ": Token <CONST_INT> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return CONST_INT;
            }

{float}       {
                symbol_info *s = new symbol_info((string)yytext, "CONST_FLOAT");
                yylval = (YYSTYPE)s;
                loglist = "Line no " + to_string(lines) + ": Token <CONST_FLOAT> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return CONST_FLOAT;
            }

"="           {
                loglist = "Line no " + to_string(lines) + ": Token <ASSIGNOP> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return ASSIGNOP;
            }

"!"           {
                loglist = "Line no " + to_string(lines) + ": Token <NOT> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return NOT;
            }

"("           {
                loglist = "Line no " + to_string(lines) + ": Token <LPAREN> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return LPAREN;
            }

")"           {
                loglist = "Line no " + to_string(lines) + ": Token <RPAREN> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return RPAREN;
            }

"{"           {
                loglist = "Line no " + to_string(lines) + ": Token <LCURL> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return LCURL;
            }

"}"           {
                loglist = "Line no " + to_string(lines) + ": Token <RCURL> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return RCURL;
            }

"["           {
                loglist = "Line no " + to_string(lines) + ": Token <LTHIRD> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return LTHIRD;
            }

"]"           {
                loglist = "Line no " + to_string(lines) + ": Token <RTHIRD> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return RTHIRD;
            }

","           {
                loglist = "Line no " + to_string(lines) + ": Token <COMMA> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return COMMA;
            }

":"           {
                loglist = "Line no " + to_string(lines) + ": Token <COLON> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return COLON;
            }

";"           {
                loglist = "Line no " + to_string(lines) + ": Token <SEMICOLON> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return SEMICOLON;
            }
"&&"        {
            loglist = "Line no " + to_string(lines) + ": Token <LOGICOP> Lexeme " + yytext + " found\n\n";
            outlog << loglist;
            return LOGICOP;
            }

"||"        {
            loglist = "Line no " + to_string(lines) + ": Token <LOGICOP> Lexeme " + yytext + " found\n\n";
            outlog << loglist;
            return LOGICOP;
            }

"<"|">"|"=="|"!="|"<="|">=" {
            symbol_info *s = new symbol_info((string)yytext, "RELOP");
            yylval = (YYSTYPE)s;
            loglist = "Line no " + to_string(lines) + ": Token <RELOP> Lexeme " + yytext + " found\n\n";
            outlog << loglist;
            return RELOP;
            }


"+"|"-"      {
                symbol_info *s = new symbol_info((string)yytext, "ADDOP");
                yylval = (YYSTYPE)s;
                loglist = "Line no " + to_string(lines) + ": Token <ADDOP> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return ADDOP;
            }

"*"|"/"|"%"  {
                symbol_info *s = new symbol_info((string)yytext, "MULOP");
                yylval = (YYSTYPE)s;
                loglist = "Line no " + to_string(lines) + ": Token <MULOP> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return MULOP;
            }

"++"|"--"    {
                symbol_info *s = new symbol_info((string)yytext, "INCOP");
                yylval = (YYSTYPE)s;
                loglist = "Line no " + to_string(lines) + ": Token <INCOP> Lexeme " + yytext + " found\n\n";
                outlog << loglist;
                return INCOP;
            }

%%
