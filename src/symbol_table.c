#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "symbol_table.h"
 
extern Symbol *tableGlobale[TAILLE_TABLE];
StructDef* structDefs = NULL;
int deplct = 0;

void init_table(Symbol *table[]) {
    for (int i = 0; i < 1008; i++) {
        table[i] = NULL;
    }
}
int hashage(char *str) {
    unsigned int h = 0;
    unsigned int k = 613;

    for (int i = 0; str[i] != '\0'; i++) {
        h = (k * h + (unsigned char)str[i]) % TAILLE_TABLE;
    }

    return h;
}
int type_et_taille(Node *n, Type *t, int *taille) {
    if (n == NULL) return 0;

    if (strcmp(n->ident, "int") == 0) {
        *t = TYPE_INT;
        *taille = 4;
        return 1;
    }
    else if (strcmp(n->ident, "char") == 0) {
        *t = TYPE_CHAR;
        *taille = 1;
        return 1;
    }
    else if (strcmp(n->ident, "void") == 0) {
        *t = TYPE_VOID;
        *taille = 0;
        return 1;
    }

    return 0;
}

/*
faire fonction recherche
puis faire fonction qui cherche global , local
puis exo6 pour les type ect 
*/
Symbol * recherche(Symbol *table[],char *name){
    int i = hashage(name);
    Symbol *tmp = table[i];
    while (tmp != NULL){
        if (strcmp(tmp->name, name) == 0){
            return tmp;
        }
        tmp = tmp->suivant;
    }
    return NULL;

}


Symbol *ajout(Symbol *table[], char *name, Type type){
    int i = hashage(name);
    Symbol *tmp = table[i];

    while (tmp != NULL){
        if (strcmp(tmp->name, name) == 0){
            return NULL;
        }
        tmp = tmp->suivant;
    }

    Symbol *nouv = malloc(sizeof(Symbol));
    if (nouv == NULL){
        return NULL;
    }

    nouv->name = strdup(name);
    nouv->is_function = 0;
    nouv->type = type;
    nouv->adresse = 0;
    nouv->struct_name = NULL;
    nouv->suivant = table[i];
    table[i] = nouv;

    return nouv;
}

Symbol * ajout_fonction(Symbol *table[], char *name , Type type){
    Symbol *s = ajout(table,name,type);
    if (s!=NULL){
        s->is_function = 1;
    }
    return s;
}

int ajout_globalTPC(Node *decls, Symbol *table[]) {
    if (decls == NULL || decls->label != declarations)
        return 0;
 
    for (Node *decl = decls->firstChild; decl != NULL; decl = decl->nextSibling) {
        if (decl->label != declaration) continue;
 
        Node *elem = decl->firstChild;
        if (elem == NULL) continue;
 
        if (elem->label == type) {
            Type symtype;
            int  taille = 0;
            if (!type_et_taille(elem, &symtype, &taille)) continue;
 
            for (Node *idNode = elem->firstChild; idNode != NULL; idNode = idNode->nextSibling) {
                if (idNode->label != id) continue;
                Symbol *s = ajout(table, idNode->ident, symtype);
                if (s != NULL) {
                    s->adresse = deplct;
                    deplct += taille;
                } else {
                    fprintf(stderr, "err sem ligne %d : %s identificateur deja declaree\n",idNode->lineno, idNode->ident);
                    exit(2);
                }
            }
        }
        else if (elem->label == structure) {

            Node *idN = elem->firstChild; /* id du nom de la struct */
            if (idN == NULL || idN->label != id) continue;
 
            char *sname = idN->ident;
 
            int has_contenu = 0;
            for (Node *c = idN->nextSibling; c != NULL; c = c->nextSibling) {
                if (c->label == contenustruct) { 
                    has_contenu = 1; break; 
                }
            }
            if (has_contenu) {
                enregistrer_struct(decl);
                continue;
 
            }
            
            StructDef *sd = trouver_struct(sname);

            if (sd == NULL) {
                fprintf(stderr, "err sem ligne %d : structure %s non declaree\n", idN->lineno,sname);
                exit(2);
            }

            int sz = sd->taille;
 
            for (Node *varId = idN->nextSibling; varId != NULL; varId = varId->nextSibling) {
                if (varId->label != id) continue;
                Symbol *s = ajout_struct_var(table, varId->ident, (char*)sname);
                if (s != NULL) {
                    s->adresse = deplct;
                    deplct += sz;
                } else {
                    fprintf(stderr, "err sem ligne %d: %s identificateur deja declaree\n",varId->lineno, varId->ident);
                    exit(2);
                }
            }
        }
    }
    return 1;
}

