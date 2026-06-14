#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include <string.h>
#include "symbol_table.h"
extern Node* root;
extern Symbol *tableGlobale[TAILLE_TABLE];
Symbol **tableLocale = NULL;

int taille_symbol(Symbol *s) {
    if (s == NULL)
        return 0;

    if (s->is_function)
        return 0;
	
    if (s->type == TYPE_INT)
        return 4;

    if (s->type == TYPE_CHAR)
        return 1;

    if (s->type == TYPE_STRUCT)
        return taille_struct(s->struct_name);

    return 0;
}

int adresse_locale(Symbol *s) {
    return s->adresse + taille_symbol(s);
}
int number_elem_adr(Symbol *table[]) {
    int sum = 0;

    if (table == NULL)
        return 0;

    for (int i = 0; i < TAILLE_TABLE; i++) {
        Symbol *tmp = table[i];

        while (tmp != NULL) {
            sum += taille_symbol(tmp);
            tmp = tmp->suivant;
        }
    }

    return sum;
}

typedef struct {
    Symbol *base;
    int is_local;
    int offset;
    Type type;
    char *struct_name;
} LValueInfo;


LValueInfo resolve_lvalue(Node *n) {
    LValueInfo lv;

    lv.base = NULL;
    lv.is_local = 0;
    lv.offset = 0;
    lv.type = TYPE_VOID;
    lv.struct_name = NULL;

    if (n == NULL) {
        fprintf(stderr, "err sem ligne %d: lvalue invalide \n",n->lineno);
        exit(2);
    }

    if (n->label == id) {
        Symbol *s = NULL;

        if (tableLocale != NULL) {
            s = recherche(tableLocale, n->ident);

            if (s != NULL)
                lv.is_local = 1;
        }

        if (s == NULL) {
            s = recherche(tableGlobale, n->ident);
        }

        if (s == NULL) {
            fprintf(stderr, "err sem ligne %d : variable %s non declaree\n", n->lineno,n->ident);
            exit(2);
        }
		if (s->is_function == 1){
			fprintf(stderr,"err sem ligne %d : fonction utilise comme varaible\n",n->lineno);
			exit(2);
		}

        lv.base = s;
        lv.type = s->type;

        if (s->type == TYPE_STRUCT)
            lv.struct_name = s->struct_name;

        return lv;
    }

    if (n->label == field_dot) {
        Node *left = n->firstChild;
        Node *fieldName = left->nextSibling;

        LValueInfo base = resolve_lvalue(left);

        if (base.type != TYPE_STRUCT) {
            fprintf(stderr, "err sem ligne %d : acces champ sur une variable non structure\n",n->lineno);
            exit(2);
        }

        StructDef *sd = trouver_struct(base.struct_name);

        if (sd == NULL) {
            fprintf(stderr, "err sem ligne %d : structure %s inconnue\n",n->lineno,base.struct_name);
            exit(2);
        }

        StructChamps *champ = trouver_champ(sd, fieldName->ident);

        if (champ == NULL) {
            fprintf(stderr, "err sem ligne %d : champ %s inexistant dans struct %s\n",n->lineno,fieldName->ident, sd->name);
            exit(2);
        }
        base.offset += champ->offset;
        base.type = champ->type;
        base.struct_name = champ->struct_name;
        return base;
    }

    fprintf(stderr, "err sem ligne %d : lvalue invalide\n",n->lineno);
    exit(2);
}
void charger_lvalue(FILE *f, LValueInfo lv) {
    if (lv.type == TYPE_STRUCT) {
        fprintf(stderr, "err sem  ligne 0 : une structure complete ne peut pas etre utilisee comme expression simple\n");
        exit(2);
    }

    if (lv.is_local) {
        int adr = lv.base->adresse + taille_symbol(lv.base) - lv.offset;

        if (lv.type == TYPE_CHAR) {
            fprintf(f, "mov rax, 0\n");
            fprintf(f, "mov al, byte [rbp - %d]\n", adr);
        } else {
            fprintf(f, "mov eax, dword [rbp - %d]\n", adr);
        }
    } else {
        int adr = lv.base->adresse + lv.offset;

        if (lv.type == TYPE_CHAR) {
            fprintf(f, "mov rax, 0\n");
            fprintf(f, "mov al, byte [global_vars + %d]\n", adr);
        } else {
            fprintf(f, "mov eax, dword [global_vars + %d]\n", adr);
        }
    }

    fprintf(f, "push rax\n\n");
}
void stocker_lvalue(FILE *f, LValueInfo lv) {
    if (lv.type == TYPE_STRUCT) {
        fprintf(stderr, "err sem ligne 0 : affectation directe d'une structure non geree\n");
        exit(2);
    }

    if (lv.is_local) {
        int adr = lv.base->adresse + taille_symbol(lv.base) - lv.offset;

        if (lv.type == TYPE_CHAR)
            fprintf(f, "mov byte [rbp - %d], al\n\n", adr);
        else
            fprintf(f, "mov dword [rbp - %d], eax\n\n", adr);
    } else {
        int adr = lv.base->adresse + lv.offset;

        if (lv.type == TYPE_CHAR)
            fprintf(f, "mov byte [global_vars + %d], al\n\n", adr);
        else
            fprintf(f, "mov dword [global_vars + %d], eax\n\n", adr);
    }
}
void translate_aux(Node* tree, FILE* f){
	Node * n1;
	Node * n2;
	Node * n3;
	static int countf = 0;
	static int countc= 0;
	if (tree == NULL)
		return;
	switch (tree->label){
		case num:
			fprintf(f, "mov rax, %s\n",tree->ident);
			fprintf(f, "push rax\n\n");
			break;
		case character:
			fprintf(f,"mov rax, %d\n",tree->ident[0]);
			fprintf(f,"push rax\n\n");
			break;
		case id:{
			Symbol * s =NULL;
			int is_local = 0;

			if (tableLocale != NULL){
				s = recherche(tableLocale,tree->ident);
				if (s != NULL) {
					is_local = 1;
				}
			}
			if (s == NULL){
				s = recherche(tableGlobale,tree->ident);
			}

			if (s == NULL){
				fprintf(stderr, "err sem ligne %d : Variable non déclaré\n",tree->firstChild->lineno);
				exit(2);
			}
			if (s->is_function ==1){
				fprintf(stderr,"err sem ligne %d : fonction utilisee comme variable\n",tree->firstChild->lineno);
				exit(2);
			}
			
			if (is_local){
				if (s->type == TYPE_CHAR) {
					fprintf(f, "mov rax, 0\n");
					fprintf(f, "mov al, byte [rbp - %d]\n", adresse_locale(s));
				}
				else {
					fprintf(f, "mov eax, dword [rbp - %d]\n", adresse_locale(s));
				}
			}
			else {
				if (s->type == TYPE_CHAR) {
					fprintf(f, "mov rax, 0\n");
					fprintf(f, "mov al, byte [global_vars + %d]\n", s->adresse);
				}
				else {
					fprintf(f, "mov eax, dword [global_vars + %d]\n", s->adresse);
				}
			}

			fprintf(f, "push rax\n\n");
			break;
		}
		case positif:
    		translate_aux(tree->firstChild, f);
    		break;

		case negatif:
			translate_aux(tree->firstChild, f);
			fprintf(f, "pop rax\n");
			fprintf(f, "neg rax\n");
			fprintf(f, "push rax\n\n");
    		break;
		case add:
			translate_aux(tree->firstChild,f);
			translate_aux(tree->firstChild->nextSibling,f);
			fprintf(f, "pop rcx\n");
			fprintf(f, "pop rax\n");
			fprintf(f, "add rax, rcx\n");
			fprintf(f, "push rax\n\n");
			break;
		case sub:
			translate_aux(tree->firstChild,f);
			translate_aux(tree->firstChild->nextSibling,f);
			fprintf(f, "pop rcx\n");
			fprintf(f, "pop rax\n");
			fprintf(f, "sub rax, rcx\n");
			fprintf(f, "push rax\n\n");
			break;
		case assign:
			n1 = tree->firstChild;
			n2 = n1->nextSibling;

			if (n1->label == field_dot) {
				LValueInfo lv = resolve_lvalue(n1);

				Type type_droite = get_type_expression(n2, tableLocale, tableGlobale);

				if (lv.type == TYPE_CHAR && type_droite == TYPE_INT) {
					fprintf(stderr, "warning ligne %d : affectation d'un int a un type char\n", n1->lineno);
				}
				translate_aux(n2, f);
				fprintf(f, "pop rax\n");

				stocker_lvalue(f, lv);
				break;
			}
			Symbol* s_assign = NULL;
			int is_local_assign = 0;

			if (tableLocale != NULL){
				s_assign = recherche(tableLocale,n1->ident);
				if (s_assign != NULL){
					is_local_assign = 1;
				}
			}

			if (s_assign == NULL){
				s_assign = recherche(tableGlobale,n1->ident);
			}
			if (s_assign == NULL){
				fprintf(stderr," err sem ligne %d : assign a une variable non declaré\n",n1->lineno);
				exit(2);
			}
			if (s_assign ->is_function){
				fprintf(stderr,"err sem ligne %d : fonction utilise comme variable\n",n1->lineno);
				exit(2);
			}

			Type type_gauche = s_assign->type;
			Type type_droite = get_type_expression(n2,tableLocale,tableGlobale);
			if (type_droite == TYPE_VOID) {
			fprintf(stderr, "err sem ligne %d : affectation d'une expression void\n", n1->lineno);
			exit(2);
			}

			if (type_gauche != TYPE_STRUCT && type_droite == TYPE_STRUCT) {
				fprintf(stderr, "err sem ligne %d : affectation d'une structure vers un non-struct\n", n1->lineno);
				exit(2);
			}

			if (type_gauche == TYPE_STRUCT && type_droite != TYPE_STRUCT) {
				fprintf(stderr, "err sem ligne %d : affectation d'un non-struct vers une structure\n", n1->lineno);
				exit(2);
			}
			if (type_gauche == TYPE_CHAR && type_droite == TYPE_INT ){
				fprintf(stderr, "warning ligne %d : affectation d'un int a un type char : %s\n",n1->lineno,n1->ident);
			}
			translate_aux(n2,f);
			fprintf(f,"pop rax\n");

			if (is_local_assign){
				if (s_assign->type == TYPE_CHAR)
					fprintf(f, "mov byte [rbp - %d], al\n\n", adresse_locale(s_assign));
				else
					fprintf(f, "mov dword [rbp - %d], eax\n\n", adresse_locale(s_assign));
				}
			else {
				if (s_assign->type == TYPE_CHAR)
					fprintf(f, "mov byte [global_vars + %d], al\n\n", s_assign->adresse);
				else
					fprintf(f, "mov dword [global_vars + %d], eax\n\n", s_assign->adresse);
				}
			break;


		case if_: {
				n1 = tree->firstChild;         
				n2 = n1->nextSibling;          
				n3 = n2->nextSibling;       
				countf++;
				int if_actuel = countf;
				Type type_cond = get_type_expression(n1, tableLocale, tableGlobale);

				if (type_cond == TYPE_VOID) {
					fprintf(stderr, "err sem ligne %d : condition de type void\n", n1->lineno);
					exit(2);
				}

				if (type_cond == TYPE_STRUCT) {
					fprintf(stderr, "err sem ligne %d : condition de type structure\n", n1->lineno);
					exit(2);
				}
				translate_aux(n1, f);
				fprintf(f, "pop rax\n");
				fprintf(f, "cmp rax, 0\n");
				fprintf(f, "je if_faux%d\n", if_actuel);
				translate_aux(n2, f); 
					
				if (n3 == NULL) {
					fprintf(f, "if_faux%d:\n", if_actuel);
				} 
				else {
					fprintf(f, "jmp if_fin%d\n",if_actuel); 

					fprintf(f, "if_faux%d:\n", if_actuel);  
					translate_aux(n3, f);                   
						
					fprintf(f, "if_fin%d:\n", if_actuel);   
				}
				break;
			}
		case compare:
			translate_aux(tree->firstChild,f);
			translate_aux(tree->firstChild->nextSibling,f);
			fprintf(f,"pop rcx\n");
			fprintf(f,"pop rax\n");
			fprintf(f,"cmp rax,rcx\n");
			countc++;
			if (strcmp(tree->ident,"==") == 0)
				fprintf(f,"je vrai_c%d\n",countc);
			
			else if (strcmp(tree->ident,"!=") == 0)
				fprintf(f,"jne vrai_c%d\n",countc);
		
			fprintf(f,"faux_c%d:\n",countc);
			fprintf(f,"mov rax, 0\n");
			fprintf(f,"jmp fin_c%d\n",countc);
			fprintf(f,"vrai_c%d:\n",countc);
			fprintf(f,"mov rax,1\n");
			fprintf(f,"fin_c%d:\n",countc);
			fprintf(f,"push rax\n");
			break;

		case order:
			translate_aux(tree->firstChild,f);
			translate_aux(tree->firstChild->nextSibling,f);
			fprintf(f,"pop rcx\n");
			fprintf(f,"pop rax\n");
			fprintf(f,"cmp rax,rcx\n");
			countc++;
			if (strcmp(tree->ident,"<") == 0)
				fprintf(f,"jl vrai_c%d\n",countc);

			else if (strcmp(tree->ident,">") == 0)
				fprintf(f,"jg vrai_c%d\n",countc);
			
			else if (strcmp(tree->ident,"<=") == 0)
				fprintf(f,"jle vrai_c%d\n",countc);
			
			else if (strcmp(tree->ident,">=") == 0)
				fprintf(f,"jge vrai_c%d\n",countc);
			
			fprintf(f,"faux_c%d:\n",countc);
			fprintf(f,"mov rax, 0\n");
			fprintf(f,"jmp fin_c%d\n",countc);
			fprintf(f,"vrai_c%d:\n",countc);
			fprintf(f,"mov rax,1\n");
			fprintf(f,"fin_c%d:\n",countc);
			fprintf(f,"push rax\n");
			break;

		case and_: {
			countc++;
			int c = countc;
			translate_aux(tree->firstChild, f);
			fprintf(f, "pop rax\n");
			fprintf(f, "cmp rax, 0\n");
			fprintf(f, "je faux_and%d\n", c); 
			translate_aux(tree->firstChild->nextSibling, f);
			fprintf(f, "pop rax\n");
			fprintf(f, "cmp rax, 0\n");
			fprintf(f, "je faux_and%d\n", c);

			fprintf(f, "mov rax, 1\n");
			fprintf(f, "jmp fin_and%d\n", c);

			fprintf(f, "faux_and%d:\n", c);
			fprintf(f, "mov rax, 0\n");

			fprintf(f, "fin_and%d:\n", c);
			fprintf(f, "push rax\n\n");
			break;
		}

		case or_: {
			countc++;
			int c = countc;
			translate_aux(tree->firstChild, f);
			fprintf(f, "pop rax\n");
			fprintf(f, "cmp rax, 0\n");
			fprintf(f, "jne vrai_or%d\n", c); 

			translate_aux(tree->firstChild->nextSibling, f);
			fprintf(f, "pop rax\n");
			fprintf(f, "cmp rax, 0\n");
			fprintf(f, "jne vrai_or%d\n", c);

			fprintf(f, "mov rax, 0\n");
			fprintf(f, "jmp fin_or%d\n", c);

			fprintf(f, "vrai_or%d:\n", c);
			fprintf(f, "mov rax, 1\n");

			fprintf(f, "fin_or%d:\n", c);
			fprintf(f, "push rax\n\n");
			break;
		}

		case not_: {
			countc++;
			int c = countc;
			translate_aux(tree->firstChild, f);
			fprintf(f, "pop rax\n");
			fprintf(f, "cmp rax, 0\n");
			fprintf(f, "je vrai_not%d\n", c);

			fprintf(f, "mov rax, 0\n");
			fprintf(f, "jmp fin_not%d\n", c);
			
			fprintf(f, "vrai_not%d:\n", c);
			fprintf(f, "mov rax, 1\n");
			
			fprintf(f, "fin_not%d:\n", c);
			fprintf(f, "push rax\n\n");
			break;
		}
		case divstar: {
			translate_aux(tree->firstChild, f);
			translate_aux(tree->firstChild->nextSibling, f);
			
			fprintf(f, "pop rcx\n");
			fprintf(f, "pop rax\n");
			
			if (strcmp(tree->ident, "*") == 0) {
				fprintf(f, "imul rcx\n");   
				fprintf(f, "push rax\n\n"); 
			} 
			else if (strcmp(tree->ident, "/") == 0) {
				fprintf(f, "mov rdx, 0\n");
				fprintf(f, "idiv rcx\n");   
				fprintf(f, "push rax\n\n"); 
			} 
			else if (strcmp(tree->ident, "%") == 0) {
				fprintf(f, "mov rdx, 0\n");
				fprintf(f, "idiv rcx\n");   
				fprintf(f, "push rdx\n\n"); 
			}
			break;
		}
		case while_:{
			n1 =  tree->firstChild;
			n2 = tree->firstChild->nextSibling;
			countf++;
			int while_actuel = countf;
			fprintf(f,"deb_while%d:\n",while_actuel);
			translate_aux(n1,f);
			fprintf(f,"pop rax\n");
			fprintf(f,"cmp rax, 0\n");
			fprintf(f,"je fin_while%d\n",while_actuel);
			translate_aux(n2,f);
			fprintf(f,"jmp deb_while%d\n",while_actuel);
			fprintf(f,"fin_while%d:\n",while_actuel);
			break;
		}
		case declarations:{
			break;
		}

		case return_:{
			if (tree->firstChild != NULL) {
				translate_aux(tree->firstChild, f);
				fprintf(f, "pop rax\n"); 
			}
			else{
				fprintf(f,"mov rax,0\n");
			}
			fprintf(f,"mov rsp,rbp\n");
			fprintf(f,"pop rbp\n");
			fprintf(f,"ret\n\n");
			break;
			}
		case call_function: {
			Node *id_node = tree->firstChild;
			Node *args = id_node->nextSibling;
			int nb_args = 0;
			int total = 0;
			if (args != NULL){
				for (Node *arg = args->firstChild; arg != NULL; arg = arg->nextSibling){
					total++;
				}
			}
			int nb_param_attendu = -1;

			Type types_param_attendus[256];
			char *structs_param_attendus[256];

			for (int i = 0; i < 256; i++) {
				types_param_attendus[i] = TYPE_VOID;
				structs_param_attendus[i] = NULL;
			}
			if (strcmp(id_node->ident, "putint") == 0) {
				nb_param_attendu = 1;
				types_param_attendus[0] = TYPE_INT;
			}
			else if (strcmp(id_node->ident, "putchar") == 0) {
				nb_param_attendu = 1;
				types_param_attendus[0] = TYPE_CHAR;
			}
			else if (strcmp(id_node->ident, "getint") == 0) {
				nb_param_attendu = 0;
			}
			else if (strcmp(id_node->ident, "getchar") == 0) {
				nb_param_attendu = 0;
			}
			else {
				Node *fonctsNode = NULL;

				for (Node *c = root->firstChild; c != NULL; c = c->nextSibling) {
					if (c->label == functions) {
						fonctsNode = c;
						break;
					}
				}

				if (fonctsNode != NULL) {
					for (Node *func = fonctsNode->firstChild; func != NULL; func = func->nextSibling) {
						if (func->label != function)
							continue;

						Node *head = func->firstChild;
						if (head == NULL || head->label != heading)
							continue;

						Node *nomF = NULL;
						Node *params = NULL;

						for (Node *elem = head->firstChild; elem != NULL; elem = elem->nextSibling) {
							if (elem->label == id && nomF == NULL) {
								nomF = elem;
							}
							else if (elem->label == parameters) {
								params = elem;
							}
						}
				if (nomF != NULL && strcmp(nomF->ident, id_node->ident) == 0) {
					nb_param_attendu = 0;

					if (params != NULL) {
						for (Node *type_node = params->firstChild; type_node != NULL; type_node = type_node->nextSibling) {
							if (type_node->label != type)
								continue;

							Type typeParam = TYPE_VOID;
							int tailleParam = 0;
							char *structParam = NULL;

							if (type_node->firstChild != NULL && type_node->firstChild->label == structure) {
								Node *structNode = type_node->firstChild;
								Node *structNameNode = structNode->firstChild;

								typeParam = TYPE_STRUCT;
								structParam = structNameNode->ident;
							}
							else {
								type_et_taille(type_node, &typeParam, &tailleParam);
							}

							for (Node *paramId = type_node->firstChild; paramId != NULL; paramId = paramId->nextSibling) {
								if (paramId->label == id) {
									types_param_attendus[nb_param_attendu] = typeParam;
									structs_param_attendus[nb_param_attendu] = structParam;
									nb_param_attendu++;
								}
							}
						}
					}
					break;
				}
					}
				}
			}
			if (nb_param_attendu == -1) {
				fprintf(stderr, "err sem ligne %d : fonction %s non declaree\n", id_node->lineno, id_node->ident);
				exit(2);
			}

			if (total != nb_param_attendu) {
				fprintf(stderr, "err sem ligne %d : mauvais nombre d'arguments pour %s\n", id_node->lineno, id_node->ident);
				exit(2);
			}
			int indice_arg = 0;
			if (args != NULL) {
				for (Node *arg = args->firstChild; arg != NULL; arg = arg->nextSibling) {
					Type typeArg = get_type_expression(arg, tableLocale, tableGlobale);

					if (typeArg == TYPE_VOID) {
						fprintf(stderr, "err sem ligne %d : argument de type void\n", arg->lineno);
						exit(2);
					}

					if (types_param_attendus[indice_arg] == TYPE_CHAR && typeArg == TYPE_INT) {
						fprintf(stderr, "warning ligne %d : argument int donne a un parametre char\n", arg->lineno);
					}

					if (types_param_attendus[indice_arg] == TYPE_STRUCT || typeArg == TYPE_STRUCT) {
						if (types_param_attendus[indice_arg] != typeArg) {
							fprintf(stderr, "err sem ligne %d : argument structure incompatible\n", arg->lineno);
							exit(2);
						}

						char *structArg = NULL;

						if (arg->label == id || arg->label == field_dot) {
							LValueInfo lv_arg = resolve_lvalue(arg);
							structArg = lv_arg.struct_name;
						}
						else if (arg->label == call_function) {
							Node *called_id = arg->firstChild;
							Symbol *sf = recherche(tableGlobale, called_id->ident);
							if (sf != NULL)
								structArg = sf->struct_name;
						}

						if (structArg == NULL ||
							structs_param_attendus[indice_arg] == NULL ||
							strcmp(structArg, structs_param_attendus[indice_arg]) != 0) {
							fprintf(stderr, "err sem ligne %d : type structure incompatible en argument\n", arg->lineno);
							exit(2);
						}
					}
					indice_arg++;
				}
			}
			if (total<=6){
				if (args != NULL){
					for (Node *arg = args->firstChild; arg != NULL; arg = arg->nextSibling) {
						Type type_arg = get_type_expression(arg, tableLocale, tableGlobale);
						if (type_arg == TYPE_VOID) {
							fprintf(stderr, "err sem ligne %d : argument de type void\n", arg->lineno);
							exit(2);
						}
						translate_aux(arg, f);
						nb_args++;
					}
				}
			}
			else {
				for (int i = total ; i>=7;i--){
					int j = 1;
					for (Node *arg = args->firstChild; arg != NULL; arg = arg->nextSibling){
						if (j==i){
							translate_aux(arg,f);
							break;
						}
						j++;
					}
				}
				for (int i = 1 ; i<=6;i++){
					int j = 1;
					for (Node *arg = args->firstChild; arg != NULL; arg = arg->nextSibling){
						if (j==i){
							translate_aux(arg,f);
							break;
						}
						j++;
					}
				}
				nb_args = 6;
			}
			switch (nb_args) {
				case 6: fprintf(f, "pop r9\n");
				case 5: fprintf(f, "pop r8\n");
				case 4: fprintf(f, "pop rcx\n");
				case 3: fprintf(f, "pop rdx\n");
				case 2: fprintf(f, "pop rsi\n");
				case 1: fprintf(f, "pop rdi\n");
				case 0: break;
			}
		
			fprintf(f,"call %s\n",id_node->ident);
			if (total>6){
				fprintf(f,"add rsp, %d\n",(total-6)*8);
			}
			Symbol *s = recherche(tableGlobale,id_node->ident);
			if (s == NULL || s->is_function !=1){
				fprintf(stderr, "Erreur semantique ligne %d : la fonction %s n'est pas declaree.\n", id_node->lineno,id_node->ident);
				exit(2);
			}
			if (s->type != TYPE_VOID) 
				fprintf(f, "push rax\n\n");
			else 
				fprintf(f, "\n");
			break;
		}
		case field_dot: {
			LValueInfo lv = resolve_lvalue(tree);
			charger_lvalue(f, lv);
			break;
		}
		default:
			for (Node *c = tree->firstChild; c != NULL ; c = c->nextSibling){
				translate_aux(c,f);
			}
			break;
	}
}

