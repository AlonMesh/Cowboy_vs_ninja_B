#ifndef TRAINEDNINJA_HPP
#define TRAINEDNINJA_HPP
#include "Ninja.hpp"

namespace ariel {
    class TrainedNinja : public Ninja {
        public:
            TrainedNinja(string name, Point location) : Ninja(std::move(name), location, TRAINED_NINJA_HP, TRAINED_NINJA_SPEED) {};
            
            TrainedNinja() : Ninja("", Point(), TRAINED_NINJA_HP, TRAINED_NINJA_SPEED) {};

            string print() const override {
                string toString;
                if (this->isAlive()) {
                    toString += "\tN " + getName() + ":\n";
                    toString += "\t\tStatus: Alive (" + to_string(getHealthPoints()) + " / " + to_string(TRAINED_NINJA_HP) + ")\n";
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