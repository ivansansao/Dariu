#include "sounds.hpp"

#include "iostream"

using namespace std;

Sounds::Sounds()
    : jump_sound(jump_buffer),
      chain_sound(chain_buffer),
      shot_sound(shot_buffer),
      jetpack_sound(jetpack_buffer),
      fired_sound(fired),
      dooropen_sound(dooropen),
      crash_sound(crash),
      carry_sound(carry),
      drop_sound(drop),
      pop_sound0(pop),
      pop_sound1(pop),
      pop_sound2(pop),
      pop_sound3(pop),
      pop_sound4(pop),
      pop_sound5(pop),
      pop_sound6(pop),
      pop_sound7(pop),
      pop_sound8(pop),
      pop_sound9(pop),
      enimydie_sound(enimydie),
      enimydiedemoin_sound(enimydiedemoin),
      enemy_will_eat_salad_sound(enemy_will_eat_salad),
      enimy_what_i_did_sound(enimy_what_i_did),
      enimy_are_you_crazy_sound(enimy_are_you_crazy),
      get_glas_sound0(get_glas),
      get_glas_sound1(get_glas),
      get_glas_sound2(get_glas),
      get_glas_sound3(get_glas),
      get_glas_sound4(get_glas),
      get_glas_sound5(get_glas),
      get_glas_sound6(get_glas),
      get_glas_sound7(get_glas),
      get_glas_sound8(get_glas),
      get_glas_sound9(get_glas),
      enimydiein321_sound(enimydiein321),
      enimydieinfernu_sound(enimydieinfernu),
      enimydieraul_sound(enimydieraul),
      enimydievendoluz_sound(enimydievendoluz),
      getjetpack_sound(getjetpack),
      getgun_sound(getgun),
      grabammo_sound(grabammo),
      grabflower_sound(grabflower),
      levelcomplete_sound(levelcomplete) {
    volume_music = 30.f;
    volume_effect = 50.f;

    // Music

    (void)music.openFromFile("./src/asset/sound/track1.ogg");
    music.setLooping(true);

    (void)music_gameover.openFromFile("./src/asset/sound/gameover.ogg");

    (void)music_gamewin.openFromFile("./src/asset/sound/gamewin.ogg");
    music_gamewin.setLooping(true);

    // Effects

    (void)chain_buffer.loadFromFile("./src/asset/sound/chain.ogg");
    chain_sound.setBuffer(chain_buffer);

    (void)shot_buffer.loadFromFile("./src/asset/sound/shot.ogg");
    shot_sound.setBuffer(shot_buffer);

    (void)jump_buffer.loadFromFile("./src/asset/sound/jump.ogg");
    jump_sound.setBuffer(jump_buffer);

    (void)jetpack_buffer.loadFromFile("./src/asset/sound/Jetpack.ogg");
    jetpack_sound.setBuffer(jetpack_buffer);
    jetpack_sound.setLooping(true);

    (void)dooropen.loadFromFile("./src/asset/sound/dooropen.ogg");
    dooropen_sound.setBuffer(dooropen);

    (void)fired.loadFromFile("./src/asset/sound/fired.ogg");
    fired_sound.setBuffer(fired);

    (void)crash.loadFromFile("./src/asset/sound/brickbreak.ogg");
    crash_sound.setBuffer(crash);

    (void)carry.loadFromFile("./src/asset/sound/carry.ogg");
    carry_sound.setBuffer(carry);
    carry_sound.setLooping(true);

    (void)drop.loadFromFile("./src/asset/sound/drop.ogg");
    drop_sound.setBuffer(drop);

    (void)pop.loadFromFile("./src/asset/sound/pop.ogg");
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

    (void)enimydie.loadFromFile("./src/asset/sound/enimydie.ogg");
    enimydie_sound.setBuffer(enimydie);

    (void)enimydiedemoin.loadFromFile("./src/asset/sound/enimydiedemoin.ogg");
    enimydiedemoin_sound.setBuffer(enimydiedemoin);

    (void)enemy_will_eat_salad.loadFromFile("./src/asset/sound/will_eat_salad.ogg");
    enemy_will_eat_salad_sound.setBuffer(enemy_will_eat_salad);
    (void)enimy_what_i_did.loadFromFile("./src/asset/sound/what_i_did.ogg");
    enimy_what_i_did_sound.setBuffer(enimy_what_i_did);
    (void)enimy_are_you_crazy.loadFromFile("./src/asset/sound/are_you_crazy.ogg");
    enimy_are_you_crazy_sound.setBuffer(enimy_are_you_crazy);
    (void)get_glas.loadFromFile("./src/asset/sound/get_glas.ogg");
    get_glas_sound0.setBuffer(get_glas);
    get_glas_sound1.setBuffer(get_glas);
    get_glas_sound2.setBuffer(get_glas);
    get_glas_sound3.setBuffer(get_glas);
    get_glas_sound4.setBuffer(get_glas);
    get_glas_sound5.setBuffer(get_glas);
    get_glas_sound6.setBuffer(get_glas);
    get_glas_sound7.setBuffer(get_glas);
    get_glas_sound8.setBuffer(get_glas);
    get_glas_sound9.setBuffer(get_glas);

    (void)enimydiein321.loadFromFile("./src/asset/sound/enimydiein321.ogg");
    enimydiein321_sound.setBuffer(enimydiein321);
    (void)enimydieinfernu.loadFromFile("./src/asset/sound/enimydieinfernu.ogg");
    enimydieinfernu_sound.setBuffer(enimydieinfernu);
    (void)enimydieraul.loadFromFile("./src/asset/sound/enimydieraul.ogg");
    enimydieraul_sound.setBuffer(enimydieraul);
    (void)enimydievendoluz.loadFromFile("./src/asset/sound/enimydievendoluz.ogg");
    enimydievendoluz_sound.setBuffer(enimydievendoluz);

    (void)grabammo.loadFromFile("./src/asset/sound/grabammo.ogg");
    grabammo_sound.setBuffer(grabammo);
    (void)grabflower.loadFromFile("./src/asset/sound/grabflower.ogg");
    grabflower_sound.setBuffer(grabflower);

    (void)getjetpack.loadFromFile("./src/asset/sound/getjetpack.ogg");
    getjetpack_sound.setBuffer(getjetpack);
    (void)getgun.loadFromFile("./src/asset/sound/getgun.ogg");
    getgun_sound.setBuffer(getgun);

    (void)levelcomplete.loadFromFile("./src/asset/sound/levelcomplete.ogg");
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
    carry_sound.setVolume(volume_effect);
    drop_sound.setVolume(volume_effect);
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

    enimydiedemoin_sound.setVolume(volume_effect);

    enemy_will_eat_salad_sound.setVolume(volume_effect);
    enimy_what_i_did_sound.setVolume(volume_effect);
    enimy_are_you_crazy_sound.setVolume(volume_effect);

    get_glas_sound0.setVolume(volume_effect);
    get_glas_sound1.setVolume(volume_effect);
    get_glas_sound2.setVolume(volume_effect);
    get_glas_sound3.setVolume(volume_effect);
    get_glas_sound4.setVolume(volume_effect);
    get_glas_sound5.setVolume(volume_effect);
    get_glas_sound6.setVolume(volume_effect);
    get_glas_sound7.setVolume(volume_effect);
    get_glas_sound8.setVolume(volume_effect);
    get_glas_sound9.setVolume(volume_effect);

    enimydiein321_sound.setVolume(volume_effect);
    enimydieinfernu_sound.setVolume(volume_effect);
    enimydieraul_sound.setVolume(volume_effect);
    enimydievendoluz_sound.setVolume(volume_effect);
    grabammo_sound.setVolume(volume_effect);
    grabflower_sound.setVolume(volume_effect);
    getjetpack_sound.setVolume(volume_effect);
    getgun_sound.setVolume(volume_effect);
}

