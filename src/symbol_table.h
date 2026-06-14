#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "tree.h"

#define TAILLE_TABLE 1008

typedef enum {
    TYPE_CHAR,
    TYPE_INT,
    TYPE_VOID,
    TYPE_STRUCT
} Type;

typedef struct Symbol {
    char *name;
    int is_function;
    Type type;
    int adresse;
    struct Symbol* suivant;
    char* struct_name;
} Symbol;

typedef struct localtablenode {
    char *functionName;
    Symbol *table[1008];
    struct localtablenode* next;
}LocalTableNode;


typedef struct structchamps{
    char* name;
    int offset;
    Type type;
    char* struct_name;
    struct structchamps* next;
}StructChamps;

typedef struct structdef{
    char*name;
    StructChamps* champs;
    int taille;
    struct structdef* next;
} StructDef;


extern int deplct;
extern LocalTableNode* localTables;
extern StructDef *structDefs;
int hashage(char *str);
void init_table(Symbol *table[]);
Symbol *ajout(Symbol *table[], char *name, Type type);
int type_et_taille(Node *n, Type *t, int *taille);
int ajout_globalTPC(Node *decls, Symbol *table[]);
void ajout_parametres(Node *params, Symbol *tableLocale[]);
void ajout_variables_locales(Node *decls, Symbol *tableLocale[]);
void afficher_table(Symbol *table[]);
void construire_table_fonction(Node *f);
void parcours_fonctions(Node *n);
void afficher_table_locale();
Symbol** get_local_table(char* function_name);
Symbol * recherche(Symbol *table[],char *name);
Type get_type_expression(Node* n, Symbol** tableLocale, Symbol** tableGlobale);

void verif_existence_main(Node *n);
int verif_return_noeud(Node *n, Type typeRetour, Symbol **tableLocale);
void verif_return_fonctions(Node *root);

StructDef* trouver_struct(char* name);
StructDef* enregistrer_struct(Node* decl_struct);
//void parcours_struct_def(Node* root);
StructChamps* trouver_champ(StructDef *struct_def, char* struct_name);
int taille_struct(char* struct_name);
Symbol *ajout_struct_var(Symbol *table[], char *name, char *struct_name);

Symbol * ajout_fonction(Symbol *table[], char *name , Type type);
#endif