void ajout_parametres(Node *params, Symbol *tableLocale[]) {
    if (params == NULL || params->label != parameters)
        return;
 
    for (Node *typeNode = params->firstChild; typeNode != NULL; typeNode = typeNode->nextSibling) {
        if (typeNode->label == type) {
            if (typeNode->firstChild != NULL && typeNode->firstChild->label == structure) {
                Node *structNode = typeNode->firstChild;
                Node *structNameNode = structNode->firstChild;

                if (structNameNode == NULL || structNameNode->label != id)
                    continue;

                StructDef *sd = trouver_struct(structNameNode->ident);

                if (sd == NULL) {
                    fprintf(stderr, "err sem ligne %d : structure %s non declaree\n", structNameNode->lineno,structNameNode->ident);
                    exit(2);
                }

                for (Node *idNode = structNode->nextSibling; idNode != NULL; idNode = idNode->nextSibling) {
                    if (idNode->label != id)
                        continue;

                    Symbol *s = ajout_struct_var(tableLocale, idNode->ident, structNameNode->ident);

                    if (s != NULL) {
                        s->adresse = deplct;
                        deplct += sd->taille;
                    } else {
                        fprintf(stderr, "err sem ligne %d : %s parameter deja declaree\n", idNode->lineno,idNode->ident);
                        exit(2);
                    }
                }

                continue;
            }
            Type symtype;
            int  taille = 0;
            if (!type_et_taille(typeNode, &symtype, &taille)) continue;
 
            for (Node *idNode = typeNode->firstChild; idNode != NULL; idNode = idNode->nextSibling) {
                if (idNode->label != id) continue;
                Symbol *s = ajout(tableLocale, idNode->ident, symtype);
                if (s != NULL) {
                    s->adresse = deplct;
                    deplct += taille;
                } else {
                    fprintf(stderr, "err sem ligne %d : %s parameter deja declaree\n", idNode->lineno,idNode->ident);
                    exit(2);
                }
            }
        }
        else if (typeNode->label == structure) {
            Node *idN = typeNode->firstChild;
            if (idN == NULL || idN->label != id) continue;
            char *sname = idN->ident;
            StructDef  *sd    = trouver_struct(sname);
            int         sz    = (sd != NULL) ? sd->taille : 0;
 
            for (Node *varId = idN->nextSibling; varId != NULL; varId = varId->nextSibling) {
                if (varId->label != id) continue;
                Symbol *s = ajout_struct_var(tableLocale, varId->ident, (char*)sname);
                if (s != NULL) {
                    s->adresse = deplct;
                    deplct += sz;
                } else {
                    fprintf(stderr, "err sem %d : %s parameter deja declaree\n",varId->lineno, varId->ident);
                    exit(2);
                }
            }
        }
        else if (typeNode->label == type) {
        }
    }
}



void ajout_variables_locales(Node *decls, Symbol *tableLocale[]) {
    if (decls == NULL || decls->label != declarations)
        return;
 
    for (Node *decl = decls->firstChild; decl != NULL; decl = decl->nextSibling) {
        if (decl->label != declaration) continue;
 
        Node *elem = decl->firstChild;
        if (elem == NULL) continue;
 
        if (elem->label == type) {
            Type symtype;
            int  taille = 0;
            if (!type_et_taille(elem, &symtype, &taille)) continue;
 
            for (Node *idNode = elem->firstChild; idNode != NULL; idNode = idNode->nextSibling) {
                if (idNode->label != id) continue;
                Symbol *s = ajout(tableLocale, idNode->ident, symtype);
                if (s != NULL) {
                    s->adresse = deplct;
                    deplct += taille;
                } else {
                    fprintf(stderr, "Err sem ligne %d : variable %s deja declaree\n", idNode->lineno,idNode->ident);
                    exit(2);
                }
            }
        }
        else if (elem->label == structure) {
            Node *idN = elem->firstChild;
            if (idN == NULL || idN->label != id) continue;
 
            char *sname = idN->ident;
             int has_contenu = 0;
            for (Node *c = idN->nextSibling; c != NULL; c = c->nextSibling) {
                if (c->label == contenustruct) { has_contenu = 1; break; }
            }
            if (has_contenu) {
                enregistrer_struct(decl);
                continue;
            }
            StructDef *sd = trouver_struct(sname);

            if (sd == NULL) {
                fprintf(stderr, "err sem ligne %d: structure %s non declaree\n", idN->lineno,sname);
                exit(2);
            }

            int sz = sd->taille;
            for (Node *varId = idN->nextSibling; varId != NULL; varId = varId->nextSibling) {
                if (varId->label != id) continue;
                Symbol *s = ajout_struct_var(tableLocale, varId->ident, (char*)sname);
                if (s != NULL) {
                    s->adresse = deplct;
                    deplct += sz;
                } else {
                    fprintf(stderr, "Err sem ligne %d : variable %s deja declaree\n", varId->lineno,varId->ident);
                    exit(2);
                }
            }
        }
    }
}


