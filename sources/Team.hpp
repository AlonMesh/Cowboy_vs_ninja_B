#ifndef TEAM_HPP
#define TEAM_HPP
#include "Point.hpp"
#include "Character.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include <vector>

namespace ariel {
    class Team {
        private:
            Character leader;
            vector<Character> champions;

        public:
            Team(Character leader) : leader(leader) {
                this->champions.push_back(leader);
            }

            //destructor

            // Insert a Character to a team
            void add(Character* champion);

            // edit
            void attack(Team* enemy_team);

            // Returns the amout of alive champions in team
            int stillAlive();

            // edit
            void print();

    };
}

#endif