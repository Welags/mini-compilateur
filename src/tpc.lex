%{
#include "tree.h"
#include "tpc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern int lineno;
int current_column = 1;
#define YY_USER_ACTION current_column += yyleng;
%}
%option nounput
%option noinput

%x COMMENTAIRE
%x COMMENTAIRE2

%%


"//" {BEGIN COMMENTAIRE;}
<COMMENTAIRE>"\n" {lineno++; current_column = 1; BEGIN INITIAL; }
<COMMENTAIRE>. {;}

"/*" {BEGIN COMMENTAIRE2;}
<COMMENTAIRE2>"*/" {BEGIN INITIAL;}
<COMMENTAIRE2>"\n" { lineno++; current_column = 1; }
<COMMENTAIRE2>(.|\n) {;}

"if" {return IF;}
"else" {return ELSE;}
"return" {return RETURN;}
"while" {return WHILE;}
"void" {return VOID;}
"struct" {return STRUCT;}

\'([^\'\n\t\\]|\\.)\' {
	if (yytext[1] == '\\'){
		if (yytext[2] == 'n')
			yylval.byte = '\n';
		else if (yytext[2] == 't')
			yylval.byte = '\t';
		else
			yylval.byte = yytext[2];
	}
	else
		yylval.byte = yytext[1];
	return CHARACTER;}
		

"int" {strcpy(yylval.ident, yytext); return TYPE;}
"char" {strcpy(yylval.ident, yytext); return TYPE;}

"<=" { strcpy(yylval.comp,yytext); return ORDER;}
">=" { strcpy(yylval.comp,yytext); return ORDER;}
"<" { strcpy(yylval.comp,yytext); return ORDER;}
">" { strcpy(yylval.comp,yytext); return ORDER;}

[+-] {yylval.byte = yytext[0]; return ADDSUB;}
[*/%] {yylval.byte = yytext[0]; return DIVSTAR;}

"==" { strcpy(yylval.comp,yytext); return EQ;}
"!=" { strcpy(yylval.comp,yytext); return EQ;}

"||" {return OR;}
"&&" {return AND;}
[.,;{}()=!] {return yytext[0];}

[a-zA-Z_][a-zA-Z_0-9]* {strcpy(yylval.ident,yytext);return IDENT;}
[0-9]+ {yylval.num = atoi(yytext); return NUM;}
[\n] { lineno++; current_column = 1; }
[\t] { current_column += 3; }
[\r ] {;}
. {fprintf(stderr, "Erreur lexicale à la ligne %d, colonne %d : caractère '%s' inconnu\n", lineno, current_column - 1, yytext); return 1;}
<<EOF>> {return 0;}

%%