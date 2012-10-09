options = -g -Wall -pedantic
ssdl = `sdl-config --cflags --libs`
sttf = -lSDLmain -lSDL -lSDL_ttf 
endbin = bin/
endobj = obj/
endsrc = src/

all: $(endbin)main 


$(endobj)main.o: $(endsrc)main.c  
	gcc $(options) -c $(endsrc)main.c $(ssdl) $(sttf) -o $(endobj)main.o

$(endobj)hero.o: $(endsrc)hero.c $(endsrc)hero.h $(endsrc)map.h
	gcc $(options) -c $(endsrc)hero.c $(ssdl) $(sttf) -o $(endobj)hero.o
	
$(endobj)jeu.o: $(endsrc)jeu.c  $(endsrc)hero.h
	gcc $(options) -c $(endsrc)jeu.c $(ssdl) $(sttf) -o $(endobj)jeu.o
	
$(endobj)map.o: $(endsrc)map.c $(endsrc)map.h
	gcc $(options) -c $(endsrc)map.c $(ssdl) $(sttf) -o $(endobj)map.o

$(endobj)sdlJeu.o: $(endsrc)sdlJeu.c $(endsrc)sdlJeu.h $(endsrc)jeu.h $(endsrc)anim.h
	gcc $(options) -c $(endsrc)sdlJeu.c $(ssdl) $(sttf) -o $(endobj)sdlJeu.o

$(endobj)anim.o: $(endsrc)anim.c $(endsrc)anim.h
	gcc $(options) -c $(endsrc)anim.c $(ssdl) $(sttf) -o $(endobj)anim.o
		
$(endbin)main: $(endobj)main.o $(endobj)sdlJeu.o $(endobj)hero.o $(endobj)jeu.o $(endobj)map.o $(endobj)anim.o
	gcc $(endobj)main.o $(endobj)sdlJeu.o $(endobj)hero.o $(endobj)jeu.o $(endobj)map.o $(endobj)anim.o $(ssdl) $(sttf) -o $(endbin)main
	
clean:
	rm obj/* bin/*
