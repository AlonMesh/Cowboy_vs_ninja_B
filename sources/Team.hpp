#ifndef TEAM_HPP
#define TEAM_HPP
#include "Point.hpp"
#include "Character.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"
#include <vector>

namespace ariel
{
    constexpr int MEMBERS_LIMIT = 10;
    class Team
    {
    protected:

    private:
        int numCowboys;
        Character *leader;
        vector<Character *> members;

    public:
        Team(Character *leader);

        virtual ~Team();

        // Declare copy constructor
        Team(const Team& other) = default;

        // Declare copy assignment operator
        Team& operator=(const Team& other) = default;

        // Declare move constructor
        Team(Team&& other) noexcept = default;

        // Declare move assignment operator
        Team& operator=(Team&& other) noexcept = default;

        // Insert a Character to a team
        virtual void add(Character *member);

        // Insert a Character to a team without special logic behind it
        void add_back(Character *member);

        // mine
        static void add_validation(Character *member, vector<Character*> members);

        // edit
        virtual void attack(Team *enemy_team);

        // Returns the amout of alive members in team
        int stillAlive();

        // edit
        void print();

        // mine
        Character *getLeader();

        // mine
        vector<Character*> getMembers();
    };
}

#endif