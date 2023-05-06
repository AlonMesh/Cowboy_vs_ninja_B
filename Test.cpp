#include "doctest.h"
#include <stdexcept>
#include "sources/Team.hpp"
using namespace ariel;
using namespace std;
#include <cmath>
#include <vector>

TEST_CASE("Point initialize") {
    // Default constructor
    Point p1 = Point();
    CHECK_EQ(p1.get_x(), 0.0);
    CHECK_EQ(p1.get_y(), 0.0);

    // Constructor with two doubles
    Point p2(1.0, 2.0);
    CHECK_EQ(p2.get_x(), 1.0);
    CHECK_EQ(p2.get_y(), 2.0);

    // Verify that the default constructor is equivalent to the constructor with two zeros
    Point p3(0.0, 0.0);
    CHECK_EQ(p1.get_x(), p3.get_x());
    CHECK_EQ(p1.get_y(), p3.get_x());

    /* The Point class allows for convenient initialization using two integers
    which are automatically converted to doubles. This test simply verifies
    that this automatic conversion works as expected.*/
    Point p(3, 4);
    CHECK_EQ(p.get_x(), static_cast<double>(3));
    CHECK_EQ(p.get_y(), static_cast<double>(4));
}

TEST_CASE("Distance between points") {
    Point a(1, 2);
    Point b(4, 6);
    Point c(1, 2);

    // The distance between a point and itself should be zero
    CHECK_EQ(a.distance(a), 0.0);

    // The distance between identical points should be zero
    CHECK_EQ(a.distance(c), 0.0);

    // Distance should be symmetric
    CHECK_EQ(a.distance(b), b.distance(a));

    // Distance should be calculated correctly
    CHECK_EQ(a.distance(b), 5.0);

    b = Point(3, 5); // Reset

    // Distance between a and b should be the square root of 13
    CHECK_EQ(a.distance(b), sqrt(13.0));

    // Additional test with arbitrary double values
    Point d(2, 8);
    Point e(9, 4);
    CHECK_EQ(d.distance(e), 8.94427191);
}

TEST_CASE("moveTowards function") {
    Point currentPoint(0, 0);
    Point targetPoint(5, 0);
    int distance = 5;

    Point resultPoint = Point::moveTowards(currentPoint, targetPoint, distance);

    // If 'currentPoint' is exactly 'distance' away from 'targetPoint', return 'targetPoint'.
    CHECK_EQ(resultPoint.get_x(), targetPoint.get_x());
    CHECK_EQ(resultPoint.get_y(), targetPoint.get_y());

    // Reset
    Point currentPoint(0, 0);
    Point targetPoint(5, 5); // Real distance is 7.07... 
    int distance = 8;

    Point resultPoint = Point::moveTowards(currentPoint, targetPoint, distance);

    // If 'currentPoint' is already within 'distance' of 'targetPoint', return 'targetPoint'.
    CHECK(resultPoint.get_x() == targetPoint.get_x());
    CHECK(resultPoint.get_y() == targetPoint.get_y());

    // Reset
    Point currentPoint(0, 0);
    Point targetPoint(10, 10);
    int distance = 5;

    Point resultPoint = Point::moveTowards(currentPoint, targetPoint, distance);

    // Verify that the 'distance' is now 5.0
    CHECK_EQ(resultPoint.distance(currentPoint), 5.0);

    // Verify that 'resultPoint' is on the line connecting 'currentPoint' and 'targetPoint'
    CHECK(resultPoint.isOnLine(currentPoint, targetPoint));

    // Verify that 'resultPoint' is in 'distance' away from 'currentPoint'.
    CHECK_EQ(resultPoint.distance(currentPoint), 5.0);
}

TEST_CASE("Character initialization") {
    Character* champ = new Character("Champ", Point(0, 0), 100);

    // Name, location, and HP were set correctly
    CHECK_EQ(champ->getName(), "Champ");
    CHECK_EQ(champ->getLocation(), Point(0, 0));
    CHECK_EQ(champ->getHealthPoints(), 100);

    // The created Character is alive
    CHECK(champ->isAlive());

    delete champ;
}

TEST_CASE("Character hit()") {
    Character* champ = new Character("Champ", Point(0, 0), 100);
    
    // Hitting a 'champ' by 20 HP will leave him with 80 and still alive
    champ->hit(20);
    CHECK_EQ(champ->getHealthPoints(), 80);
    CHECK(champ->isAlive());

    // Hitting a 'champ' by 80 HP will leave him with 0 and kill him
    champ->hit(80);
    CHECK_EQ(champ->getHealthPoints(), 80);
    CHECK_FALSE(champ->isAlive());

    // Can't hit a dead Character
    CHECK_THROWS(champ->hit(10));

    Character champ("Champ", Point(0, 0), 100); // Reset

    // Can't hit with a negative number (No heals allowed)
    CHECK_THROWS(champ->hit(-10));

    // Hitting a Character with more HP than he has left will kill him
    CHECK_NOTHROW(champ->hit(110));
    CHECK_FALSE(champ->isAlive());

    delete champ;
}

