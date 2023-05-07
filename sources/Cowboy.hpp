#ifndef COWBOY_HPP
#define COWBOY_HPP
#include "Character.hpp"
#define COWBOY_HP 110
#define COWBOY_AMMO 6

namespace ariel {
    class Cowboy : public Character {
        private:
            int ammo;

        public:
        Cowboy(const string& name, Point location) : Character(name, location, COWBOY_HP), ammo(COWBOY_AMMO) {};
        Cowboy() : Character(), ammo(COWBOY_AMMO) {}; // NO 110 sent! ***
        virtual ~Cowboy() = default;
        
        // Get a pointer to an enemy, deal him minor damge; decrease self ammo by one
        void shoot(Character* enemy);

        // Returns true if a Cowboy has bulltes
        bool hasboolets();

        // Load 6 bullets
        void reload();

        //mine
        int getAmmo();
    };
}

#endif