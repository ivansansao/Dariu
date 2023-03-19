#include "sounds.hpp"

#include "iostream"

using namespace std;

Sounds::Sounds() {
    volume = 7.f;

    // Music

    music.openFromFile("./asset/sound/track1.ogg");
    music.setLoop(true);
    music.play();

    music_gameover.openFromFile("./asset/sound/gameover.ogg");

    music_gamewin.openFromFile("./asset/sound/gamewin.ogg");
    music_gamewin.setLoop(true);

    // Effects
    jump_buffer.loadFromFile("./asset/sound/jump.ogg");
    jump_sound.setBuffer(jump_buffer);

    dooropen.loadFromFile("./asset/sound/dooropen.ogg");
    dooropen_sound.setBuffer(dooropen);

    fired.loadFromFile("./asset/sound/fired.ogg");
    fired_sound.setBuffer(fired);

    crash.loadFromFile("./asset/sound/crash.ogg");
    crash_sound.setBuffer(crash);

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

    enimydie.loadFromFile("./asset/sound/enimydie.ogg");
    enimydie_sound.setBuffer(enimydie);

    levelcomplete.loadFromFile("./asset/sound/levelcomplete.ogg");
    levelcomplete_sound.setBuffer(levelcomplete);
    applyVolume();
}
void Sounds::up() {
    if (volume < 100.f) volume += 1.f;
    applyVolume();
}
void Sounds::down() {
    if (volume > 0.f) volume -= 1.f;
    applyVolume();
}

void Sounds::applyVolume() {
    music.setVolume(volume);
    music_gameover.setVolume(volume);
    music_gamewin.setVolume(volume);
    jump_sound.setVolume(volume);
    dooropen_sound.setVolume(volume);
    fired_sound.setVolume(volume);
    crash_sound.setVolume(volume);
    pop_sound0.setVolume(volume);
    pop_sound1.setVolume(volume);
    pop_sound2.setVolume(volume);
    pop_sound3.setVolume(volume);
    pop_sound4.setVolume(volume);
    pop_sound5.setVolume(volume);
    pop_sound6.setVolume(volume);
    pop_sound7.setVolume(volume);
    pop_sound8.setVolume(volume);
    pop_sound9.setVolume(volume);
    enimydie_sound.setVolume(100.f);
    levelcomplete_sound.setVolume(volume);
}