void construire_table_fonction(Node *f) {
    if (f == NULL || f->label != function) 
        return;

    LocalTableNode *tableLocale = malloc(sizeof(LocalTableNode));
    init_table(tableLocale->table);
    deplct = 0;

    Node *head = NULL;
    Node *corps = NULL;
    Node *params = NULL;
    Node *decls = NULL;
    Node *nomFonction = NULL;
    Node *typeRetour = NULL; 

    for (Node *elem = f->firstChild; elem != NULL; elem = elem->nextSibling) {
        if (elem->label == heading) head = elem;
        else if (elem->label == body) 
            corps = elem;
    }

    if (head != NULL) {
        for (Node *elem = head->firstChild; elem != NULL; elem = elem->nextSibling) {
            if (elem->label == id && nomFonction == NULL)
                nomFonction = elem;
            else if (elem->label == parameters)
                params = elem;
            else if (elem->label == type)
                typeRetour = elem; 
        }
    }


    if (nomFonction != NULL) {
        Type type = TYPE_VOID;
        int taille = 0;
        
    
        char *structRetour = NULL;

        if (typeRetour != NULL) {
            Node *structNode = NULL;

            if (typeRetour->label == structure) {
                structNode = typeRetour;
            }
            else if (typeRetour->firstChild != NULL && typeRetour->firstChild->label == structure) {
                structNode = typeRetour->firstChild;
            }

            if (structNode != NULL) {
                Node *structNameNode = structNode->firstChild;

                if (structNameNode == NULL || structNameNode->label != id) {
                    fprintf(stderr, "err sem ligne %d : type retour struct invalide\n",structNameNode->lineno);
                    exit(2);
                }

                StructDef *sd = trouver_struct(structNameNode->ident);

                if (sd == NULL) {
                    fprintf(stderr, "err sem ligne %d : structure %s non declaree\n",structNameNode->lineno ,structNameNode->ident);
                    exit(2);
                }

                type = TYPE_STRUCT;
                taille = sd->taille;
                structRetour = structNameNode->ident;
            }
            else if (typeRetour->firstChild != NULL) {
                type_et_taille(typeRetour->firstChild, &type, &taille);
            }
            else {
                type_et_taille(typeRetour, &type, &taille);
            }
        }
        

        Symbol *aj = ajout_fonction(tableGlobale, nomFonction->ident, type);
        if (aj == NULL){
            fprintf(stderr,"err sem ligne %d : %s fonction deja delcaree\n",nomFonction->lineno,nomFonction->ident);
            exit(2);
        }
        if (type == TYPE_STRUCT && structRetour != NULL) {
            aj->struct_name = strdup(structRetour);
        }
    }

    if (corps != NULL) {
        for (Node *elem = corps->firstChild; elem != NULL; elem = elem->nextSibling) {
            if (elem->label == declarations) {
                decls = elem;
                break;
            }
        }
    }

    if (nomFonction != NULL)
        tableLocale->functionName = strdup(nomFonction->ident);
    else
        tableLocale->functionName = strdup("nom de fonction inconnu");
        
    ajout_parametres(params, tableLocale->table);
    ajout_variables_locales(decls, tableLocale->table);

    tableLocale->next = localTables;
    localTables = tableLocale;
}
void afficher_table(Symbol *table[]) {
    for (int i = 0; i < TAILLE_TABLE; i++) {
        Symbol *tmp = table[i];
        while (tmp != NULL) {
            if (tmp->type == TYPE_STRUCT)
                printf("nom =%s, type = struct (%s) adresse =%d\n",tmp->name,tmp->struct_name,tmp->adresse);
            else
                printf("  nom=%s type=%d adresse=%d\n", tmp->name, tmp->type, tmp->adresse);
            tmp = tmp->suivant;
        }
    }
}

