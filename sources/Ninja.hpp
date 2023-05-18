#ifndef NINJA_HPP
#define NINJA_HPP
#include "Character.hpp"

namespace ariel {
    constexpr int YOUNG_NINJA_HP = 100;
    constexpr int YOUNG_NINJA_SPEED = 14;
    constexpr int TRAINED_NINJA_HP = 120;
    constexpr int TRAINED_NINJA_SPEED = 12;
    constexpr int OLD_NINJA_HP = 150;
    constexpr int OLD_NINJA_SPEED = 8;
    constexpr int NINJA_DMG = 40;

    class Ninja : public Character {
        private:
            int speed;
        
        protected:
            /**
             * @brief A protected constructor used only by derived classes of Ninja.
             * 
             * @param name The name of the ninja.
             * @param location The location of the ninja.
             * @param healthPoints The health points of the ninja.
             * @param speed The speed of the ninja.
             */
            Ninja(string name, Point location, int healthPoints, int speed);

        public:
            /**
             * A function that moves the ninja through a given enemy.
             * @param enemy A pointer to the enemy to move through.
             */
            void move(Character* enemy);
            
            /**
             * A function that deals massive damage to an enemy if he's close enough.
             * @param enemy A pointer to the enemy to deal damage to.
             */
            void slash(Character* enemy);

            // Returns the speed of the ninja
            int getSpeed();

            // A function that controls the ninja's action against the enemy
            void actionControl(Character* enemy);
    };
}

#endif