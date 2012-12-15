options = -g -Wall -pedantic -DNDEBUG -O2
ssdl = `sdl-config --cflags --libs`
sttf = -lSDLmain -lSDL -lSDL_ttf -lSDL_image -lSDL_gfx -lSDL_mixer
endbin = bin/
endobj = obj/
endsrc = src/

all: $(endbin)main 


$(endobj)main.o: $(endsrc)main.c $(endsrc)SDLGame.h
	gcc $(options) -c $(endsrc)main.c $(ssdl) $(sttf) -o $(endobj)main.o

$(endobj)Position.o:$(endsrc)Position.c $(endsrc)Position.h
	gcc $(options) -c $(endsrc)Position.c $(ssdl) $(sttf) -o $(endobj)Position.o

$(endobj)Dialogue.o:$(endsrc)Dialogue.c $(endsrc)Dialogue.h
	gcc $(options) -c $(endsrc)Dialogue.c $(ssdl) $(sttf) -o $(endobj)Dialogue.o
		
$(endobj)Animation.o:$(endsrc)Animation.c $(endsrc)Animation.h 
	gcc $(options) -c $(endsrc)Animation.c $(ssdl) $(sttf) -o $(endobj)Animation.o
	
$(endobj)Enemy.o:$(endsrc)Enemy.c $(endsrc)Enemy.h $(endsrc)Character.h
	gcc $(options) -c $(endsrc)Enemy.c $(ssdl) $(sttf) -o $(endobj)Enemy.o
	
$(endobj)Physics.o:$(endsrc)Physics.c $(endsrc)Physics.h $(endsrc)Character.h $(endsrc)Object.h
	gcc $(options) -c $(endsrc)Physics.c $(ssdl) $(sttf) -o $(endobj)Physics.o
	
$(endobj)Object.o:$(endsrc)Object.c $(endsrc)Object.h $(endsrc)Position.h
	gcc $(options) -c $(endsrc)Object.c $(ssdl) $(sttf) -o $(endobj)Object.o

$(endobj)Character.o: $(endsrc)Character.c $(endsrc)Character.h $(endsrc)Position.h
	gcc $(options) -c $(endsrc)Character.c $(ssdl) $(sttf) -o $(endobj)Character.o
	
$(endobj)Game.o: $(endsrc)Game.c $(endsrc)Game.h $(endsrc)Enemy.h $(endsrc)Physics.h $(endsrc)Map.h
	gcc $(options) -c $(endsrc)Game.c $(ssdl) $(sttf) -o $(endobj)Game.o
	
$(endobj)Map.o: $(endsrc)Map.c $(endsrc)Map.h
	gcc $(options) -c $(endsrc)Map.c $(ssdl) $(sttf) -o $(endobj)Map.o

$(endobj)SDLGame.o: $(endsrc)SDLGame.c $(endsrc)SDLGame.h $(endsrc)Game.h $(endsrc)Animation.h $(endsrc)Dialogue.h
	gcc $(options) -c $(endsrc)SDLGame.c $(ssdl) $(sttf) -o $(endobj)SDLGame.o
		
$(endbin)main: $(endobj)main.o $(endobj)SDLGame.o $(endobj)Character.o $(endobj)Game.o $(endobj)Map.o $(endobj)Dialogue.o $(endobj)Enemy.o $(endobj)Position.o $(endobj)Object.o $(endobj)Physics.o  $(endobj)Animation.o
	gcc $(endobj)main.o $(endobj)Dialogue.o $(endobj)SDLGame.o $(endobj)Character.o $(endobj)Game.o $(endobj)Map.o $(endobj)Enemy.o $(endobj)Position.o $(endobj)Object.o $(endobj)Physics.o $(endobj)Animation.o $(ssdl) $(sttf) -o $(endbin)main
	
clean:
	rm obj/* bin/*
