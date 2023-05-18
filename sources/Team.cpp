#include "Team.hpp"

namespace ariel
{
    Team::Team(Character *leader) : leader(leader)
    {
        this->numCowboys = 0;
        this->add(leader);
    }

    Team::~Team()
    {
        // Deallocate the memory of the characters
        for (Character *member : members)
        {
            delete member;
        }
    }

    void Team::add(Character *member)
    {
        add_validation(member, this->getMembers());

        if (dynamic_cast<Ninja *>(member) != nullptr)
        {
            // member is a Ninja
            this->members.push_back(member);
            member->joinedTeam();
        }
        else if (dynamic_cast<Cowboy *>(member) != nullptr)
        {
            // member is a Cowboy
            members.insert(members.begin() + numCowboys, member);
            this->numCowboys += 1;
            member->joinedTeam();
        }
        else
        {
            throw runtime_error("A character must be cowboy or ninja");
        }
    }

    void Team::add_back(Character *member) { // In practice, only for team2 use it
        add_validation(member, this->getMembers());
        this->members.push_back(member);
    }

    void Team::add_validation(Character *member, vector<Character*> members)
    {
        if (member->isInTeam())
        {
            throw runtime_error("Character can be only in one team");
        }

        if (members.size() >= MEMBERS_LIMIT)
        {
            throw runtime_error("Team can has only" + to_string(MEMBERS_LIMIT) + " members");
        }

        if (!member->isAlive())
        {
            throw runtime_error("A dead character can't join a team");
        }
    }

    void Team::attack(Team *enemy_team)
    {
        if (enemy_team == nullptr) {
            throw invalid_argument("Can't work with nullptr");
        }

        if (this == enemy_team)
        {
            throw runtime_error("Team can't attack itself");
        }

        if (enemy_team->stillAlive() <= 0) {
            throw runtime_error("If all characters in team are dead, it can't be attacked");
        }

        if (this->stillAlive() <= 0)
        {
            return;
            // throw runtime_error("If all characters in team are dead, it can't attack or be attacked");
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
        for (auto member : this->members)
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
                    }
                    else if (dynamic_cast<TrainedNinja*>(member) != nullptr) {
                        TrainedNinja *ninja = dynamic_cast<TrainedNinja*>(member);
                        ninja->actionControl(target);
                        ninja->raiseDmgDealt(NINJA_DMG);
                    }
                    else {
                        OldNinja *ninja = dynamic_cast<OldNinja*>(member);
                        ninja->actionControl(target);
                        ninja->raiseDmgDealt(NINJA_DMG);
                    }
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
        int alive_members = 0;

        for (auto member : this->members)
        {
            if (member->isAlive())
            {
                alive_members++;
            }
        }
        return alive_members;
    }

    void Team::print()
    {
        cout << "Team (" << this->getLeader()->getName();
        cout << ") has " << this->stillAlive() << " / " << this->getMembers().size() << " members alive" << endl;
        for (auto member : this->members)
        {
            cout << member->print() << endl;
        }
    }

    Character *Team::getLeader()
    {
        return this->leader;
    }

    vector<Character*> Team::getMembers() {
        return this->members;
    }
}
