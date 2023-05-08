CXX=g++
DEBUG=-g
OPT=-O0
WARN=-Wall
CPPVERSION=-std=c++17
ifeq ($(OS), Windows_NT)	
	TARGET=dariu.exe
	REMOVE=del *.o
	SFML=-IC:\SFML\include -LC:\SFML\lib -LC:\mingw64\x86_64-w64-mingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
else
	TARGET=./dariu
	REMOVE=rm *.o
	SFML=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
endif
CXXFLAGS=$(DEBUG) $(OPT) $(WARN) $(SFML) $(CPPVERSION)
LD=g++
OBJS= main.o game.o dariu.o tilemap.o tools.o actor.o animation.o score.o enimies.o plataform.o sounds.o
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(CXXFLAGS)
	@$(REMOVE)
	@./$(TARGET) 2

main.o: ./src/main.cpp ; $(CXX) -c $(CXXFLAGS) ./src/main.cpp -o main.o
game.o: ./src/model/game.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/game.cpp -o game.o
dariu.o: ./src/model/dariu.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/dariu.cpp -o dariu.o
tilemap.o: ./src/model/tilemap.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/tilemap.cpp -o tilemap.o
tools.o: ./src/model/tools.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/tools.cpp -o tools.o
actor.o: ./src/model/actor.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/actor.cpp -o actor.o
animation.o: ./src/model/animation.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/animation.cpp -o animation.o
score.o: ./src/model/score.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/score.cpp -o score.o
enimies.o: ./src/model/enimies.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/enimies.cpp -o enimies.o
plataform.o: ./src/model/plataform.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/plataform.cpp -o plataform.o
sounds.o: ./src/model/sounds.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/sounds.cpp -o sounds.o
