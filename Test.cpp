#include "doctest.h"
#include <stdexcept>
#include "sources/Team.hpp"
using namespace ariel;
using namespace std;
#include <cmath>

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
    Character champ("Champ", Point(0, 0), 100);

    // Name, location, and health points were set correctly
    CHECK_EQ(champ.getName(), "Champ");
    CHECK_EQ(champ.getLocation(), Point(0, 0));
    CHECK_EQ(champ.getHealthPoints(), 100);

    // The created Character is alive
    CHECK(champ.isAlive());
}

TEST_CASE("hit of Character") {
    Character champ("Champ", Point(0, 0), 100);
    
    // Hitting a 'champ' by 20 HP will leave him with 80 and still alive
    champ.hit(20);
    CHECK_EQ(champ.getHealthPoints(), 80);
    CHECK(champ.isAlive());

    // Hitting a 'champ' by 80 HP will leave him with 0 and kill him
    champ.hit(80);
    CHECK_EQ(champ.getHealthPoints(), 80);
    CHECK_FALSE(champ.isAlive());

    // Can't hit a dead Character
    CHECK_THROWS(champ.hit(10));

    Character champ("Champ", Point(0, 0), 100); // Reset

    // Can't hit with a negative number (No heals allowed)
    CHECK_THROWS(champ.hit(-10));

    // Hitting a Character with more HP than he has left will kill him
    CHECK_NOTHROW(champ.hit(110));
    CHECK_FALSE(champ.isAlive());
}

TEST_CASE("distance of Character") {
    Character c1("Champ", Point(0, 0), 100);
    Character c2("Coco", Point(1, 0), 100);
    Character c3("Candy", Point(0, 0), 100);

    // Distance is simetric
    CHECK_EQ(c1.distance(&c2), c2.distance(&c1));

    // Character's distance is like Point's distance
    CHECK_EQ(c1.distance(&c2), c1.getLocation().distance(c2.getLocation()));

    // A 
    CHECK_EQ(c1.distance(&c3), 0.0);
}

TEST_CASE("Cowboy initialization") {
    Cowboy cowboy1("Cow", Point());

    // Character's fields are like expected when creating a Cowboy
    CHECK_EQ(cowboy1.getName(), "Cow");
    CHECK_EQ(cowboy1.getLocation(), Point(0, 0));
    CHECK_EQ(cowboy1.getHealthPoints(), 110); // A cowboy has 110 HP

    // Cowboy's fields are like expected when creating a Cowboy
    CHECK_EQ(cowboy1.getAmmo(), 6);
    CHECK(cowboy1.isAlive());
    CHECK(cowboy1.hasboolets());

    // Clerify that Cowboy is an instance of Character. 
    // Implemented by downcast a Character pointer to Cowboy pointer.
    Character* character_ptr = new Cowboy();
    Cowboy* cowboy_ptr = dynamic_cast<Cowboy*>(character_ptr);
    CHECK(cowboy_ptr != nullptr);
}

TEST_CASE("Cowboy shooting") {
    Cowboy cowboy1("Cow", Point());
    Cowboy cowboy2("Enemy", Point(1, 1));

    cowboy1.shoot(&cowboy2);

    // 'cowboy1' shoots 'cowboy2' and uses 1 bullet; 'cowboy2' loses 10 HP.
    CHECK_EQ(cowboy1.getAmmo(), 5);
    CHECK_EQ(cowboy1.hasboolets(), true);
    CHECK_EQ(cowboy2.getHealthPoints(), 100);

    // Use all the ammo
    for (size_t i = 0; i < 5; i++) {
        cowboy1.shoot(&cowboy2);
    }

    // 'cowboy1' has no bullets left
    CHECK_EQ(cowboy1.getAmmo(), 0);
    CHECK_EQ(cowboy1.hasboolets(), false);

    // Cowboy can't shoot if he has no bullets
    CHECK_THROWS(cowboy1.shoot(&cowboy2)); // which error?***********

    // 'cowboy1' reloads and has 6 bullets again
    cowboy1.reload();
    CHECK_EQ(cowboy1.getAmmo(), 6);
    CHECK_EQ(cowboy1.hasboolets(), true);

    Cowboy cowboy3("KillMe", Point(2, 2)); // 110 hp

    // 'cowboy1' shoots 'cowboy3' multiple times until 'cowboy3' dies
    for (size_t i = 0; i < 12; i++) {
        cowboy1.shoot(&cowboy3);
        cowboy1.reload();
    }

    // 'cowboy3' is dead
    CHECK_EQ(cowboy3.getHealthPoints(), 0); 
    CHECK_EQ(cowboy3.isAlive(), false);

    // Edge cases:
    // Cowboy can't shoot a dead Character
    CHECK_THROWS(cowboy1.shoot(&cowboy3));

    // Cowboy can't shoot himself
    CHECK_THROWS(cowboy1.shoot(&cowboy1));

    // Cowboy can't reload() when he already has full ammo
    cowboy1.shoot(&cowboy2);
    cowboy1.reload();
    CHECK_THROWS(cowboy1.reload());
}

TEST_CASE("Ninja Initialization") {
    // All types of ninjas have the expected HP and speed
    YoungNinja ninja1("a", Point(1, 1));
    CHECK_EQ(ninja1.getHealthPoints(), 100);
    CHECK_EQ(ninja1.getSpeed(), 14);

    TrainedNinja ninja2("b", Point(2, 2));
    CHECK_EQ(ninja2.getHealthPoints(), 120);
    CHECK_EQ(ninja2.getSpeed(), 12);

    OldNinja ninja3("c", Point(3, 3));
    CHECK_EQ(ninja3.getHealthPoints(), 150);
    CHECK_EQ(ninja3.getSpeed(), 8);

    // All types of ninjas are instance of Ninja class
    Ninja* ninja_ptr1 = new YoungNinja();
    YoungNinja* young_ptr = dynamic_cast<YoungNinja*>(ninja_ptr1);
    CHECK(young_ptr != nullptr);

    Ninja* ninja_ptr2 = new YoungNinja();
    TrainedNinja* trained_ptr = dynamic_cast<TrainedNinja*>(ninja_ptr2);
    CHECK(trained_ptr != nullptr);

    Ninja* ninja_ptr3 = new YoungNinja();
    OldNinja* old_ptr = dynamic_cast<OldNinja*>(ninja_ptr3);
    CHECK(old_ptr != nullptr);
}

TEST_CASE("Ninja move and slash functions") {
    YoungNinja ninja1("Champ", Point(0, 0));
    Cowboy enemy("Enemy", Point(1, 1));
}