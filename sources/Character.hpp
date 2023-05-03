#ifndef CHAR_HPP
#define CHAR_HPP
using namespace std;
#include <string>
#include "Point.hpp"

namespace ariel {
    class Character {
        private:
            string name;
            Point pos;
            int healthPoints;
        
        public:
            Character(string name, Point pos, int healthPoints) : name(name), pos(pos), healthPoints(healthPoints) {} ;
            Character() : name(""), healthPoints(100), pos(Point(0,0)) {} ;

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

            //edit
            void print();
    };
}
#endif