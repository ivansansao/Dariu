TARGET=../dariu
CXX=g++
DEBUG=-g
OPT=-O0
WARN=-Wall
SFML=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CXXFLAGS=$(DEBUG) $(OPT) $(WARN) $(SFML)
LD=g++
OBJS= main.o game.o dariu.o
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(CXXFLAGS)
	@rm *.o
	@./$(TARGET) 2

main.o: main.cpp ; $(CXX) -c $(CXXFLAGS) main.cpp -o main.o
game.o: ./model/game.cpp ; $(CXX) -c $(CXXFLAGS) ./model/game.cpp -o game.o
dariu.o: ./model/dariu.cpp ; $(CXX) -c $(CXXFLAGS) ./model/dariu.cpp -o dariu.o
