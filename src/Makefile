CXX=g++
DEBUG=-g
OPT=-O0
WARN=-Wall
CPPVERSION=-std=c++17
ifeq ($(OS), Windows_NT)	
	TARGET=../dariu.exe
	REMOVE=del *.o
	SFML=-IC:\SFML\include -LC:\SFML\lib -LC:\mingw64\x86_64-w64-mingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
else
	TARGET=../dariu
	REMOVE=rm *.o
	SFML=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
endif
CXXFLAGS=$(DEBUG) $(OPT) $(WARN) $(SFML) $(CPPVERSION)
LD=g++
OBJS= main.o game.o dariu.o tilemap.o tools.o actor.o animation.o score.o enimies.o inimigo.o plataform.o sounds.o
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(CXXFLAGS)
	@$(REMOVE)
	@./$(TARGET) 2

main.o: main.cpp ; $(CXX) -c $(CXXFLAGS) main.cpp -o main.o
game.o: ./model/game.cpp ; $(CXX) -c $(CXXFLAGS) ./model/game.cpp -o game.o
dariu.o: ./model/dariu.cpp ; $(CXX) -c $(CXXFLAGS) ./model/dariu.cpp -o dariu.o
tilemap.o: ./model/tilemap.cpp ; $(CXX) -c $(CXXFLAGS) ./model/tilemap.cpp -o tilemap.o
tools.o: ./model/tools.cpp ; $(CXX) -c $(CXXFLAGS) ./model/tools.cpp -o tools.o
actor.o: ./model/actor.cpp ; $(CXX) -c $(CXXFLAGS) ./model/actor.cpp -o actor.o
animation.o: ./model/animation.cpp ; $(CXX) -c $(CXXFLAGS) ./model/animation.cpp -o animation.o
score.o: ./model/score.cpp ; $(CXX) -c $(CXXFLAGS) ./model/score.cpp -o score.o
enimies.o: ./model/enimies.cpp ; $(CXX) -c $(CXXFLAGS) ./model/enimies.cpp -o enimies.o
inimigo.o: ./model/inimigo.cpp ; $(CXX) -c $(CXXFLAGS) ./model/inimigo.cpp -o inimigo.o
plataform.o: ./model/plataform.cpp ; $(CXX) -c $(CXXFLAGS) ./model/plataform.cpp -o plataform.o
sounds.o: ./model/sounds.cpp ; $(CXX) -c $(CXXFLAGS) ./model/sounds.cpp -o sounds.o