void sauvegarder_parametres(Node *params, Symbol **tableLocale, FILE *f) {
    if (params != NULL && tableLocale != NULL) {
        int num_arg = 0;
        for (Node *type_node = params->firstChild; type_node != NULL; type_node = type_node->nextSibling) {
            if (type_node->label != type)
                continue;

            for (Node *idNode = type_node->firstChild; idNode != NULL; idNode = idNode->nextSibling) {
                if (idNode->label != id)
                    continue;

                Symbol *s = recherche(tableLocale, idNode->ident);

                if (s == NULL) {
                    fprintf(stderr, "err sem ligne %d : parametre %s introuvable\n", idNode ->lineno,idNode->ident);
                    exit(2);
                }
				if (num_arg<6){
					switch (num_arg) {
						case 0:
							fprintf(f, "mov rax, rdi\n");
							break;
						case 1:
							fprintf(f, "mov rax, rsi\n");
							break;
						case 2:
							fprintf(f, "mov rax, rdx\n");
							break;
						case 3:
							fprintf(f, "mov rax, rcx\n");
							break;
						case 4:
							fprintf(f, "mov rax, r8\n");
							break;
						case 5:
							fprintf(f, "mov rax, r9\n");
							break;
					}
				}else {
					int taille_param = 8 * (num_arg - 6)  + 16 ;
					fprintf(f,"mov rax, [rbp + %d]\n",taille_param);
				}
                if (s->type == TYPE_CHAR) {
                    fprintf(f, "mov byte [rbp - %d], al\n", adresse_locale(s));
                }
                else if (s->type == TYPE_INT) {
                    fprintf(f, "mov dword [rbp - %d], eax\n", adresse_locale(s));
                }
                num_arg++;
            }
        }
        if (num_arg > 0)
            fprintf(f, "\n");
    }
}

