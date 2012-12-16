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



void initTree(Tree *pTree);
/* Precondition : *pA non prealablement initialise
   Postcondition : *pA est initialise vide */


void freeTree(Tree *pTree);
/* Precondition : *pA prealablement initialise
   Postcondition : *pA pret a disparaitre (ne doit plus etre utilise) */


int emptyTreeTest(Tree pTree);
/* Precondition : A initialise
   Resultat : 1 si A est vide, 0 sinon */

void insertElement(float e, Tree *pTree);
/* Precondition : *pA est un arbre binaire de recherche initialise
   Postcondition : si e n'existait pas deja dans l'arbre *pA, alors
   un nouveau noeud contenant e est insere aux feuilles de *pA. 
   Si au contraire e existait deja dans l'arbre, alors l'arbre est
   inchange. */


float searchElement(float e, Tree pTree, int choice, int confirm);
void affichageArborescent(Tree A);

void initDialogue(Tree *pTree);
char *discutionDialogue(Tree *pTree, float choice);

#endif