TEST_CASE("distance of Character") { // *************
    Character c1("Champ", Point(0, 0), 100);
    Character c2("Coco", Point(1, 0), 100);
    Character* c3 = new Character("Candy", Point(0, 0), 100);

    // Distance is simetric
    CHECK_EQ(c1.distance(&c2), c2.distance(&c1));

    // Character's distance is like Point's distance
    CHECK_EQ(c1.distance(&c2), c1.getLocation().distance(c2.getLocation()));

    // A 
    CHECK_EQ(c1.distance(c3), 0.0);
}

TEST_CASE("Cowboy initialization") {
    Cowboy* cowboy1 = new Cowboy("Cow", Point());

    // Character's fields are like expected when creating a Cowboy
    CHECK_EQ(cowboy1->getName(), "Cow");
    CHECK_EQ(cowboy1->getLocation(), Point(0, 0));
    CHECK_EQ(cowboy1->getHealthPoints(), 110); // A cowboy has 110 HP

    // Cowboy's fields are like expected when creating a Cowboy
    CHECK_EQ(cowboy1->getAmmo(), 6);
    CHECK(cowboy1->isAlive());
    CHECK(cowboy1->hasboolets());

    // Clerify that Cowboy is an instance of Character. 
    // Implemented by downcast a Character pointer to Cowboy pointer.
    Character* character_ptr = new Cowboy();
    Cowboy* cowboy_ptr = dynamic_cast<Cowboy*>(character_ptr);
    CHECK(cowboy_ptr != nullptr);

    delete cowboy1;
    delete character_ptr;
    delete cowboy_ptr;
}

TEST_CASE("Cowboy shooting") {
    Cowboy* cowboy1 = new Cowboy("Cow", Point());
    Cowboy* cowboy2 = new Cowboy("Enemy", Point(1, 1));

    cowboy1->shoot(cowboy2);

    // 'cowboy1' shoots 'cowboy2' and uses 1 bullet; 'cowboy2' loses 10 HP.
    CHECK_EQ(cowboy1->getAmmo(), 5);
    CHECK_EQ(cowboy1->hasboolets(), true);
    CHECK_EQ(cowboy2->getHealthPoints(), 100);

    // Use all the ammo
    for (size_t i = 0; i < 5; i++) {
        cowboy1->shoot(cowboy2);
    }

    // 'cowboy1' has no bullets left
    CHECK_EQ(cowboy1->getAmmo(), 0);
    CHECK_EQ(cowboy1->hasboolets(), false);

    // Cowboy can't shoot if he has no bullets
    CHECK_THROWS(cowboy1->shoot(cowboy2)); // which error?***********

    // 'cowboy1' reloads and has 6 bullets again
    cowboy1->reload();
    CHECK_EQ(cowboy1->getAmmo(), 6);
    CHECK_EQ(cowboy1->hasboolets(), true);

    Cowboy* cowboy3 = new Cowboy("KillMe", Point(2, 2)); // 110 hp

    // 'cowboy1' shoots 'cowboy3' multiple times until 'cowboy3' dies
    for (size_t i = 0; i < 12; i++) {
        cowboy1->shoot(cowboy3);
        cowboy1->reload();
    }

    // 'cowboy3' is dead
    CHECK_EQ(cowboy3->getHealthPoints(), 0); 
    CHECK_FALSE(cowboy3->isAlive());

    // Edge cases:
    // Cowboy can't shoot a dead Character
    CHECK_THROWS(cowboy1->shoot(cowboy3));

    // Cowboy can't shoot himself
    CHECK_THROWS(cowboy1->shoot(cowboy1));

    // Cowboy can't reload() when he already has full ammo
    cowboy1->shoot(cowboy2);
    cowboy1->reload();
    CHECK_THROWS(cowboy1->reload());

    // Cowboy can't shoot if he's dead (reminder: 'cowboy3' is dead)
    CHECK_THROWS(cowboy3->shoot(cowboy1));

    delete cowboy1;
    delete cowboy2;
    delete cowboy3;
}

