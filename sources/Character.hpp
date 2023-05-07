#ifndef CHAR_HPP
#define CHAR_HPP
#include <string>
#include "Point.hpp"
#define DEFAULT_HP 100
using namespace std;
namespace ariel {
    class Character {
        private:
            string name;
            Point location;
            int healthPoints;
        
        public:
            Character(const string& name, Point location, int healthPoints) : name(name), location(location), healthPoints(healthPoints) {} ;
            Character() : name(""), healthPoints(DEFAULT_HP), location(Point(0,0)) {} ;
            virtual ~Character() = default;

            // Copy Constructor
            Character(const Character& other) {
                name = other.name;
                location = other.location;
                healthPoints = other.healthPoints;
            }

            // Copy Assignment Operator
            Character& operator=(const Character& other) {
                if (this == &other) {
                    return *this;
                }
                name = other.name;
                location = other.location;
                healthPoints = other.healthPoints;
                return *this;
            }

            // Move Constructor
            Character(Character&& other) noexcept {
                name = move(other.name);
                location = move(other.location);
                healthPoints = move(other.healthPoints);
            }

            // Move Assignment Operator
            Character& operator=(Character&& other) noexcept {
                if (this == &other) {
                    return *this;
                }
                name = move(other.name);
                location = move(other.location);
                healthPoints = move(other.healthPoints);
                return *this;
            }

            // Returns true if the Character is still alive (more than 0 hp)
            bool isAlive();

            // Returns the distance between this Character and a given Character
            double distance(Character* other);

            // Decrase the hp of a Character by a given int
            void hit(int damage);

            // Returns the name of the Character
            string getName();

            // Returns the position of the Character
            Point getLocation();

            // mine
            int getHealthPoints();

            //edit
            void print();
    };
}
#endif