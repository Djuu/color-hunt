#ifndef _DIALOGUE
#define _DIALOGUE


typedef struct 
{
  float info;
  struct Node * ls;
  struct Node * rs;
}Node;


typedef struct 
{
	Node * adRoot; 
	int nbElemInTree;
}Tree;



/** Precondition : *pTree non prealablement initialise
   Postcondition : *pTree est initialise vide */
void initTree(Tree *pTree);


/** Precondition : *pTree prealablement initialise
   Postcondition : *pTree pret a disparaitre (ne doit plus etre utilise) */
void freeTree(Tree *pTree);


/** Precondition : pTree initialise
   Resultat : 1 si pTree est vide, 0 sinon */
int emptyTreeTest(Tree pTree);

/** Precondition : *pTree est un arbre binaire de recherche initialise
   Postcondition : si e n'existait pas deja dans l'arbre *pTree, alors
   un nouveau noeud contenant e est insere aux feuilles de *pTree. 
   Si au contraire e existait deja dans l'arbre, alors l'arbre est
   inchange. */
void insertElement(float e, Tree *pTree);

/** Recherche l'élément e dans l'arbre et renvoie son fils gauche ou droit en fonction du choix effectué dans le dialogue */
float searchElement(float e, Tree pTree, int choice, int confirm);
/** Initialise l'arbre */
void initDialogue(Tree *pTree);
/** Cherche dans le fichier dialogue le bon dialogue correspondant au choix effectué */
char *discutionDialogue(Tree *pTree, float choice);

#endif
