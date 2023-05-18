#include "Cowboy.hpp"

namespace ariel
{

    Cowboy::Cowboy(const string &name, Point location) : Character(name, location, COWBOY_HP), ammo(COWBOY_AMMO){};

    Cowboy::Cowboy() : Character(), ammo(COWBOY_AMMO){};

    void Cowboy::shoot(Character *enemy)
    {
        if (!this->isAlive())
        {
            throw runtime_error("A dead cowboy can't shoot");
        }

        if (!enemy->isAlive())
        {
            throw runtime_error("Cowboy can't shoot a dead character");
        }

        if (this == enemy)
        {
            throw runtime_error("Cowboy can't shoot himself");
        }

        if (this->ammo > 0)
        {
            enemy->hit(COWBOY_DMG);
            this->ammo -= 1;
        }
    }

    bool Cowboy::hasboolets()
    {
        return (this->getAmmo() > 0);
    }

    void Cowboy::reload()
    {
        if (this->getAmmo() < 0)
        {
            throw runtime_error("Somehow a cowboy has negative amount of ammo");
        }

        if (!this->isAlive())
        {
            throw runtime_error("A dead cowboy can't relaod");
        }

        this->ammo = 6;
    }

    int Cowboy::getAmmo()
    {
        return this->ammo;
    }

    string Cowboy::print() const
    {
        string toString;
        if (this->isAlive())
        {
            toString += "\tC " + getName() + ":\n";
            toString += "\t\tStatus: Alive (" + to_string(getHealthPoints()) + " / " + to_string(COWBOY_HP) + ")\n";
            toString += "\t\tLocation: (" + to_string(getLocation().getx()) + ", " + to_string(getLocation().gety()) + ")\n";
        }
        else
        {
            toString += "\tC (" + getName() + "):\n";
            toString += "\t\tStatus: Dead\n";
            toString += "\t\tDeath Location: (" + to_string(getLocation().getx()) + ", " + to_string(getLocation().gety()) + ")\n";
        }
        return toString;
    }

} // namespace ariel