void ecrire_fonctions(FILE *f) {
    fprintf(f, "\n; Fonctions d'entree/sortie\n");
    fprintf(f, "global getint\n");
    fprintf(f, "global putchar\n");
    fprintf(f, "global getchar\n");
    fprintf(f, "global putint\n\n");

	fprintf(f,"getchar:\n");
	fprintf(f,"sub rsp,8\n");
	fprintf(f,"mov rax,0\n");
	fprintf(f,"mov rdi,0\n");
	fprintf(f,"mov rsi,rsp\n");
	fprintf(f,"mov rdx,1\n");
	fprintf(f,"syscall\n");
	fprintf(f,"cmp rax,1\n");
	fprintf(f,"jne error\n");
	fprintf(f,"mov rcx,0\n");
	fprintf(f,"mov cl, byte [rsp]\n");
	fprintf(f,"mov rax,rcx\n");
	fprintf(f,"add rsp,8\n");
	fprintf(f,"ret\n\n");
	fprintf(f,"error:\n");
	fprintf(f,"add rsp,8\n");
	fprintf(f,"mov rax,0\n");
	fprintf(f,"ret\n\n");

	fprintf(f,"putchar:\n");
	fprintf(f,"push rdi\n");
	fprintf(f,"mov rax,1\n");
	fprintf(f,"mov rdi,1\n");
	fprintf(f,"mov rsi,rsp\n");
	fprintf(f,"mov rdx,1\n");
	fprintf(f,"syscall\n");
	fprintf(f,"pop rdi\n");
	fprintf(f,"ret\n\n");

	fprintf(f, "getint:\n");
	fprintf(f, "sub rsp, 8\n");
	fprintf(f, "mov r8, 0\n");
	fprintf(f, "mov r9, 1\n");
	fprintf(f, "mov r10, 0\n");
	fprintf(f, "mov rax, 0\n");
	fprintf(f, "mov rdi, 0\n");
	fprintf(f, "mov rsi, rsp\n");
	fprintf(f, "mov rdx, 1\n");
	fprintf(f, "syscall\n");
	fprintf(f, "cmp rax, 1\n");
	fprintf(f, "jne getint_error\n");
	fprintf(f, "mov rcx, 0\n");
	fprintf(f, "mov cl, byte [rsp]\n");
	fprintf(f, "cmp rcx, '-'\n");
	fprintf(f, "jne getint_check_plus\n");
	fprintf(f, "mov r9, -1\n");
	fprintf(f, "jmp getint_loop\n");
	fprintf(f, "getint_check_plus:\n");
	fprintf(f, "cmp rcx, '+'\n");
	fprintf(f, "jne getint_first_digit\n");
	fprintf(f, "jmp getint_loop\n");
	fprintf(f, "getint_first_digit:\n");
	fprintf(f, "cmp rcx, '0'\n");
	fprintf(f, "jl getint_error\n");
	fprintf(f, "cmp rcx, '9'\n");
	fprintf(f, "jg getint_error\n");
	fprintf(f, "sub rcx, '0'\n");
	fprintf(f, "imul r8, 10\n");
	fprintf(f, "add r8, rcx\n");
	fprintf(f, "inc r10\n");
	fprintf(f, "jmp getint_loop\n");
	fprintf(f, "getint_loop:\n");
	fprintf(f, "mov rax, 0\n");
	fprintf(f, "mov rdi, 0\n");
	fprintf(f, "mov rsi, rsp\n");
	fprintf(f, "mov rdx, 1\n");
	fprintf(f, "syscall\n");
	fprintf(f, "cmp rax, 1\n");
	fprintf(f, "jne getint_error\n");
	fprintf(f, "mov rcx, 0\n");
	fprintf(f, "mov cl, byte [rsp]\n");
	fprintf(f, "cmp rcx, '0'\n");
	fprintf(f, "jl getint_not_digit\n");
	fprintf(f, "cmp rcx, '9'\n");
	fprintf(f, "jg getint_not_digit\n");
	fprintf(f, "sub rcx, '0'\n");
	fprintf(f, "imul r8, 10\n");
	fprintf(f, "add r8, rcx\n");
	fprintf(f, "inc r10\n");
	fprintf(f, "jmp getint_loop\n");
	fprintf(f, "getint_not_digit:\n");
	fprintf(f, "cmp rcx, 10\n");
	fprintf(f, "jne getint_error\n");
	fprintf(f, "cmp r10, 0\n");
	fprintf(f, "je getint_error\n");
	fprintf(f, "imul r8, r9\n");
	fprintf(f, "mov rax, r8\n");
	fprintf(f, "add rsp, 8\n");
	fprintf(f, "ret\n");
	fprintf(f, "getint_error:\n");
	fprintf(f, "add rsp, 8\n");
	fprintf(f, "mov rax, 60\n");
	fprintf(f, "mov rdi, 5\n");
	fprintf(f, "syscall\n\n");

	fprintf(f,"putint:\n");
	fprintf(f,"mov rax, rdi\n");
	fprintf(f,"cmp rax, 0\n");
	fprintf(f,"je print_zero\n");
	fprintf(f,"jge prepare_loop\n");
	fprintf(f,"push rax\n");
	fprintf(f,"mov rdi, '-'\n");
	fprintf(f,"call putchar\n");
	fprintf(f,"pop rax\n");
	fprintf(f,"neg rax\n");
	fprintf(f,"jmp prepare_loop\n\n");
	fprintf(f,"print_zero:\n");
	fprintf(f,"mov rdi, '0'\n");
	fprintf(f,"call putchar\n");
	fprintf(f,"mov rdi, 10\n");
	fprintf(f,"call putchar\n");
	fprintf(f,"ret\n\n");
	fprintf(f,"prepare_loop:\n");
	fprintf(f,"mov r8, 10\n");
	fprintf(f,"mov rcx, 0\n\n");
	fprintf(f,"divide_loop:\n");
	fprintf(f,"cmp rax, 0\n");
	fprintf(f,"je print_loop\n");
	fprintf(f,"mov rdx, 0\n");
	fprintf(f,"div r8\n");
	fprintf(f,"add rdx, '0'\n");
	fprintf(f,"push rdx\n");
	fprintf(f,"inc rcx\n");
	fprintf(f,"jmp divide_loop\n");
	fprintf(f,"print_loop:\n");
	fprintf(f,"cmp rcx, 0\n");
	fprintf(f,"je fini\n");
	fprintf(f,"pop rdi\n");
	fprintf(f,"push rcx\n");
	fprintf(f,"call putchar\n");
	fprintf(f,"pop rcx\n");
	fprintf(f,"dec rcx\n");
	fprintf(f,"jmp print_loop\n\n");
	fprintf(f,"fini:\n");
	fprintf(f,"mov rdi, 10\n");
	fprintf(f,"call putchar\n");
	fprintf(f,"ret\n\n");

}
void translate(Node* tree, FILE* f){
	int taille = number_elem_adr(tableGlobale);
	fprintf(f, "section .bss\n");
	if (taille > 0){
		fprintf(f, "global_vars: resb %d\n", taille);
	}
	fprintf(f, "\n");
	fprintf(f, "section .text\n");
	fprintf(f, "global _start\n");
	fprintf(f, "_start:\n");
	fprintf(f, "    call main\n");    
	fprintf(f, "    mov rdi, rax\n");
	fprintf(f, "    mov rax, 60\n"); 
	fprintf(f, "    syscall\n\n");

	Node *fonctsNode = NULL;
	for (Node *c = tree->firstChild; c != NULL ; c = c->nextSibling){
		if (c->label == functions) {
			fonctsNode = c;
			break;
		}
	}

	if (fonctsNode != NULL) {
		
		for (Node *currFunc = fonctsNode->firstChild; currFunc != NULL; currFunc = currFunc->nextSibling) {
			if (currFunc->label == function) {
				Node* heading = currFunc->firstChild;
				Node* id_node = heading->firstChild; 
                
			
				if (id_node->label != id && id_node->nextSibling != NULL) {
					id_node = id_node->nextSibling;
				}

				if (id_node != NULL && id_node->label == id) {
					
					fprintf(f, "%s:\n", id_node->ident);

					
					fprintf(f, "push rbp\n");
					fprintf(f, "mov rbp, rsp\n");

			
					tableLocale = get_local_table(id_node->ident);
					int taille_locale = number_elem_adr(tableLocale);
					if (taille_locale > 0) {
						fprintf(f, "sub rsp, %d\n", taille_locale);
					}
					Node *params_node = NULL;
					for (Node *elem_header = heading->firstChild; elem_header != NULL; elem_header = elem_header->nextSibling) {
						if (elem_header->label == parameters) {
							params_node = elem_header;
							break;
						}
					}

					sauvegarder_parametres(params_node, tableLocale, f);
					translate_aux(currFunc->firstChild->nextSibling, f);
					fprintf(f,"mov rax,0\n");
					fprintf(f,"mov rsp,rbp\n");
					fprintf(f,"pop rbp\n");
					fprintf(f, "ret\n\n");
				}
			}
		}
	}
	 ecrire_fonctions(f);
}