#ifndef YOUNGNINJA_HPP
#define YOUNGNINJA_HPP
#include "Ninja.hpp"

namespace ariel {
        class YoungNinja : public Ninja {
        public:
            YoungNinja(string name, Point location) : Ninja(std::move(name), location, YOUNG_NINJA_HP, YOUNG_NINJA_SPEED) {};

            YoungNinja() : Ninja("", Point(), YOUNG_NINJA_HP, YOUNG_NINJA_SPEED) {};

            string print() const override {
                string toString;
                if (this->isAlive()) {
                    toString += "\tN " + getName() + ":\n";
                    toString += "\t\tStatus: Alive (" + to_string(getHealthPoints()) + " / " + to_string(YOUNG_NINJA_HP) + ")\n";
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