void afficher_table_locale(){
    LocalTableNode* curr = localTables;
    if (curr == NULL){
        printf("Aucune table locale\n");
        return;
    }
    while (curr != NULL){
        printf("Table de la fonction : %s\n",curr->functionName);
        afficher_table(curr->table);
        curr = curr->next;
    }
}

void parcours_fonctions(Node *n) {
    if (n == NULL) 
        return;

    if (n->label == function) {
        construire_table_fonction(n);
    }

    parcours_fonctions(n->firstChild);
    parcours_fonctions(n->nextSibling);
}


Symbol** get_local_table(char* function_name){
    LocalTableNode *curr = localTables;
    while (curr != NULL){
        if (strcmp(curr->functionName,function_name) == 0)
            return curr->table;
        curr = curr->next;
    }
    return NULL;
} 
Type get_type_field_dot(Node *n, Symbol **tableLocale, Symbol **tableGlobale, char **struct_name_out) {
    if (n == NULL) {
        *struct_name_out = NULL;
        return TYPE_VOID;
    }

    if (n->label == id) {
        Symbol *s = NULL;

        if (tableLocale != NULL)
            s = recherche(tableLocale, n->ident);

        if (s == NULL && tableGlobale != NULL)
            s = recherche(tableGlobale, n->ident);

        if (s == NULL) {
            fprintf(stderr, "err sem ligne %d : variable %s non declaree\n", n->lineno,n->ident);
            exit(2);
        }
        if (s->is_function == 1){
                fprintf(stderr,"err sem ligne %d : fonction utilise comme varaible\n",n->lineno);
                exit(2);
        }

        if (s->type == TYPE_STRUCT)
            *struct_name_out = s->struct_name;
        else
            *struct_name_out = NULL;

        return s->type;
    }

    if (n->label == field_dot) {
        Node *left = n->firstChild;
        Node *fieldName = left->nextSibling;

        char *left_struct_name = NULL;
        Type left_type = get_type_field_dot(left, tableLocale, tableGlobale, &left_struct_name);

        if (left_type != TYPE_STRUCT) {
            fprintf(stderr, "err sem  ligne %d : acces champ sur non structure\n",left->lineno);
            exit(2);
        }

        StructDef *sd = trouver_struct(left_struct_name);

        if (sd == NULL) {
            fprintf(stderr, "err sem ligne %d : structure %s inconnue\n", left->lineno,left_struct_name);
            exit(2);
        }

        StructChamps *champ = trouver_champ(sd, fieldName->ident);

        if (champ == NULL) {
            fprintf(stderr, "err sem ligne %d : champ %s inexistant\n", fieldName->lineno,fieldName->ident);
            exit(2);
        }

        *struct_name_out = champ->struct_name;

        return champ->type;
    }

    *struct_name_out = NULL;
    return TYPE_VOID;
}

