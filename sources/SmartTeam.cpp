#include "SmartTeam.hpp"
#include "Ninja.hpp"
#include "Character.hpp"

namespace ariel
{
    SmartTeam::SmartTeam(Character *leader) : Team(leader) {};

    void SmartTeam::attack(Team *enemy_team)
    {

        /**
         * Before each attack, calculate the nubmer of alive cowboys and create alive ninja vector
         * This will grant us quick information:
         * 1. Instant damage (by cowboys)
         * 2. Potential damage (by ninjas), limited by locations
         */
        int alive_cowboys_damage = 0;
        vector<Character *> alive_ninjas;

        for (auto *member : this->getMembers())
        {
            if (member->isAlive())
            {
                if (dynamic_cast<Cowboy *>(member) != nullptr)
                {
                    alive_cowboys_damage += COWBOY_DMG;
                }
                else if (dynamic_cast<YoungNinja *>(member) != nullptr ||
                         dynamic_cast<TrainedNinja *>(member) != nullptr ||
                         dynamic_cast<OldNinja *>(member) != nullptr)
                {
                    alive_ninjas.push_back(member);
                }
            }
        }

        // Collecting data: How much damage can be done against each enemy
        vector<int> potential_damage_by_ninjas;
        for (auto *enemy : enemy_team->getMembers())
        {
            if (enemy->isAlive())
            {
                int potential_damage_sum = 0;
                for (auto *ninja : alive_ninjas)
                {
                    if (ninja->distance(enemy) < 1)
                    {
                        potential_damage_sum += NINJA_DMG;
                    }
                }
                potential_damage_by_ninjas.push_back(potential_damage_sum);
            }

            else
            { // enemy is dead
                // -1 is a flag to alert the program to skip that cell
                // It is cuz the i'th member will have the i'th element in potential_damage_by_ninjas
                potential_damage_by_ninjas.push_back(-1);
            }
        }

        Character *target = findTarget(enemy_team->getMembers(), potential_damage_by_ninjas, alive_cowboys_damage);

        for (auto *member : this->getMembers())
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
                        alive_cowboys_damage -= COWBOY_DMG;
                    }
                    else
                    {
                        cowboy->reload();
                    }
                }
                else
                {
                    if (dynamic_cast<YoungNinja *>(member) != nullptr)
                    {
                        YoungNinja *ninja = dynamic_cast<YoungNinja *>(member);
                        ninja->actionControl(target);
                        ninja->raiseDmgDealt(NINJA_DMG);

                        // Remove it from the vector of the attacker ninjas
                        auto itt = std::find(alive_ninjas.begin(), alive_ninjas.end(), ninja);
                        if (itt != alive_ninjas.end())
                        {
                            alive_ninjas.erase(itt);
                        }

                        else if (dynamic_cast<TrainedNinja *>(member) != nullptr)
                        {
                            TrainedNinja *ninja = dynamic_cast<TrainedNinja *>(member);
                            ninja->actionControl(target);
                            ninja->raiseDmgDealt(NINJA_DMG);

                            // Remove it from the vector of the attacker ninjas
                            auto itt = std::find(alive_ninjas.begin(), alive_ninjas.end(), ninja);
                            if (itt != alive_ninjas.end())
                            {
                                auto index = std::distance(alive_ninjas.begin(), itt);
                                alive_ninjas.erase(alive_ninjas.begin() + static_cast<std::ptrdiff_t>(index));
                            }
                        }
                        else
                        {
                            OldNinja *ninja = dynamic_cast<OldNinja *>(member);
                            ninja->actionControl(target);
                            ninja->raiseDmgDealt(NINJA_DMG);

                            // Remove it from the vector of the attacker ninjas
                            auto itt = std::find(alive_ninjas.begin(), alive_ninjas.end(), ninja);
                            if (itt != alive_ninjas.end())
                            {
                                auto index = std::distance(alive_ninjas.begin(), itt);
                                alive_ninjas.erase(alive_ninjas.begin() + static_cast<std::ptrdiff_t>(index));
                            }
                        }
                    }
                }

                if (!target->isAlive())
                {
                    if (enemy_team->stillAlive() == 0)
                    {
                        break;
                    }

                    target = findTarget(enemy_team->getMembers(), potential_damage_by_ninjas, alive_cowboys_damage);
                }
            }
        }
    }

    Character *SmartTeam::findTarget(vector<Character *> enemy_team, vector<int> potential_damage_by_ninjas, int potential_damage_by_cowboys)
    {
        for (size_t i = 0; i < enemy_team.size(); i++)
        {
            auto enemy = enemy_team[i];
            int potential_damage = potential_damage_by_ninjas[i] + potential_damage_by_cowboys;

            if (enemy->isAlive())
            {
                if (enemy->getHealthPoints() < potential_damage)
                {
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
        Character *target = nullptr;
        int target_hp = 40 + 1;
        for (auto enemy : enemy_team)
        {
            if (enemy->isAlive())
            {
                YoungNinja *yn = dynamic_cast<YoungNinja *>(enemy);
                if (yn != nullptr)
                {
                    if (enemy->getHealthPoints() < target_hp)
                    {
                        target = yn;
                        target_hp = enemy->getHealthPoints();
                    }
                }
            }
        }
        if (target != nullptr)
        {
            return target;
        }

        target_hp = 40 + 1;
        for (auto enemy : enemy_team)
        {
            if (enemy->isAlive())
            {
                TrainedNinja *tn = dynamic_cast<TrainedNinja *>(enemy);
                if (tn != nullptr)
                {
                    if (enemy->getHealthPoints() < target_hp)
                    {
                        target = tn;
                        target_hp = enemy->getHealthPoints();
                    }
                }
            }
        }
        if (target != nullptr)
        {
            return target;
        }

        target_hp = OLD_NINJA_HP + 1;
        for (auto enemy : enemy_team)
        {
            if (enemy->isAlive())
            {
                OldNinja *on = dynamic_cast<OldNinja *>(enemy);
                if (on != nullptr)
                {
                    if (enemy->getHealthPoints() < target_hp)
                    {
                        target = on;
                        target_hp = enemy->getHealthPoints();
                    }
                }
            }
        }
        if (target != nullptr)
        {
            return target;
        }

        target_hp = COWBOY_HP + 1;
        for (auto enemy : enemy_team)
        {
            if (enemy->isAlive())
            {
                Cowboy *cowboy = dynamic_cast<Cowboy *>(enemy);
                if (cowboy != nullptr)
                {
                    if (enemy->getHealthPoints() < target_hp)
                    {
                        target = cowboy;
                        target_hp = enemy->getHealthPoints();
                    }
                }
            }
        }
        return target;
    }

}