all:
	g++	-I src/include -L src/lib -o hangman hangman.cpp diff.cpp windows.cpp draw.cpp GameLogic.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf 
	./hangman