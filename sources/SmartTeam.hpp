#ifndef SMARTTEAM_HPP
#define SMARTTEAM_HPP
#include "Team.hpp"
#include <algorithm>

namespace ariel {
    /**
     * A derived class of the Team class, representing a team that attacks more strategically than a regular team.
     * The team prioritizes attacking low-health enemies, targets high damage enemies, and maximizes damage cooperation.
     * This class implements the attack method of the parent class to provide smart attack strategy.
    */
    class SmartTeam : public Team
    {
    public:
        SmartTeam(Character *leader); 
        /**
         * I conducted an analysis to determine which character type dealt the most damage in a single round.
         * To achieve this, I created 400 random teams of 10 characters, with a distribution of:
         * 40% Cowboys and 20% of each type of Ninja.
         * I recorded the winner team of each round, and calculated the amount of damage dealt by each character,
         * categorized by their class character types.
         * This enabled me to calculate the average damage each type does in each game with good probability:
         *      Cowboy:  202.74
         *      Young:   748.37
         *      Trained: 742.22
         *      Old:     848.90
         * The average damage divided by the character's HP amount:
         *      Cowboy:  1.8431
         *      Young:   7.4837
         *      Trained: 6.1852
         *      Old:     5.6593
         * (It basiclly means: for each 1 HP of a character, it deals this amount of damage)
        */
       void attack(Team *enemy_team) override;
        
        Character* findTarget(vector<Character*> enemy_team, vector<int> potential_damage_by_ninjas, int potential_damage_by_cowboys);
    };
}

#endif