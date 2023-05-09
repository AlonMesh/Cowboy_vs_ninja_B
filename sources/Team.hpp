#ifndef TEAM_HPP
#define TEAM_HPP
#include "Point.hpp"
#include "Character.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include <vector>

namespace ariel
{
    class Team
    {
    protected:
        Character *leader;
        vector<Character *> champions;

    private:
        int numCowboys;

    public:
        Team(Character *leader);

        virtual ~Team() = default;

        // Insert a Character to a team
        virtual void add(Character *character);

        // mine
        void add_validation(Character *character);

        // edit
        void attack(Team *enemy_team);

        // Returns the amout of alive champions in team
        int stillAlive();

        // edit
        void print();

        // mine
        Character *getLeader();

        // mine
        vector<Character*> getMembers();
    };

    class Team2 : public Team
    {
        void add(Character *character) override;
    };

    class SmartTeam : public Team
    {
        void smartOrder();
    };
}

#endif