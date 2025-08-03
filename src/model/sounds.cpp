#include "sounds.hpp"

#include "iostream"

using namespace std;

Sounds::Sounds() {
    volume_music = 50.f;
    volume_effect = 50.f;

    // Music

    music.openFromFile("./src/asset/sound/track1.ogg");
    music.setLoop(true);

    music_gameover.openFromFile("./src/asset/sound/gameover.ogg");

    music_gamewin.openFromFile("./src/asset/sound/gamewin.ogg");
    music_gamewin.setLoop(true);

    // Effects

    chain_buffer.loadFromFile("./src/asset/sound/chain.ogg");
    chain_sound.setBuffer(chain_buffer);

    shot_buffer.loadFromFile("./src/asset/sound/shot.ogg");
    shot_sound.setBuffer(shot_buffer);

    jump_buffer.loadFromFile("./src/asset/sound/jump.ogg");
    jump_sound.setBuffer(jump_buffer);

    jetpack_buffer.loadFromFile("./src/asset/sound/Jetpack.ogg");
    jetpack_sound.setBuffer(jetpack_buffer);
    jetpack_sound.setLoop(true);

    dooropen.loadFromFile("./src/asset/sound/dooropen.ogg");
    dooropen_sound.setBuffer(dooropen);

    fired.loadFromFile("./src/asset/sound/fired.ogg");
    fired_sound.setBuffer(fired);

    crash.loadFromFile("./src/asset/sound/crash.ogg");
    crash_sound.setBuffer(crash);

    pop.loadFromFile("./src/asset/sound/pop.ogg");
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

    enimydie.loadFromFile("./src/asset/sound/enimydie.ogg");
    enimydie_sound.setBuffer(enimydie);

    enimydiedemoin.loadFromFile("./src/asset/sound/enimydiedemoin.ogg");
    enimydiedemoin_sound.setBuffer(enimydiedemoin);
    enimydiein321.loadFromFile("./src/asset/sound/enimydiein321.ogg");
    enimydiein321_sound.setBuffer(enimydiein321);
    enimydieinfernu.loadFromFile("./src/asset/sound/enimydieinfernu.ogg");
    enimydieinfernu_sound.setBuffer(enimydieinfernu);
    enimydieraul.loadFromFile("./src/asset/sound/enimydieraul.ogg");
    enimydieraul_sound.setBuffer(enimydieraul);
    enimydievendoluz.loadFromFile("./src/asset/sound/enimydievendoluz.ogg");
    enimydievendoluz_sound.setBuffer(enimydievendoluz);

    levelcomplete.loadFromFile("./src/asset/sound/levelcomplete.ogg");
    levelcomplete_sound.setBuffer(levelcomplete);
    applyVolume();
}
void Sounds::music_up() {
    pop_sound9.play();
    if (volume_music < 100.f) volume_music += 1.f;
    applyVolume();
}
void Sounds::music_down() {
    pop_sound9.play();
    if (volume_music > 0.f) volume_music -= 1.f;
    applyVolume();
}
void Sounds::effect_up() {
    pop_sound9.play();
    if (volume_effect < 100.f) volume_effect += 1.f;
    applyVolume();
}
void Sounds::effect_down() {
    pop_sound9.play();
    if (volume_effect > 0.f) volume_effect -= 1.f;
    applyVolume();
}

void Sounds::applyVolume() {
    music.setVolume(volume_music);
    music_gameover.setVolume(volume_music);
    music_gamewin.setVolume(volume_music);

    jetpack_sound.setVolume(volume_effect);
    jump_sound.setVolume(volume_effect);
    dooropen_sound.setVolume(volume_effect);
    fired_sound.setVolume(volume_effect);
    crash_sound.setVolume(volume_effect);
    pop_sound0.setVolume(volume_effect);
    pop_sound1.setVolume(volume_effect);
    pop_sound2.setVolume(volume_effect);
    pop_sound3.setVolume(volume_effect);
    pop_sound4.setVolume(volume_effect);
    pop_sound5.setVolume(volume_effect);
    pop_sound6.setVolume(volume_effect);
    pop_sound7.setVolume(volume_effect);
    pop_sound8.setVolume(volume_effect);
    pop_sound9.setVolume(volume_effect);
    enimydie_sound.setVolume(volume_effect);
    levelcomplete_sound.setVolume(volume_effect);
    chain_sound.setVolume(volume_effect);
    shot_sound.setVolume(volume_effect);
}