#ifndef SOUNDS_H
#define SOUNDS_H

#include <SFML/Audio.hpp>

class Sounds {
   public:
    Sounds();

    sf::SoundBuffer jump_buffer;
    sf::Sound jump_sound;

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
};
#endif
