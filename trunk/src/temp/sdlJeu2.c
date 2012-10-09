#include <stdio.h>

#include <ncurses.h>

#include <assert.h>
#include <time.h>
#include "jeu.h"

void ncursAff( WINDOW* win, Jeu *pJeu)
{
	int x,y,i_fant;

	 map *pTer = jeuGetMap(pJeu);
	 hero *pPac = jeuGetHero(pJeu);

	wclear(win);

	for(x=0;x<getDimX(pTer);++x)
		for(y=0;y<getDimY(pTer);++y)
			mvwprintw( win, y, x, "%c", mapGetXY(pTer,x,y) );


	mvwprintw( win, getPosiY(pPac), getPosiX(pPac), "*");

	wmove( win, getPosiY(pPac), getPosiX(pPac));
}

void ncursBoucle(Jeu *pJeu)
{

	WINDOW *win, *screen;
	int c;
	int continue_boucle;
	
	 /* Horloges (en secondes) */
    float horloge_courante, horloge_precedente;

    /* Intervalle de temps (en secondes) entre deux évolutions du jeu */
    /* Changer la valeur pour ralentir ou accélérer le déplacement des fantomes */
    float intervalle_horloge = 0.1f;

	screen = initscr();		/* passe l'écran texte en mode NCurses */

	clear();		/* efface l'écran */
	
	noecho();  	/* Lorsqu'une touche est préssée au clavier, elle n'apparait pasa à l'écran */

	cbreak();		/* un caractère est directement affiché, il ne passe pas dans un buffer */

	/* Creation d'une nouvelle fenetre en mode texte */
	/* => fenetre de dimension et position ( WIDTH, HEIGHT, STARTX,STARTY) */
	win = newwin( getDimY(jeuGetMap(pJeu)), getDimX(jeuGetMap(pJeu)), 0, 0 );
	
	keypad(win, TRUE);		/* pour que les flèches soient traitées (il faut le faire après création de la fenêtre) */

	/*halfdelay(temps_dizieme);*/
	/* notimeout(win,true); */
	/* wtimeout( win, 500 ); */

	nodelay(win,true); /* Pour que l'appel à wgetch soit non-bloquant */

	continue_boucle = 1;

	/* Récupère l'horloge actuelle et la convertit en secondes */
    /* clock() retourne le nombre de tops horloge depuis le lancement du programme */
    horloge_precedente = (float)clock()/(float)CLOCKS_PER_SEC;

    ncursAff( win, pJeu);

	do
	{
	if(pJeu->perso.saut==0)
	{
	  	gravitation(&(pJeu->perso), &(pJeu->gMap));
	  	
	}

	
        /* Récupère l'horloge actuelle et la convertit en secondes */
        /* clock() retourne le nombre de tops horloge depuis le lancement du programme */
        horloge_courante = (float)clock()/(float)CLOCKS_PER_SEC;

        if (horloge_courante-horloge_precedente>=intervalle_horloge)
        {
                
                ncursAff( win, pJeu);
                horloge_precedente = horloge_courante;
              
        }


		c = wgetch(win);
		
		
		/* jeuActionClavier( jeu, 'd'); */
		switch(c)
		{
			case KEY_LEFT:
				control( pJeu, 'g');
				ncursAff( win, pJeu);
				break;
			case KEY_RIGHT:
				control( pJeu, 'd');
				ncursAff( win, pJeu);
				break;
			case KEY_UP:
				control( pJeu, 's');
				ncursAff( win, pJeu);
				break;
			case 27: /* ECHAP */
				continue_boucle = 0;
				break;
		}
		
	} while (continue_boucle==1);

    assert(delwin(win)!=ERR);
    assert(delwin(screen)!=ERR);

	endwin();
}
