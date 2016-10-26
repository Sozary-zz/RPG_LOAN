all: RPG
OBJ=obj/

$(OBJ)Arme.o: Arme.cpp
	g++ -o $(OBJ)Arme.o -c Arme.cpp

$(OBJ)Classe.o: Classe.cpp
	g++ -o $(OBJ)Classe.o -c Classe.cpp

$(OBJ)Hero.o: Hero.cpp
	g++ -o $(OBJ)Hero.o -c Hero.cpp

$(OBJ)Inventaire.o: Inventaire.cpp
	g++ -o $(OBJ)Inventaire.o -c Inventaire.cpp

$(OBJ)main.o: main.cpp
	g++ -o $(OBJ)main.o -c main.cpp

$(OBJ)Monstre.o: Monstre.cpp
	g++ -o $(OBJ)Monstre.o -c Monstre.cpp

$(OBJ)Personnage.o: Personnage.cpp
	g++ -o $(OBJ)Personnage.o -c Personnage.cpp

$(OBJ)Position.o: Position.cpp
	g++ -o $(OBJ)Position.o -c Position.cpp

$(OBJ)Slot.o: Slot.cpp
	g++ -o $(OBJ)Slot.o -c Slot.cpp
 
RPG:  Arme.o $(OBJ)Classe.o $(OBJ)Hero.o $(OBJ)Inventaire.o $(OBJ)main.o $(OBJ)Monstre.o $(OBJ)Personnage.o $(OBJ)Position.o $(OBJ)Slot.o
	g++ -o RPG  $(OBJ)Arme.o $(OBJ)Classe.o $(OBJ)Hero.o $(OBJ)Inventaire.o $(OBJ)main.o $(OBJ)Monstre.o $(OBJ)Personnage.o $(OBJ)Position.o $(OBJ)Slot.o
	
