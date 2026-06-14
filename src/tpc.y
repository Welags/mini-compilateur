%{
/* tpc.y */
#include <stdio.h>
#include <unistd.h>
#include "tree.h"
#include "tpc.h"
#include "symbol_table.h"
#include <string.h>
#include <getopt.h>
void translate(Node* tree, FILE* f);
extern FILE *yyin;

int yylex();
void yyerror(char *);
int lineno = 1;
extern int current_column;
Node *root = NULL;
Symbol *tableGlobale[TAILLE_TABLE];
LocalTableNode* localTables = NULL;

static struct option option_complete[] = {
    {"tree",  no_argument, 0, 't'},
    {"help",  no_argument, 0, 'h'},
    {"symtabs",  no_argument, 0, 's'},
    {0, 0, 0, 0}
};
%}
%union {
    char byte;
    int num;
    char ident[64];
    char comp[3];
    Node *node;
}

%type <node> Prog DeclVars DeclStruct ContenuStruct Declarateurs DeclFoncts DeclFonct EnTeteFonct Parametres 
%type <node> ListTypVar Corps SuiteInstr Instr Exp TB FB M E T F 
%type <node> Arguments ListExp FieldPathDot

%token <byte> CHARACTER ADDSUB DIVSTAR
%token <num> NUM
%token <ident> IDENT
%token <comp> ORDER EQ
%token OR
%token AND
%token <ident> TYPE
%token STRUCT
%token VOID
%token IF
%token ELSE
%token WHILE
%token RETURN


%%
Prog:  DeclVars DeclFoncts
    {
        $$ = makeNode(program);
        addChild($$,$1);
        addChild($$,$2);
        root = $$;
    }
    
    ;
DeclVars:

      DeclVars TYPE Declarateurs ';'
      {
        if ($1 == NULL){
            $$ = makeNode(declarations);
        }else {
            $$ = $1;
        }
        Node * d = makeNode(declaration);
        Node *t = makeNodeString(type, $2);
        addChild(t,$3);
        addChild(d,t);
        addChild($$,d);

      }
    | DeclVars STRUCT IDENT Declarateurs ';'
    {
       if ($1 == NULL){
            $$ = makeNode(declarations);
        }else {
            $$ = $1;
        }
        Node *d = makeNode(declaration);
        Node *s = makeNode(structure);
        Node * i = makeNodeString(id,$3);
        
        addChild(s,i);
        addChild(s,$4);
        addChild(d,s);
        addChild($$,d);
    }
    | DeclVars DeclStruct

    {
        if ($1 == NULL){
            $$ = makeNode(declarations);
        }else {
            $$ = $1;
        }
        addChild($$,$2);

    }
    | 
    {
        $$ = NULL;
    }
    ;
DeclStruct:
       STRUCT IDENT '{' ContenuStruct '}' ';'
       {
        Node *d = makeNode(declaration);
        Node *s = makeNode(structure);
        Node *i = makeNodeString(id,$2);
        
        addChild(s,i);
        addChild(s,$4);
        addChild(d,s);
        $$ = d;
       }
    ;
ContenuStruct:
        ContenuStruct TYPE Declarateurs ';'
        {
            Node *c;
            if ($1 == NULL){
                c = makeNode(contenustruct);
            }else {
                c = $1 ;
            }
            Node *t = makeNodeString(type, $2);
            addChild(t,$3);
            addChild(c,t);
            $$ = c;
        }
    |   TYPE Declarateurs ';'
    {
        Node *c = makeNode(contenustruct);
        Node *t = makeNodeString(type, $1);
        addChild(t,$2);
        addChild(c,t);
        $$ = c;
    }
    |   ContenuStruct STRUCT IDENT Declarateurs ';'
    {
        Node *c;
        if ($1 == NULL){
            c = makeNode(contenustruct);
        } else {
            c = $1;
        }

        Node *s = makeNode(structure);
        Node *i = makeNodeString(id, $3);

        addChild(s, i);
        addChild(s, $4);
        addChild(c, s);

        $$ = c;
    }
    |   STRUCT IDENT Declarateurs ';'
    {
        Node *c = makeNode(contenustruct);
        Node *s = makeNode(structure);
        Node *i = makeNodeString(id, $2);

        addChild(s, i);
        addChild(s, $3);
        addChild(c, s);

        $$ = c;
    }
    ;
Declarateurs:
       Declarateurs ',' IDENT
       {
        $$ = $1;
        addSibling($$,makeNodeString(id,$3));
       }
    |  IDENT
    {

        $$ = makeNodeString(id,$1);
    }
    ;
DeclFoncts:
       DeclFoncts DeclFonct
       {
        if ($1==NULL){
            $$ = makeNode(functions);
        }else {
            $$ = $1;
        }
        addChild($$,$2);

       }
    |  DeclFonct
    {
        $$ = makeNode(functions);
        addChild($$,$1);
    }
    ;
DeclFonct:
       EnTeteFonct Corps
       {
        $$ = makeNode(function);
        addChild($$,$1);
        addChild($$,$2);
       }
    ;