void Sounds::playGetGlas() {
    if (this->get_glas_sound0.getStatus() == sf::SoundSource::Status::Stopped) {
        this->get_glas_sound0.play();
    } else if (this->get_glas_sound1.getStatus() == sf::SoundSource::Status::Stopped) {
        this->get_glas_sound1.play();
    } else if (this->get_glas_sound2.getStatus() == sf::SoundSource::Status::Stopped) {
        this->get_glas_sound2.play();
    } else if (this->get_glas_sound3.getStatus() == sf::SoundSource::Status::Stopped) {
        this->get_glas_sound3.play();
    } else if (this->get_glas_sound4.getStatus() == sf::SoundSource::Status::Stopped) {
        this->get_glas_sound4.play();
    } else if (this->get_glas_sound5.getStatus() == sf::SoundSource::Status::Stopped) {
        this->get_glas_sound5.play();
    } else if (this->get_glas_sound6.getStatus() == sf::SoundSource::Status::Stopped) {
        this->get_glas_sound6.play();
    } else if (this->get_glas_sound7.getStatus() == sf::SoundSource::Status::Stopped) {
        this->get_glas_sound7.play();
    } else if (this->get_glas_sound8.getStatus() == sf::SoundSource::Status::Stopped) {
        this->get_glas_sound8.play();
    } else if (this->get_glas_sound9.getStatus() == sf::SoundSource::Status::Stopped) {
        this->get_glas_sound9.play();
    }
}