Type get_type_expression(Node* n, Symbol** tableLocale, Symbol** tableGlobale){
    if (n == NULL)
        return TYPE_VOID;
    
    if (n->label == num)
        return TYPE_INT;
    if (n->label == character)
        return TYPE_CHAR;
    if (n->label == id) {
        Symbol *s = NULL;
        if (tableLocale != NULL)
            s = recherche(tableLocale,n->ident);
        if (s == NULL && tableGlobale != NULL)
            s = recherche(tableGlobale,n->ident);
        if (s != NULL){
            	if (s->is_function == 1){
                    fprintf(stderr,"err sem ligne %d : fonction utilise comme varaible\n",n->lineno);
                    exit(2);
		}
        return s->type;
        }
        fprintf(stderr,"err sem ligne %d : variable/parametre pas declarer %s \n",n->lineno,n->ident);
        exit(2);
    }
    if (n->label == call_function) {
        Node *id_node = n->firstChild;
        Symbol *s = recherche(tableGlobale, id_node->ident);

        if (s == NULL || !s->is_function) {
            fprintf(stderr, "err sem ligne %d : fonction %s non declaree\n", id_node->lineno, id_node->ident);
            exit(2);
        }
        return s->type;
    }

    if (n->label == field_dot) {
        char *struct_name = NULL;
        return get_type_field_dot(n, tableLocale, tableGlobale, &struct_name);
    }

    if (n->label == positif || n->label == negatif) {
        Type t = get_type_expression(n->firstChild, tableLocale, tableGlobale);

        if (t == TYPE_VOID) {
            fprintf(stderr, "err sem ligne %d : operation sur expression void\n", n->lineno);
            exit(2);
        }

        if (t == TYPE_STRUCT) {
            fprintf(stderr, "err sem ligne %d : operation sur structure\n", n->lineno);
            exit(2);
        }

        return TYPE_INT;
    }

    if (n->label == add || n->label == sub || n->label == divstar ||
        n->label == compare || n->label == order ||
        n->label == and_ || n->label == or_) {

        Type t1 = get_type_expression(n->firstChild, tableLocale, tableGlobale);
        Type t2 = get_type_expression(n->firstChild->nextSibling, tableLocale, tableGlobale);

        if (t1 == TYPE_VOID || t2 == TYPE_VOID) {
            fprintf(stderr, "err sem ligne %d : operation avec expression void\n", n->lineno);
            exit(2);
        }

        if (t1 == TYPE_STRUCT || t2 == TYPE_STRUCT) {
            fprintf(stderr, "err sem ligne %d : operation avec structure\n", n->lineno);
            exit(2);
        }

        return TYPE_INT;
    }

    if (n->label == not_) {
        Type t = get_type_expression(n->firstChild, tableLocale, tableGlobale);

        if (t == TYPE_VOID) {
            fprintf(stderr, "err sem ligne %d : negation d'une expression void\n", n->lineno);
            exit(2);
        }

        if (t == TYPE_STRUCT) {
            fprintf(stderr, "err sem ligne %d : negation d'une structure\n", n->lineno);
            exit(2);
        }

        return TYPE_INT;
    }

    if (n->label == condition) {
        Type t = get_type_expression(n->firstChild, tableLocale, tableGlobale);

        if (t == TYPE_VOID) {
            fprintf(stderr, "err sem ligne %d : condition de type void\n", n->lineno);
            exit(2);
        }

        if (t == TYPE_STRUCT) {
            fprintf(stderr, "err sem ligne %d : condition de type structure\n", n->lineno);
            exit(2);
        }

        return TYPE_INT;
    }

    return TYPE_INT;
}