EnTeteFonct:
       TYPE IDENT '(' Parametres ')'
       {
        Node * h = makeNode(heading);
        Node * t = makeNodeString(type,$1);
        Node * i = makeNodeString(id,$2);
        
        addChild(h,i);
        addChild(h,t);
        addChild(h,$4);
        $$ = h;

       }
    |  STRUCT IDENT IDENT '(' Parametres ')'
    {
        Node * h = makeNode(heading);
        Node * s = makeNode(structure);
        Node * t = makeNode(type);
        Node * id_structure = makeNodeString(id,$2);
        Node * id_function = makeNodeString(id,$3);
        addChild(s,id_structure);
        addChild(t,s);
        addChild(h,t);
        addChild(h,id_function);
        addChild(h,$5);
        $$ = h ;

    }
    |  VOID IDENT '(' Parametres ')'
    {
        Node * h  = makeNode(heading);
        Node * t = makeNode(type);
        Node * v = makeNodeString(type,"void");
        Node * i = makeNodeString(id,$2);
        addChild(t,v);
        addChild(h,t);
        addChild(h,i);
        addChild(h,$4);
        $$ = h;
    }
    ;
Parametres:
       VOID
       {
        $$ = makeNode(parameters);
       }
    |  ListTypVar
    {
        $$ = $1;
    }
    ;
ListTypVar:
       ListTypVar ',' TYPE IDENT
       {
        $$ = $1;
        Node * t = makeNodeString(type,$3);
        Node * i = makeNodeString(id,$4);
        addChild(t,i);
        addChild($$,t);
       }
    |  TYPE IDENT
    {
        Node * p = makeNode(parameters);
        Node * t = makeNodeString(type,$1);
        Node * i = makeNodeString(id,$2);
        addChild(t,i);
        addChild(p,t);
        $$ = p;
    }
    |  ListTypVar ',' STRUCT IDENT IDENT
    {
        $$  = $1;
        Node *t = makeNode(type);
        Node * s = makeNode(structure);
        addChild(s,makeNodeString(id,$4));
        addChild(t,s);
        Node *i = makeNodeString(id,$5);
        addChild(t,i);
        addChild($$,t);
    }
    |  STRUCT IDENT IDENT    
    {
        Node * p = makeNode(parameters);
        Node *t = makeNode(type);
        Node * s = makeNode(structure);
        addChild(s,makeNodeString(id,$2));
        addChild(t,s);
        Node *i = makeNodeString(id,$3);
        addChild(t,i);
        addChild(p,t);
        $$ = p;
    }
    ;
Corps: '{' DeclVars SuiteInstr '}'
    {
        Node *b = makeNode(body);
        addChild(b,$2);
        addChild(b,$3);
        $$ = b;
    }
    ;
SuiteInstr:
       SuiteInstr Instr
       {
        $$ = $1;
        addChild($$,$2);
       }
    | 
    {
        $$ = makeNode(instructions);
    }
    ;
Instr:
       FieldPathDot '=' Exp ';'  
    {
        Node *a = makeNode(assign);
        addChild(a,$1);
        addChild(a,$3);
        $$ = a;
    }
    |  IF '(' Exp ')' Instr
    {
        Node * ifc = makeNode(if_);
        Node * c = makeNode(condition);
        addChild(c,$3);
        addChild(ifc,c);
        addChild(ifc,$5);
        $$ = ifc;
    }
    |  IF '(' Exp ')' Instr ELSE Instr
        {
        Node * ifc = makeNode(if_);
       
        Node * c = makeNode(condition);
        addChild(c,$3);
        
        addChild(ifc,c);
        addChild(ifc,$5);
        addChild(ifc,$7);
        $$ = ifc;
        

    }
    |  WHILE '(' Exp ')' Instr
        {
        Node * whilec  = makeNode(while_);
        Node * c = makeNode(condition);
        addChild(c,$3);
        addChild(whilec,c);
        addChild(whilec,$5);
        $$ = whilec;

    }
    |  IDENT '(' Arguments  ')' ';'
    {
        Node *  cf = makeNode(call_function);
        Node * i = makeNodeString(id,$1);
        addChild(cf,i);
        addChild(cf,$3);
        $$ = cf;
    }
    |  RETURN Exp ';'
    {
        Node *r = makeNode(return_);
        addChild(r,$2);
        $$ = r;
    }
    |  RETURN ';'
    {
        Node *r = makeNode(return_);
  
        $$ = r;
    }
    |  '{' SuiteInstr '}'
    {
        $$ = $2;
    }
    |  ';'
    {
        $$ = makeNode(instructions);
    }
    ;
Exp :  Exp OR TB
    {
        Node * o = makeNode(or_);
        addChild(o,$1);
        addChild(o,$3);
        $$ = o;
    }
    |  TB
    {
        $$ =  $1;
    }
    ;
TB  :  TB AND FB
    {
        Node * a = makeNode(and_);
        addChild(a,$1);
        addChild(a,$3);
        $$ = a;
    }
    |  FB
    {
        $$ = $1;
    }
    ;
