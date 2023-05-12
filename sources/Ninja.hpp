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
            // A virtual destructor for the Ninja class.
            virtual ~Ninja() = default;

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

            // A pure virtual function that prints the ninja's details
            virtual void print() const = 0;
    };

    class YoungNinja : public Ninja {
        public:
            YoungNinja(string name, Point location) : Ninja(name, location, YOUNG_NINJA_HP, YOUNG_NINJA_SPEED) {};
            YoungNinja() : Ninja("", Point(), YOUNG_NINJA_HP, YOUNG_NINJA_SPEED) {};

            virtual ~YoungNinja() = default;

        void print() const override {
            cout << "\t" << this->name << " (YoungNinja):" << endl;
            cout << "\t\tStatus: " << (this->isAlive() ? "Alive" : "Dead") << " (" << getHealthPoints() << " / " << YOUNG_NINJA_HP << ")" << endl;
            cout << "\t\tLocation: ";
            getLocation().print();
            cout << endl;
        }
    };

        class TrainedNinja : public Ninja {
        public:
            TrainedNinja(string name, Point location) : Ninja(name, location, TRAINED_NINJA_HP, TRAINED_NINJA_SPEED) {};
            TrainedNinja() : Ninja("", Point(), TRAINED_NINJA_HP, TRAINED_NINJA_SPEED) {};

            virtual ~TrainedNinja() = default;

        void print() const override {
            cout << "\t" << this->name << " (TrainedNinja):" << endl;
            cout << "\t\tStatus: " << (this->isAlive() ? "Alive" : "Dead") << " (" << getHealthPoints() << " / " << TRAINED_NINJA_HP << ")" << endl;
            cout << "\t\tLocation: ";
            getLocation().print();
            cout << endl;
        }
    };

        class OldNinja : public Ninja {
        public:
            OldNinja(string name, Point location) : Ninja(name, location, OLD_NINJA_HP, OLD_NINJA_SPEED) {};
            OldNinja() : Ninja("", Point(), OLD_NINJA_HP, OLD_NINJA_SPEED) {};

            virtual ~OldNinja() = default;

        void print() const override {
            cout << "\t" << this->name << " (OldNinja):" << endl;
            cout << "\t\tStatus: " << (this->isAlive() ? "Alive" : "Dead") << " (" << getHealthPoints() << " / " << OLD_NINJA_HP << ")" << endl;
            cout << "\t\tLocation: ";
            getLocation().print();
            cout << endl;
        }
    };
}

#endif