void verif_existence_main(Node *n){
    int is_main = 0;
    if (n==NULL){
        return;
    }
    Node *fNode = NULL;
    for (Node *s = n->firstChild;s!=NULL;s=s->nextSibling){
        if (s->label  == functions){
            fNode = s;
            break;
        }
    }
    if (fNode == NULL){
        fprintf(stderr, "err sem ligne 0 : pas de main\n");
        exit(2);
    }
    for (Node *f = fNode->firstChild;f!=NULL;f = f->nextSibling){
        if (f->label != function){
            continue;
        }
        Node *h = f->firstChild;
        if (h==NULL){
            continue;
        }
        if (h->label!=heading){
            continue;
        }
        Node *nomF = NULL;
        Node *typeRetour = NULL;
        Node *param = NULL;
        for (Node *elem = h->firstChild;elem!=NULL;elem = elem->nextSibling){
            if (elem->label == id  && nomF == NULL){
                nomF = elem;
            }
            else if (elem->label == type){
                typeRetour = elem;
            }
            else if (elem->label == parameters){
                param = elem;
            }

        }
        if (nomF != NULL && strcmp(nomF->ident,"main")==0){
            is_main++;
            Type main_type = TYPE_VOID;
            int taille = 0;
            int is_good_type = 0;
            if (typeRetour != NULL){
                if (typeRetour->firstChild != NULL && typeRetour->firstChild->label == type){
                    is_good_type = type_et_taille(typeRetour->firstChild,&main_type,&taille);
                }
                else {
                    is_good_type = type_et_taille(typeRetour,&main_type,&taille);
                }
            }
            if (!is_good_type || main_type != TYPE_INT){
                fprintf(stderr,"err sem ligne %d: main doit retourner int\n",nomF->lineno);
                exit(2);
            }
            if (param==NULL || param->firstChild!=NULL){
                fprintf(stderr,"err sem ligne %d : main doit prendre void en param\n",nomF->lineno);
                exit(2);
            }
        }
    }
    if (is_main==0){
        fprintf(stderr,"err sem ligne 0: il n'y a pas de main\n");
        exit(2);
    }
    if (is_main>1){
        fprintf(stderr,"err sem ligne 0 : plusieurs main declaree\n");
        exit(2);
    }

}
int verif_return_noeud(Node *n, Type typeRetour, Symbol **tableLocale) {
    int trouve_return = 0;

    if (n == NULL) {
        return 0;
    }

    if (n->label == return_) {
        trouve_return = 1;
        if (typeRetour == TYPE_VOID && n->firstChild != NULL) {
            fprintf(stderr, "err sem ligne %d : return avec valeur dans une fonction void\n", n->lineno);
            exit(2);
        }

        if (typeRetour != TYPE_VOID && n->firstChild == NULL) {
            fprintf(stderr, "err sem ligne %d : return sans valeur dans une fonction non void\n", n->lineno);
            exit(2);
        }
        if (n->firstChild != NULL) {
            Type typeExpr = get_type_expression(n->firstChild, tableLocale, tableGlobale);

            if (typeExpr == TYPE_VOID) {
                fprintf(stderr, "err sem ligne %d : return d'une expression void\n", n->lineno);
                exit(2);
            }

            if (typeRetour != TYPE_STRUCT && typeExpr == TYPE_STRUCT) {
                fprintf(stderr, "err sem ligne %d : return d'une structure dans une fonction non-struct\n", n->lineno);
                exit(2);
            }

            if (typeRetour == TYPE_STRUCT && typeExpr != TYPE_STRUCT) {
                fprintf(stderr, "err sem ligne %d : return non-struct dans une fonction struct\n", n->lineno);
                exit(2);
            }
            if (typeRetour == TYPE_CHAR && typeExpr == TYPE_INT) {
                fprintf(stderr, "warning ligne %d : return d'un int dans une fonction char\n", n->lineno);
            }
        }
        
    }
    if (verif_return_noeud(n->firstChild, typeRetour, tableLocale))
        trouve_return = 1;

    if (verif_return_noeud(n->nextSibling, typeRetour, tableLocale))
        trouve_return = 1;

    return trouve_return;
}


void verif_return_fonctions(Node *root) {
    if (root == NULL) {
        return;
    }

    Node *fNode = NULL;

    for (Node *s = root->firstChild; s != NULL; s = s->nextSibling) {
        if (s->label == functions) {
            fNode = s;
            break;
        }
    }

    if (fNode == NULL) {
        return;
    }

    for (Node *f = fNode->firstChild; f != NULL; f = f->nextSibling) {
        if (f->label != function) {
            continue;
        }

        Node *h = f->firstChild;

        if (h == NULL || h->label != heading) {
            continue;
        }

        Node *nomF = NULL;
        Node *typeRetourNode = NULL;

        for (Node *elem = h->firstChild; elem != NULL; elem = elem->nextSibling) {
            if (elem->label == id && nomF == NULL) {
                nomF = elem;
            }
            else if (elem->label == type) {
                typeRetourNode = elem;
            }
        }

        if (nomF == NULL || typeRetourNode == NULL) {
            continue;
        }

        Type typeRetour = TYPE_VOID;
        int taille = 0;
        int ok = 0;

        if (typeRetourNode->firstChild != NULL && typeRetourNode->firstChild->label == type) {
            ok = type_et_taille(typeRetourNode->firstChild, &typeRetour, &taille);
        }
        else {
            ok = type_et_taille(typeRetourNode, &typeRetour, &taille);
        }

        if (!ok) {
            continue;
        }

        Node *bodyNode = h->nextSibling;

        if (bodyNode == NULL) {
            continue;
        }
        Symbol **tableLocale = get_local_table(nomF->ident);
        verif_return_noeud(bodyNode, typeRetour, tableLocale);


    }
}

Symbol *ajout_struct_var(Symbol *table[], char *name, char *struct_name) {
    Symbol *s = ajout(table, name, TYPE_STRUCT);
    if (s != NULL)
        s->struct_name = strdup(struct_name);
    return s;
}

StructDef* trouver_struct(char *name) {
    StructDef *curr = structDefs;
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0)
            return curr;
        curr = curr->next;
    }
    return NULL;
}


