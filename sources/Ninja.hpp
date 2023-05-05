#ifndef NINJA_HPP
#define NINJA_HPP
#include "Character.hpp"

namespace ariel {
    class Ninja : public Character {

        private:
            int speed;
        
        public:
            // "Superior" Consturctor of all ninjas
            Ninja(string name, Point location, int healthPoints, int speed) : Character(name, location, healthPoints), speed(speed) {};
            
            // Moving throw a given enemy
            void move(Character* enemy);
            
            // Deal massive damage to an enemey if he's close enough
            void slash(Character* enemy);

            // mine
            int getSpeed();
    };

    class YoungNinja : public Ninja {
        public:
            YoungNinja(string name, Point location) : Ninja(name, location, 100, 14) {};
            YoungNinja() : Ninja("", Point(), 100, 14) {};
    };

        class TrainedNinja : public Ninja {
        public:
            TrainedNinja(string name, Point location) : Ninja(name, location, 120, 12) {};
            TrainedNinja() : Ninja("", Point(), 120, 12) {};
    };

        class OldNinja : public Ninja {
        public:
            OldNinja(string name, Point location) : Ninja(name, location, 150, 8) {};
            OldNinja() : Ninja("", Point(), 150, 8) {};
    };
}

#endif