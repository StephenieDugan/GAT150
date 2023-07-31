#pragma once
#include <random>

namespace Twili
{
    inline void seedRandom(unsigned int seed) { srand(seed); }
    inline int random() { return rand(); }
    inline int random(unsigned int max) { return rand() % max; }
    inline int random(unsigned int min, unsigned int max) { return min + random((max - min) + 1); }

    inline float randomF() { return random() / (float) RAND_MAX; }
    inline float randomF(float max) { return randomF() * max; }
    inline float randomF(float min,float max) { return min + randomF() * (max - min); }
}