StructChamps* trouver_champ(StructDef *sd, char *field_name) {
    if (sd == NULL) return NULL;
    StructChamps *tmp = sd->champs;
    while (tmp != NULL) {
        if (strcmp(tmp->name, field_name) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

int taille_struct(char *struct_name) {
    StructDef *sd = trouver_struct(struct_name);
    if (sd == NULL) return 0;
    return sd->taille;
}

StructDef *enregistrer_struct(Node *decl_struct_node) {

    if (decl_struct_node == NULL || decl_struct_node->label != declaration)
        return NULL;
 
    Node *sNode = decl_struct_node->firstChild;
    if (sNode == NULL || sNode->label != structure)
        return NULL;
 
    Node *idNode = sNode->firstChild;
    if (idNode == NULL || idNode->label != id)
        return NULL;

    Node *csNode = NULL;
    for (Node *c = idNode->nextSibling; c != NULL; c = c->nextSibling) {
        if (c->label == contenustruct) {
            csNode = c;
            break;
        }
    }
    if (csNode == NULL)
        return NULL;
 
    char *struct_name = idNode->ident;
 
    if (trouver_struct(struct_name) != NULL) {
        fprintf(stderr, "err sem ligne %d : struct %s déjà définie\n", idNode->lineno,struct_name);
        exit(2);
    }
 
    StructDef *sd = malloc(sizeof(StructDef));
    sd->name = strdup(struct_name);
    sd->champs = NULL;
    sd->taille = 0;
    sd->next = NULL;
 
    int offset = 0;
 
    for (Node *fieldGroup = csNode->firstChild; fieldGroup != NULL; fieldGroup = fieldGroup->nextSibling) {
 
        if (fieldGroup->label == type) {
            Type ftype;
            int  ftaille = 0;
            if (!type_et_taille(fieldGroup, &ftype, &ftaille)) {
                if (fieldGroup->firstChild != NULL && fieldGroup->firstChild->label == type) {
                    type_et_taille(fieldGroup->firstChild, &ftype, &ftaille);
                }
            }

            for (Node *varId = fieldGroup->firstChild; varId != NULL; varId = varId->nextSibling) {
                if (varId->label != id) continue;
                if (trouver_champ(sd, varId->ident) != NULL) {
                    fprintf(stderr, "err sem ligne %d : champ %s deja declare dans struct %s\n",varId->lineno, varId->ident, sd->name);
                    exit(2);
                }
                StructChamps *sf = malloc(sizeof(StructChamps));
                sf->name = strdup(varId->ident);
                sf->offset = offset;
                sf->type = ftype;
                sf->struct_name = NULL;
                sf->next = NULL;
 
                offset += ftaille;
 
                if (sd->champs == NULL) {
                    sd->champs = sf;
                } else {
                    StructChamps *last = sd->champs;
                    while (last->next != NULL) last = last->next;
                    last->next = sf;
                }
            }
        }
        else if (fieldGroup->label == structure) {

            Node *sNameNode = fieldGroup->firstChild;
            if (sNameNode == NULL || sNameNode->label != id) continue;
 
            char *inner_struct_name = sNameNode->ident;
            StructDef *inner_sd = trouver_struct(inner_struct_name);

            if (inner_sd == NULL) {
                fprintf(stderr, "err sem ligne %d : structure %s non declaree\n", sNameNode->lineno,inner_struct_name);
                exit(2);
            }

            int inner_size = inner_sd->taille;
            for (Node *varId = sNameNode->nextSibling; varId != NULL; varId = varId->nextSibling) {
                if (varId->label != id)
                    continue;
                if (trouver_champ(sd, varId->ident) != NULL) {
                    fprintf(stderr, "err sem ligne %d: champ %s deja declare dans struct %s\n",varId->lineno,varId->ident, sd->name);
                    exit(2);
                }
                StructChamps *s = malloc(sizeof(StructChamps));
                s->name = strdup(varId->ident);
                s->offset = offset;
                s->type = TYPE_STRUCT;
                s->struct_name = strdup(inner_struct_name);
                s->next = NULL;
 
                offset += inner_size;
 
                if (sd->champs == NULL) {
                    sd->champs = s;
                } else {
                    StructChamps *last = sd->champs;
                    while (last->next != NULL) last = last->next;
                    last->next = s;
                }
            }
        }
    }

    sd->taille = offset;
    sd->next = structDefs;
    structDefs = sd;
    return sd;
}
