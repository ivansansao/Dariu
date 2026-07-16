CXX=g++
DEBUG=-g
OPT=-O0
WARN=-Wall
CPPVERSION=-std=c++17
ifeq ($(OS), Windows_NT)	
	TARGET=dariu.exe
	REMOVE=del /Q *.o
	SFML_CFLAGS=-IC:\SFML\include
	SFML_LIBS=-LC:\SFML\lib -LC:\mingw64\x86_64-w64-mingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
else
	TARGET=dariu
	REMOVE=rm -f *.o
	SFML_CFLAGS=-I$(CURDIR)/include $(shell pkg-config --cflags sfml-all)
	SFML_LIBS=$(shell pkg-config --libs sfml-all)
endif
CXXFLAGS=$(DEBUG) $(OPT) $(WARN) $(CPPVERSION) $(SFML_CFLAGS)
LDFLAGS=$(SFML_LIBS)
LD=g++
OBJS= main.o game.o dariu.o tilemap.o tools.o actor.o animation.o score.o enimies.o plataform.o sounds.o bulletgun.o rect.o
RUN_ARGS?=2
.PHONY: all run clean clean-target

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

run: clean-target clean all
	@echo $(CURDIR)
	@trap '$(REMOVE); exit 130' INT TERM; \
	./$(TARGET) $(RUN_ARGS); \
	status=$$?; \
	$(REMOVE); \
	exit $$status

clean:
	@$(REMOVE)

clean-target:
	@$(REMOVE) $(TARGET)

main.o: ./src/main.cpp ; $(CXX) -c $(CXXFLAGS) ./src/main.cpp -o main.o
game.o: ./src/model/game.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/game.cpp -o game.o
dariu.o: ./src/model/dariu.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/dariu.cpp -o dariu.o
tilemap.o: ./src/model/tilemap.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/tilemap.cpp -o tilemap.o
tools.o: ./src/model/tools.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/tools.cpp -o tools.o
actor.o: ./src/model/actor.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/actor.cpp -o actor.o
animation.o: ./src/model/animation.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/animation.cpp -o animation.o
score.o: ./src/model/score.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/score.cpp -o score.o
enimies.o: ./src/model/enimies.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/enimies.cpp -o enimies.o
bulletgun.o: ./src/model/bulletgun.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/bulletgun.cpp -o bulletgun.o
plataform.o: ./src/model/plataform.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/plataform.cpp -o plataform.o
sounds.o: ./src/model/sounds.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/sounds.cpp -o sounds.o
rect.o: ./src/model/rect.cpp ; $(CXX) -c $(CXXFLAGS) ./src/model/rect.cpp -o rect.o
