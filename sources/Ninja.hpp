#ifndef NINJA_HPP
#define NINJA_HPP
#include "Character.hpp"

namespace ariel {
    class Ninja : public Character {

        private:
            int speed;
        
        public:
            // "Superior" Consturctor of all ninjas
            Ninja(string name, Point pos, int healthPoints, int speed) : Character(name, pos, healthPoints), speed(speed) {};
            
            // Moving throw a given enemy
            void move(Character* enemy);
            
            // Deal massive damage to an enemey if he's close enough
            void slash(Character* enemy);
    };

    class YoungNinja : public Ninja {
        public:
            YoungNinja(string name, Point pos) : Ninja(name, pos, 100, 14) {};
    };

        class TrainedNinja : public Ninja {
        public:
            TrainedNinja(string name, Point pos) : Ninja(name, pos, 120, 12) {};
    };

        class OldNinja : public Ninja {
        public:
            OldNinja(string name, Point pos) : Ninja(name, pos, 150, 8) {};
    };
}

#endif