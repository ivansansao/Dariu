#pragma once

#ifndef SOUNDS_H
#define SOUNDS_H

#include <SFML/Audio.hpp>

class Sounds {
   public:
    Sounds();

    float volume_music = 7.f;
    float volume_effect = 7.f;

    // Music

    sf::Music music;
    sf::Music music_gameover;
    sf::Music music_gamewin;

    // Effects

    sf::SoundBuffer jump_buffer;
    sf::Sound jump_sound;

    sf::SoundBuffer chain_buffer;
    sf::Sound chain_sound;

    sf::SoundBuffer shot_buffer;
    sf::Sound shot_sound;

    sf::SoundBuffer jetpack_buffer;
    sf::Sound jetpack_sound;

    sf::SoundBuffer fired;
    sf::Sound fired_sound;

    sf::SoundBuffer dooropen;
    sf::Sound dooropen_sound;

    sf::SoundBuffer crash;
    sf::Sound crash_sound;

    sf::SoundBuffer pop;
    sf::Sound pop_sound0;
    sf::Sound pop_sound1;
    sf::Sound pop_sound2;
    sf::Sound pop_sound3;
    sf::Sound pop_sound4;
    sf::Sound pop_sound5;
    sf::Sound pop_sound6;
    sf::Sound pop_sound7;
    sf::Sound pop_sound8;
    sf::Sound pop_sound9;

    sf::SoundBuffer enimydie;
    sf::Sound enimydie_sound;

    sf::SoundBuffer enimydiedemoin;
    sf::Sound enimydiedemoin_sound;
    sf::SoundBuffer enimydiein321;
    sf::Sound enimydiein321_sound;
    sf::SoundBuffer enimydieinfernu;
    sf::Sound enimydieinfernu_sound;
    sf::SoundBuffer enimydieraul;
    sf::Sound enimydieraul_sound;
    sf::SoundBuffer enimydievendoluz;
    sf::Sound enimydievendoluz_sound;

    sf::SoundBuffer grabammo;
    sf::Sound grabammo_sound;
    sf::SoundBuffer grabflower;
    sf::Sound grabflower_sound;

    sf::SoundBuffer levelcomplete;
    sf::Sound levelcomplete_sound;

    void music_up();
    void music_down();
    void effect_up();
    void effect_down();
    void applyVolume();
};
#endif
