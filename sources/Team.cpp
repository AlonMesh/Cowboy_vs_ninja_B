#include "Team.hpp"

namespace ariel
{

    Team::Team(Character *leader) : leader(leader)
    {
        this->add(leader);
    }

    void Team::add(Character *champion)
    {
        add_validation(champion);

        if (dynamic_cast<Ninja *>(champion) != nullptr)
        {
            // champion is a Ninja
            this->champions.push_back(champion);
            champion->joinedTeam();
        }
        else if (dynamic_cast<Cowboy *>(champion) != nullptr)
        {
            // champion is a Cowboy
            champions.insert(champions.begin() + numCowboys, champion);
            this->numCowboys += 1;
            champion->joinedTeam();
        }
        else
        {
            // throw
        }
    }

    void Team::add_validation(Character *character)
    {
        if (character->isInTeam())
        {
            throw runtime_error("Character can be only in one team");
        }

        if (this->champions.size() >= 10)
        {
            throw runtime_error("Team can has only 10 members");
        }

        if (!character->isAlive())
        {
            throw runtime_error("A dead character can't join a team");
        }
    }

    void Team::attack(Team *enemy_team)
    {
        if (this == enemy_team)
        {
            throw runtime_error("Team can't attack itself");
        }

        if (this->stillAlive() <= 0 || enemy_team->stillAlive() <= 0)
        {
            throw runtime_error("If all characters in team are dead, it can't attack or be attacked");
        }

        if (!this->leader->isAlive())
        {
            // Find the closest enemy to the dead leader
            Character* newLeader = this->leader->findClosestCharacter(this->getMembers());
            // Set him new leader
            this->leader = newLeader;
        }

        // Find the closest enemy to leader of the attacking team
        // Set him new target
        Character* target = this->leader->findClosestCharacter(enemy_team->getMembers());

        // attacking
        for (auto champion : this->champions)
        {
            if (champion->isAlive())
            {
                if (dynamic_cast<Cowboy *>(champion) != nullptr)
                {
                    Cowboy *cowboy = dynamic_cast<Cowboy *>(champion);
                    if (cowboy->hasboolets())
                    {
                        cowboy->shoot(target);
                    }
                    else
                    {
                        cowboy->reload();
                    }
                }
                else
                {
                    Ninja *ninja = dynamic_cast<Ninja *>(champion);
                    ninja->actionControl(target);
                }

                if (!target->isAlive()) {
                    if (enemy_team->stillAlive() == 0) {
                        break;
                    }

                    target = this->leader->findClosestCharacter(enemy_team->getMembers());                    
                }
            }
        }
    }

    int Team::stillAlive()
    {
        int alive_characters = 0;

        for (auto champion : this->champions)
        {
            if (champion->isAlive())
            {
                alive_characters++;
            }
        }
        return alive_characters;
    }

    void Team::print()
    {
        // add info about the team
        for (auto champion : this->champions)
        {
            champion->print();
        }
    }

    Character *Team::getLeader()
    {
        return this->leader;
    }

    vector<Character*> Team::getMembers() {
        return this->champions;
    }

    void Team2::add(Character *champion)
    {
        this->champions.push_back(champion);
    }

    void SmartTeam::smartOrder()
    {
        // TODO: Implement
    }

}
