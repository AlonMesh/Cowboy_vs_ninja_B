#ifndef NINJA_HPP
#define NINJA_HPP
#include "Character.hpp"
#define YOUNG_NINJA_HP 100
#define YOUNG_NINJA_SPEED 14
#define TRAINED_NINJA_HP 120
#define TRAINED_NINJA_SPEED 12
#define OLD_NINJA_HP 150
#define OLD_NINJA_SPEED 8
#define NINJA_DMG 13

namespace ariel {
    class Ninja : public Character {

        private:
            int speed;
        
        public:
            // "Superior" Consturctor of all ninjas
            Ninja(string name, Point location, int healthPoints, int speed);
            
            virtual ~Ninja() = default;

            // Moving throw a given enemy
            void move(Character* enemy);
            
            // Deal massive damage to an enemey if he's close enough
            void slash(Character* enemy);

            // mine
            int getSpeed();

            // mine
            void actionControl(Character* enemy);
    };

    class YoungNinja : public Ninja {
        public:
            YoungNinja(string name, Point location) : Ninja(name, location, YOUNG_NINJA_HP, YOUNG_NINJA_SPEED) {};
            YoungNinja() : Ninja("", Point(), YOUNG_NINJA_HP, YOUNG_NINJA_SPEED) {};

            virtual ~YoungNinja() = default;
    };

        class TrainedNinja : public Ninja {
        public:
            TrainedNinja(string name, Point location) : Ninja(name, location, TRAINED_NINJA_HP, TRAINED_NINJA_SPEED) {};
            TrainedNinja() : Ninja("", Point(), TRAINED_NINJA_HP, TRAINED_NINJA_SPEED) {};

            virtual ~TrainedNinja() = default;
    };

        class OldNinja : public Ninja {
        public:
            OldNinja(string name, Point location) : Ninja(name, location, OLD_NINJA_HP, OLD_NINJA_SPEED) {};
            OldNinja() : Ninja("", Point(), OLD_NINJA_HP, OLD_NINJA_SPEED) {};

            virtual ~OldNinja() = default;
    };
}

#endif