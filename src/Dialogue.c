#include <assert.h>
#include <stdio.h>
#include <stdlib.h> 
#include "Dialogue.h"


static void destroyFrom(Node *pN, Tree *pTree);
static void insertEleInUnderTree(float e, Node ** ppN, Tree *pTree);
static void initNode(Node *pN, float e);

static void initNode(Node *pN, float e)
{
  pN->info = e;
  pN->ls = NULL;
  pN->rs = NULL;
}


void initTree(Tree *pTree)
{
	pTree -> adRoot = NULL;
	pTree -> nbElemInTree = 0;
}


void freeTree(Tree *pTree)
{
	Node * n;
	n=pTree -> adRoot;
	destroyFrom(n, pTree);    
}


static void destroyFrom(Node *pN, Tree *pTree)
{
	if (pN !=NULL)
	{
		destroyFrom(pN -> rs, pTree);
		destroyFrom(pN -> ls, pTree);
		free (pN);
		pTree -> nbElemInTree --;
	}

	
}


int emptyTreeTest(Tree pTree)
{
  if (pTree.adRoot==NULL) return 1;
  else return 0;
}




void insertElement(float e, Tree *pTree)
{
  	insertEleInUnderTree(e, &(pTree -> adRoot), pTree); 
}

static void insertEleInUnderTree(float e, Node ** ppN, Tree *pTree)
{
	   if(*ppN == NULL)
	   {
	   	  (*ppN)=(Node*)malloc(sizeof (Node));
	   	  initNode(*ppN, e);
	   	  pTree -> nbElemInTree ++;
	   } 
	   else if ((*ppN) -> info > e)
	   {
	    	insertEleInUnderTree(e,&(*ppN) -> ls, pTree);
	   }
	   else 
	   {
	    	insertEleInUnderTree(e,&(*ppN) -> rs, pTree);
	   }
}


float searchElement(float e, Tree pTree, int choice, int confirm)
{	
	Node * temp;
	temp = pTree.adRoot;
	if(confirm == 1)
	{
		while(temp != NULL)
		{
			if (e<temp -> info)
			{
				temp = temp -> ls;
			}
			else if (e>temp -> info)
			{
				temp = temp -> rs; 
			}
			else
			{
				if(choice == 1 && temp->ls != NULL)
				{
						temp = temp->ls;
						return temp ->info; 
				}
				else if (choice == 2 && temp ->rs !=NULL)
				{
					temp = temp ->rs;
					return temp -> info; 
				}
			}

		}
	}
	return -1;
}




void initDialogue(Tree *pTree)
{
	initTree(pTree);
	insertElement(2.0, pTree);
	insertElement(1.0, pTree);
	insertElement(3.0, pTree);
	insertElement(0.5, pTree);
	insertElement(1.5, pTree);
	insertElement(2.5, pTree);
	insertElement(3.5, pTree);

	
}

char *discutionDialogue(Tree *pTree, float choice)
{
	FILE *f = fopen("data/other/dialogue.txt","r");
  	if (f == NULL)
	{
		printf("Impossible d'ouvrir le fichier %s\n","data/other/dialogue.txt");
		exit(1);
	}

	float get;
	char tmp;
	char dialTab[200];
	int k=0;
	
	fscanf(f ,"%f",&(get));
	while (get != choice && tmp != '$')
	{	
			fscanf(f ,"%c",&(tmp));
			fscanf(f ,"%f",&(get));
	}
	
	fscanf(f ,"%c",&(tmp));
	while (tmp != '#' && tmp != '$')
	{
			
			dialTab[k]=tmp;
			fscanf(f ,"%c",&(tmp));
			printf("%c\n", tmp);
			k++;
	}

printf("%c\n", tmp);
	dialTab[k]='\0';
		printf("%s\n", dialTab);
	return dialTab; 
	
}



