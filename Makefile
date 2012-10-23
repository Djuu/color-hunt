options = -g -Wall -pedantic
ssdl = `sdl-config --cflags --libs`
sttf = -lSDLmain -lSDL -lSDL_ttf 
endbin = bin/
endobj = obj/
endsrc = src/

all: $(endbin)main 


$(endobj)main.o: $(endsrc)main.c  
	gcc $(options) -c $(endsrc)main.c $(ssdl) $(sttf) -o $(endobj)main.o

$(endobj)Character.o: $(endsrc)Character.c $(endsrc)Character.h $(endsrc)Map.h
	gcc $(options) -c $(endsrc)Character.c $(ssdl) $(sttf) -o $(endobj)Character.o
	
$(endobj)Game.o: $(endsrc)Game.c  $(endsrc)Character.h
	gcc $(options) -c $(endsrc)Game.c $(ssdl) $(sttf) -o $(endobj)Game.o
	
$(endobj)Map.o: $(endsrc)Map.c $(endsrc)Map.h
	gcc $(options) -c $(endsrc)Map.c $(ssdl) $(sttf) -o $(endobj)Map.o

$(endobj)sdlGame.o: $(endsrc)sdlGame.c $(endsrc)sdlGame.h $(endsrc)Game.h $(endsrc)anim.h
	gcc $(options) -c $(endsrc)sdlGame.c $(ssdl) $(sttf) -o $(endobj)sdlGame.o

		 
$(endbin)main: $(endobj)main.o $(endobj)Map.o $(endobj)Game.o $(endobj)Character.o $(endobj)sdlGame.o
	gcc $(endobj)main.o  $(endobj)Map.o  $(endobj)sdlGame.o $(ssdl) $(sttf) -o $(endbin)main
	
clean:
	rm obj/* bin/*
