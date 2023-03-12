#include "sounds.hpp"

#include "iostream"

using namespace std;

Sounds::Sounds() {
    jump_buffer.loadFromFile("./asset/sound/jump.ogg");
    jump_sound.setBuffer(jump_buffer);
    jump_sound.setVolume(9.f);

    cout << "actor 2.0\n";
    dooropen.loadFromFile("./asset/sound/dooropen.ogg");
    dooropen_sound.setBuffer(dooropen);
    dooropen_sound.setVolume(10.f);

    cout << "actor 3.0\n";
    fired.loadFromFile("./asset/sound/fired.ogg");
    fired_sound.setBuffer(fired);
    fired_sound.setVolume(9.f);

    cout << "actor 4.0\n";
    crash.loadFromFile("./asset/sound/crash.ogg");
    crash_sound.setBuffer(crash);
    crash_sound.setVolume(9.f);

    cout << "actor 5.0\n";
    pop.loadFromFile("./asset/sound/pop.ogg");
    pop_sound0.setBuffer(pop);
    pop_sound1.setBuffer(pop);
    pop_sound2.setBuffer(pop);
    pop_sound3.setBuffer(pop);
    pop_sound4.setBuffer(pop);
    pop_sound5.setBuffer(pop);
    pop_sound6.setBuffer(pop);
    pop_sound7.setBuffer(pop);
    pop_sound8.setBuffer(pop);
    pop_sound9.setBuffer(pop);

    pop_sound0.setVolume(7.f);
    pop_sound1.setVolume(7.f);
    pop_sound2.setVolume(7.f);
    pop_sound3.setVolume(7.f);
    pop_sound4.setVolume(7.f);
    pop_sound5.setVolume(7.f);
    pop_sound6.setVolume(7.f);
    pop_sound7.setVolume(7.f);
    pop_sound8.setVolume(7.f);
    pop_sound9.setVolume(7.f);

    enimydie.loadFromFile("./asset/sound/enimydie.ogg");
    enimydie_sound.setBuffer(enimydie);
    enimydie_sound.setVolume(100.f);
}