TEST_CASE("Ninja Initialization") {
    // All types of ninjas have the expected HP and speed
    YoungNinja* ninja1 = new YoungNinja("a", Point(1, 1));
    CHECK_EQ(ninja1->getHealthPoints(), 100);
    CHECK_EQ(ninja1->getSpeed(), 14);

    TrainedNinja* ninja2 = new TrainedNinja("b", Point(2, 2));
    CHECK_EQ(ninja2->getHealthPoints(), 120);
    CHECK_EQ(ninja2->getSpeed(), 12);

    OldNinja* ninja3 = new OldNinja("c", Point(3, 3));
    CHECK_EQ(ninja3->getHealthPoints(), 150);
    CHECK_EQ(ninja3->getSpeed(), 8);

    delete ninja1;
    delete ninja2;
    delete ninja3;

    // All types of ninjas are instance of Ninja class
    Ninja* ninja_ptr1 = new YoungNinja();
    YoungNinja* young_ptr = dynamic_cast<YoungNinja*>(ninja_ptr1);
    CHECK(young_ptr != nullptr);

    Ninja* ninja_ptr2 = new TrainedNinja();
    TrainedNinja* trained_ptr = dynamic_cast<TrainedNinja*>(ninja_ptr2);
    CHECK(trained_ptr != nullptr);

    Ninja* ninja_ptr3 = new OldNinja();
    OldNinja* old_ptr = dynamic_cast<OldNinja*>(ninja_ptr3);
    CHECK(old_ptr != nullptr);

    delete ninja_ptr1;
    delete ninja_ptr2;
    delete ninja_ptr3;
}

TEST_CASE("Ninja move and slash functions") {
    YoungNinja* ninja1 = new YoungNinja("a", Point());
    Cowboy* enemy1 = new Cowboy("Enemy", Point(10, 10));
    // Distance now: 14.14213 / ninja1 speed: 14

    // Ninja can't slash an enemy if he's more than 1 distance away
    CHECK_THROWS(ninja1->slash(enemy1));

    ninja1->move(enemy1); // Current distace: 0.14213

    // Ninja can slash an enemy if he's less than 1 distance away
    CHECK_NOTHROW(ninja1->slash(enemy1));
    
    // Ninja's slash() should deal 13 damage
    int expectedHP = enemy1->getHealthPoints() - 13; // if it is 31 instead of 13, change it.
    ninja1->slash(enemy1);
    CHECK_EQ(enemy1->getHealthPoints(), expectedHP);

    delete ninja1;
    delete enemy1;

    TrainedNinja* ninja2 = new TrainedNinja("a", Point());
    Cowboy* enemy2 = new Cowboy("Enemy", Point(5, 12));
    // Distance now: 13 / ninja1 speed: 12

    ninja2->move(enemy2); // Current distace: 1

    // Ninja can't slash an enemy if he's exactly 1 distance away
    CHECK_THROWS(ninja2->slash(enemy2));

    // Ninja can't slash himself
    CHECK_THROWS(ninja2->slash(ninja2));

    // Ninja can't move throw himself
    CHECK_THROWS(ninja2->move(ninja2));

    delete ninja2;
    delete enemy2;
}

TEST_CASE("team init") {
    Cowboy* cowboy1 = new Cowboy("Champ", Point());
    Team team1(cowboy1);

    // Basic funcitons:
    CHECK_EQ(team1.stillAlive(), 1);
    CHECK_EQ(team1.getLeader(), cowboy1);

    //more???

    delete cowboy1;
}

TEST_CASE("Team add() and stillAlive() functions") {
    // Set up team with a leader
    Cowboy* cowboy1 = new Cowboy("Champ", Point());
    Team team1(cowboy1);
    
    // Basic add() should increase number of team members
    Cowboy* cowboy2 = new Cowboy("Coco", Point());
    team1.add(cowboy2);
    CHECK_EQ(team1.stillAlive(), 2);

    // Team can't add the same Character twice
    CHECK_THROWS(team1.add(cowboy1)); // Leader
    CHECK_THROWS(team1.add(cowboy2)); // Member

    // Team can't contain more than 10 Characters
    for (size_t i = 0; i < 8; i++) {
        team1.add(new Cowboy("Same", Point()));
    }

    CHECK_EQ(team1.stillAlive(), 10);

    Cowboy* cowboy3 = new Cowboy("Candy", Point());
    CHECK_THROWS(team1.add(cowboy3));

    // Team can't add a Character that's already in another team
    Team team2(cowboy3);
    CHECK_THROWS(team2.add(cowboy1)); // Leader
    CHECK_THROWS(team2.add(cowboy2)); // Member

    // Team can't be created if the first Leader is in another team
    CHECK_THROWS(Team(cowboy1)); // Leader
    CHECK_THROWS(Team(cowboy2)); // Member

    // If a Character is dead, he is no longer part of the team
    cowboy2->hit(999);
    CHECK_EQ(team1.stillAlive(), 9);

    // If the leader of a team is dead and there are more members, there will be new leader
    cowboy1->hit(999);
    CHECK_NE(team1.getLeader(), cowboy1);
    CHECK_NE(team1.getLeader(), nullptr);
}

TEST_CASE("Team attack() function") {

}