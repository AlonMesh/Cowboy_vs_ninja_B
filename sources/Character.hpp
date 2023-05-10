#ifndef CHAR_HPP
#define CHAR_HPP
#include <string>
#include <vector>
#include "Point.hpp"
#define DEFAULT_HP 100
using namespace std;

namespace ariel
{
    class Character
    {
    protected:
        string name;
        Point location;
        int healthPoints;
        bool teamMember;

    public:
        /**
         * Character constructor with name, location and health points.
         *
         * @param name The name of the character.
         * @param location The location of the character.
         * @param healthPoints The initial health points of the character.
         */
        Character(const string &name, Point location, int healthPoints);

        /**
         * Character default constructor.
         * Initializes the name to an empty string, the health points to the default value,
         * and the location to the origin (0,0).
         */
        Character();
        virtual ~Character() = default;

        // Copy Constructor
        Character(const Character &other)
        {
            name = other.name;
            location = other.location;
            healthPoints = other.healthPoints;
        }

        // Copy Assignment Operator
        Character &operator=(const Character &other)
        {
            if (this == &other)
            {
                return *this;
            }
            name = other.name;
            location = other.location;
            healthPoints = other.healthPoints;
            return *this;
        }

        // Move Constructor
        Character(Character &&other) noexcept
        {
            name = move(other.name);
            location = move(other.location);
            healthPoints = move(other.healthPoints);
        }

        // Move Assignment Operator
        Character &operator=(Character &&other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }
            name = move(other.name);
            location = move(other.location);
            healthPoints = move(other.healthPoints);
            return *this;
        }

        /**
         * Check if the Character is alive
         * @return true if the Character's health points are greater than 0, false otherwise
         */
        bool isAlive() const;

        /**
         * Calculates the distance between the current character and another character.
         * @param other A pointer to the other character.
         * @return The distance between the two characters.
         */
        double distance(Character *other);

        /**
         * Decreases the health points of the character by the given damage amount.
         * If the character's health points go below 0, isAlive() will return false.
         * @param damage the amount of damage to deal to the character
         */
        void hit(int damage);

        // Returns the name of the Character
        string getName();

        // Returns the position of the Character
        Point getLocation() const;

        // mine*****
        int getHealthPoints() const;

        // mine*******
        void setLocation(Point point);

        // mine*******
        void joinedTeam();

        bool isInTeam();

        // mine*****
        Character* findClosestCharacter(vector<Character*> characters);

        /**
         * Print information about the Character to the console, including name, status (alive/dead), health points,
         * and location.
         */
        virtual void print() const = 0; // pure virtual function
    };
}
#endif