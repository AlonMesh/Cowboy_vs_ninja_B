#ifndef SMARTTEAM_HPP
#define SMARTTEAM_HPP
#include "Team.hpp"
#include <algorithm>;

namespace ariel {
    /**
     * A derived class of the Team class, representing a team that attacks more strategically than a regular team.
     * The team prioritizes attacking low-health enemies, targets high damage enemies, and maximizes damage cooperation.
     * This class implements the attack method of the parent class to provide smart attack strategy.
    */
    class SmartTeam : public Team
    {
    public:
        SmartTeam(Character *leader) : Team(leader) {};

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
        void attack(Team *enemy_team) override {

            /**
             * Before each attack, calculate the nubmer of alive cowboys and create alive ninja vector
             * This will grant us quick information:
             * 1. Instant damage (by cowboys)
             * 2. Potential damage (by ninjas), limited by locations
            */ 
            int alive_cowboys_damage = 0;
            vector<Character*> alive_ninjas;

            for (auto member : this->getMembers()) {
                if (member->isAlive()) {
                    if (static_cast<Cowboy *>(member) != nullptr) {
                        alive_cowboys_damage += 10;
                    }
                    else if 
                    (static_cast<YoungNinja*>(member) != nullptr || 
                     static_cast<TrainedNinja*>(member) != nullptr ||
                     static_cast<OldNinja*>(member) != nullptr ) {
                        alive_ninjas.push_back(member);
                    }
                }
            }

            // Collecting data: How much damage can be done against each enemy
            vector<int> potential_damage_by_ninjas;
            for (auto enemy : enemy_team->getMembers()) {
                if (enemy->isAlive()) {
                    int potential_damage_sum = 0;
                    for (auto ninja : alive_ninjas) {
                        if (ninja->distance(enemy) < 1) {
                            potential_damage_sum += NINJA_DMG;
                        }
                    }
                    potential_damage_by_ninjas.push_back(potential_damage_sum);
                }

                else { // enemy is dead
                    // -1 is a flag to alert the program to skip that cell
                    // It is cuz the i'th member will have the i'th element in potential_damage_by_ninjas
                    potential_damage_by_ninjas.push_back(-1);
                }
            }

            Character* target = findTarget(enemy_team->getMembers(), potential_damage_by_ninjas, alive_cowboys_damage);
            
            for (auto member : this->getMembers())
            {
                if (member->isAlive())
                {
                    if (dynamic_cast<Cowboy *>(member) != nullptr)
                    {
                        Cowboy *cowboy = dynamic_cast<Cowboy *>(member);
                        if (cowboy->hasboolets())
                        {
                            cowboy->shoot(target);
                            cowboy->raiseDmgDealt(COWBOY_DMG);
                            alive_cowboys_damage -= 10;
                        }
                        else
                        {
                            cowboy->reload();
                        }
                    }
                    else
                    {
                        if (dynamic_cast<YoungNinja*>(member) != nullptr) {
                            YoungNinja *ninja = dynamic_cast<YoungNinja*>(member);
                            ninja->actionControl(target);
                            ninja->raiseDmgDealt(NINJA_DMG);
                            
                            // Remove it from the vector of the attacker ninjas
                            auto it = std::find(alive_ninjas.begin(), alive_ninjas.end(), ninja);
                            if (it != alive_ninjas.end()) {
                                size_t index = std::distance(alive_ninjas.begin(), it);
                                alive_ninjas.erase(alive_ninjas.begin() + index);
                            }
                        }
                        else if (dynamic_cast<TrainedNinja*>(member) != nullptr) {
                            TrainedNinja *ninja = dynamic_cast<TrainedNinja*>(member);
                            ninja->actionControl(target);
                            ninja->raiseDmgDealt(NINJA_DMG);

                            // Remove it from the vector of the attacker ninjas
                            auto it = std::find(alive_ninjas.begin(), alive_ninjas.end(), ninja);
                            if (it != alive_ninjas.end()) {
                                size_t index = std::distance(alive_ninjas.begin(), it);
                                alive_ninjas.erase(alive_ninjas.begin() + index);
                            }

                        }
                        else {
                            OldNinja *ninja = dynamic_cast<OldNinja*>(member);
                            ninja->actionControl(target);
                            ninja->raiseDmgDealt(NINJA_DMG);

                            // Remove it from the vector of the attacker ninjas
                            auto it = std::find(alive_ninjas.begin(), alive_ninjas.end(), ninja);
                            if (it != alive_ninjas.end()) {
                                size_t index = std::distance(alive_ninjas.begin(), it);
                                alive_ninjas.erase(alive_ninjas.begin() + index);
                            }

                        }
                    }

                    if (!target->isAlive()) {
                        if (enemy_team->stillAlive() == 0) {
                            break;
                        }

                        target = findTarget(enemy_team->getMembers(), potential_damage_by_ninjas, alive_cowboys_damage);                   
                    }
                }
            }
        }
        
        Character* findTarget(vector<Character*> enemy_team, vector<int> potential_damage_by_ninjas, int potential_damage_by_cowboys) {
            //TODO:
                // dmg reading at the start of each findTarget...
            for (size_t i = 0; i < enemy_team.size(); i++) {
                auto enemy = enemy_team[i];
                int potential_damage = potential_damage_by_ninjas[i] + potential_damage_by_cowboys;

                if (enemy->isAlive()) {
                    if (enemy->getHealthPoints() < potential_damage) {
                        return enemy;
                    }
                }
            }

            /**
             * If the program get into this part of the code, it means that
             * the given target won't be killed this round.
             * So the given target will be chosen by:
             *      The enemy with the lowest hp by the next order:
             *      YN, TN, OL, C
            */
            Character* target = nullptr;
            int target_hp = YOUNG_NINJA_HP + 1;
            for (auto enemy : enemy_team) {
                if (enemy->isAlive()) {
                    YoungNinja* yn = dynamic_cast<YoungNinja*>(enemy);
                    if (yn != nullptr) {
                        if (enemy->getHealthPoints() < target_hp) {
                            target = yn;
                            target_hp = enemy->getHealthPoints();
                        }
                    }
                }
            }
            if (target != nullptr) {
                return target;
            }

            target_hp = TRAINED_NINJA_HP + 1;
            for (auto enemy : enemy_team) {
                if (enemy->isAlive()) {
                    TrainedNinja* tn = dynamic_cast<TrainedNinja*>(enemy);
                    if (tn != nullptr) {
                        if (enemy->getHealthPoints() < target_hp) {
                            target = tn;
                            target_hp = enemy->getHealthPoints();
                        }
                    }
                }
            }
            if (target != nullptr) {
                return target;
            }

            target_hp = OLD_NINJA_HP + 1;
            for (auto enemy : enemy_team) {
                if (enemy->isAlive()) {
                    OldNinja* on = dynamic_cast<OldNinja*>(enemy);
                    if (on != nullptr) {
                        if (enemy->getHealthPoints() < target_hp) {
                            target = on;
                            target_hp = enemy->getHealthPoints();
                        }
                    }
                }
            }
            if (target != nullptr) {
                return target;
            }

            target_hp = COWBOY_HP + 1;
            for (auto enemy : enemy_team) {
                if (enemy->isAlive()) {
                    Cowboy* cowboy = dynamic_cast<Cowboy*>(enemy);
                    if (cowboy != nullptr) {
                        if (enemy->getHealthPoints() < target_hp) {
                            target = cowboy;
                            target_hp = enemy->getHealthPoints();
                        }
                    }
                }
            }
            return target;
        }
    };
}

#endif