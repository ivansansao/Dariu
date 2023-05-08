#!sh
# mkdir build
# cd build
# cmake --build .
# make
# ./Dariu
# cd ..

# g++ src/main.cpp src/model/game.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio && ./a.out

pwd
rm -f dariu > /dev/null
rm -f *.o > /dev/null
# cd src
make
# cd ..
rm -f *.o > /dev/null

