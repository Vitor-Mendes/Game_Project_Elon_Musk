install:	
	sudo apt-get update
	sudo apt-get -f install freeglut3 freeglut3-dev binutils-gold g++ cmake libglew-dev mesa-common-dev libglew1.5-dev libglm-dev
	sudo apt-get -f install libsoil-dev
	sudo apt-get -f install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev
game:	main.cpp objetos.cpp
	g++ -o Jogo main.cpp objetos.cpp -lSOIL -lglut -lGLU -lGL -lm -lSDL -lSDL_mixer
run:	Jogo
	./Jogo
