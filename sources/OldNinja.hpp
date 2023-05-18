#ifndef OLDNINJA_HPP
#define OLDNINJA_HPP
#include "Ninja.hpp"

namespace ariel {
        class OldNinja : public Ninja {
        public:
            OldNinja(string name, Point location) : Ninja(std::move(name), location, OLD_NINJA_HP, OLD_NINJA_SPEED) {};
            
            OldNinja() : Ninja("", Point(), OLD_NINJA_HP, OLD_NINJA_SPEED) {};

            string print() const override {
                string toString;
                if (this->isAlive()) {
                    toString += "\tN " + getName() + ":\n";
                    toString += "\t\tStatus: Alive (" + to_string(getHealthPoints()) + " / " + to_string(OLD_NINJA_HP) + ")\n";
                    toString += "\t\tLocation: (" + to_string(getLocation().getx()) + ", " + to_string(getLocation().gety()) + ")\n";
                } else {
                    toString += "\tN (" + getName() + "):\n";
                    toString += "\t\tStatus: Dead\n";
                    toString += "\t\tDeath Location: (" + to_string(getLocation().getx()) + ", " + to_string(getLocation().gety()) + ")\n";
                }
                return toString;
            }
    };    
}

#endif