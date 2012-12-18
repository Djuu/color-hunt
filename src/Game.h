#ifndef _GAME
#define _GAME

#include "Map.h"
#include "Physics.h"
#include "Enemy.h"

#define consumedMana 20

typedef struct
{
	Character gChar;
	Character gPnj;
	Enemies gEnemies;
	Map gMap;
	Objects gObjects;
	int level;
}Game;

/** Initialise le jeu */
void initGame (Game *pGame, const char* pMap);
/** Appel la fonction correspondant a la touche appelée */
void controlKey (Game *pGame, const char key);
/** Accesseur Map */
Map *getGameMap (Game *pGame);
/** Accesseur Char */
Character *getGameChar (Game* pGame);
/** Réinitialisation de v_x à 0 */
void initSpeedX(Game *pGame);
/** Réinitialisation de v_y à 0 */
void initSpeedY(Game *pGame);
/** Accesseur Enemies */
Enemies *getGameEnemies(Game *pGame);
/** Si le personnage principale touche un caractère spécifique on charge un autre niveau */
int warpMap (Game *pGame);
/** Permet de gérer la collision , entre une position et la Map */
void collisionMap (Position *pPosi, Map *pMap);
/** Renvoi 1 s'il y a collision entre 2 positions , 0 sinon */
int collision(Position *pPosi1, Position *pPosi2);
/** Accesseur Pnj */
Character *getGamePnj(Game *pGame);
/** Modifie v_y pour faire une translation vers le bas */
void down(Game *pGame);
/** Modifie v_y pour faire une translation vers le haut */
void up(Game *pGame);
/** Appel la fonction correspondant a la touche appelée pour la world map*/
void controlKey2 (Game *pGame, const char key);
/** Fonction appelée quand on appuie sur le boutton d'attaque , s'il y a un ennemie devant le personnage , il perdra de la vie */
void attack(Game *pGame);
/** Accesseur Objects */
Objects *getGameObjects(Game *pGame);
/** Fonction appelée quand on appuie sur le boutton super attaque , elle initialise une boule de feu à la position du personnage puis lui applique un mouvement */
void superAttack(Game *pGame);
/** Si une boule de feu touche un ennemie , il perd de la vie et elle disparait */
void superAttackDmg(Game *pGame);
/** Modifie v_x pour faire une translation vers le la droite */
void right(Game *pGame);
/** Modifie v_x pour faire une translation vers le la gauche */
void left(Game *pGame);
/** Modifie v_x pour faire une translation vers le la droite sur la world map*/
void right2(Game *pGame);
/** Modifie v_x pour faire une translation vers le la gauche sur la world map*/
void left2(Game *pGame);
/** Fonction appelé pour faire attaquer l'ennemie , s'il touche le personnage , il perd de la vie */
void enemyAttack(Game *pGame);
/** Retourne l'id de l'ennemie le plus proche */
int distanceEnemies(Game *pGame);
/** Collision entre une position et un objet */
void collisionObjects (Position *pPosi, Objects *pObjects);
/** Intelligence des ennemies , si on approche d'un ennemie , il nous fonce dessus*/
void detect(Game *pGame);
/** Renvoi 1 si on est en contact avec un pnj , 0 sinon */
int detectPnj(Game *pGame);
#endif

