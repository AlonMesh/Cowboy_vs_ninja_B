#ifndef COWBOY_HPP
#define COWBOY_HPP
#include "Character.hpp"

namespace ariel {
    class Cowboy : public Character {
        private:
            int ammo;

        public:
        Cowboy(string name, Point pos) : Character(name, pos, 110), ammo(6) {};
        Cowboy() : Character(), ammo(0) {};

        
        // Get a pointer to an enemy, deal him minor damge; decrease self ammo by one
        void shoot(Character* enemy);

        // Returns true if a Cowboy has bulltes
        bool hasboolets();

        // Load 6 bullets
        void reload();
    };
}

#endif