FB  :  FB EQ M
    {
        Node *e = makeNodeString(compare,$2);
        addChild(e,$1);
        addChild(e,$3);
        $$ = e;
    }
    |  M
    ;
M   :  M ORDER E
    {
        Node *o = makeNodeString(order,$2);
        addChild(o,$1);
        addChild(o,$3);
        $$ = o;
    }
    |  E
    {
        $$ = $1;
    }
    ;
E   :  E ADDSUB T
    {
        Node *o;
        if ($2=='+'){ 
            o = makeNode(add);

        }else{
            o = makeNode(sub);
        }
        addChild(o,$1);
        addChild(o,$3);
        $$ = o;
    }
    |  T
    {
        $$ = $1;
    }
    ;    
T   :  T DIVSTAR F 
    {
        char buffer[2];
        buffer[0] = $2;
        buffer[1] = '\0';
        Node * d = makeNodeString(divstar,buffer);
        addChild(d,$1);
        addChild(d,$3);
        $$ = d;
    }
    |  F
    {
        $$ = $1;
    }
    ;
F   :  ADDSUB F
    {
        Node *o;
        if ($1=='-'){
            o = makeNode(negatif);
        }else {
            o = makeNode(positif);
        }
        addChild(o,$2);
        $$ = o;
    }
    |  '!' F
    {
        Node * n = makeNode(not_);
        addChild(n,$2);
        $$ = n;
    }
    |  '(' Exp ')'
    {
        $$ = $2;
    }
    |  NUM
    {
        char buffer[64];
        sprintf(buffer,"%d",$1);
        $$ = makeNodeString(num,buffer);
    }
    |  CHARACTER
    {   
        char buffer[2];
        buffer[0] = $1;
        buffer[1] = '\0';
        $$ = makeNodeString(character,buffer);
    }
  

    |  IDENT '(' Arguments  ')'
    {
        Node * cf = makeNode(call_function);
        Node * i = makeNodeString(id,$1);
        addChild(cf,i);
        addChild(cf,$3);

        $$ = cf;
    }
    |  FieldPathDot
    {
        $$ = $1;
    }
    ;
FieldPathDot:
      IDENT    
      {
        Node *i = makeNodeString(id,$1);
        $$ = i;
      }
    |  FieldPathDot '.' IDENT
    {
        Node *f =makeNode(field_dot);
        addChild(f,$1);
        Node * i = makeNodeString(id,$3);
        addChild(f,i);
        $$ = f;
    } 
    ;
Arguments:
       ListExp
       {
        $$ = $1;
       }
    |
    {
        $$ = makeNode(arguments);
    }
    ;
ListExp:
       ListExp ',' Exp
       {

        $$ = $1;
        addChild($$,$3);
       }
    |  Exp
    {
        Node *a = makeNode(arguments);
        addChild(a,$1);
        $$ = a;
    }
    ;
%%
void yyerror(char *s) {
    fprintf(stderr, "Erreur syntaxique : %s a la ligne %d colonne %d\n",s,lineno,current_column);
}

void h_print(const char *arg){
    fprintf(stderr,"utilisation : %s  option fichier\n Options :\n -t | --tree :affiche l’arbre abstrait sur la sortie standard\n -h | --help : affiche une description de l’interface utilisateur et termine l’exécution\n -s | --symtabs : affiche les tables de symboles\n",arg);
}
int main(int argc, char **argv) {
    int canShow =0;
    int option;
    int showtabl = 0;
    while((option = getopt_long(argc,argv,"ths",option_complete,NULL)) != -1){
        switch(option){
            case 't':
                canShow =1;
                break;
            case 'h':
                h_print(argv[0]);
                return 0;
            case 's':
                showtabl = 1;
                break;
            default : 
                    fprintf(stderr,"Option inconnu");
                    return 3;
        }
    }
    
    if (optind<argc){
        yyin = fopen(argv[optind],"r");
        if (yyin == NULL){
            fprintf(stderr,"erreur d'ouverture");
            return 3;
        }
    }
    int r = yyparse();

    if (root != NULL) {
    
        //Symbol *tableGlobale[TAILLE_TABLE];
        init_table(tableGlobale);
        ajout_fonction(tableGlobale, "putint", TYPE_VOID);
        ajout_fonction(tableGlobale, "putchar", TYPE_VOID);
        ajout_fonction(tableGlobale, "getint", TYPE_INT);
        ajout_fonction(tableGlobale, "getchar", TYPE_CHAR);
        deplct = 0;
        //parcours_struct_def(root);
        ajout_globalTPC(root->firstChild, tableGlobale);
        parcours_fonctions(root);
        
        verif_existence_main(root);
        verif_return_fonctions(root);
        if (showtabl) {
        printf("Table globale :\n");
        afficher_table(tableGlobale);
        afficher_table_locale();
        }
        FILE* f = fopen("_anonymous.asm", "w");
        if (f == NULL){
            fprintf(stderr,"erreur de creation\n");
            return 3;
        }
        translate(root,f);
        fclose(f);
    }

    if (root!=NULL && canShow == 1){
        printTree(root);

    }
    return r;

}