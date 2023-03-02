TARGET=../dariu
CXX=g++
DEBUG=-g
OPT=-O0
WARN=-Wall
SFML=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CXXFLAGS=$(DEBUG) $(OPT) $(WARN) $(SFML)
LD=g++
OBJS= main.o game.o dariu.o tilemap.o tools.o actor.o animation.o score.o enimies.o inimigo.o
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(CXXFLAGS)
	@rm *.o
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
