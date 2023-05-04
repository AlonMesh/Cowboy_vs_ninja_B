#include "doctest.h"
#include <stdexcept>
#include "sources/Team.hpp"
using namespace ariel;
using namespace std;
#include <cmath>

TEST_CASE("Point initiallze") {
    Point zeroPoint = Point();
    CHECK_EQ(zeroPoint.get_x(), 0.0);
    CHECK_EQ(zeroPoint.get_y(), 0.0);

    Point p(1.0, 2.0);
    CHECK_EQ(p.get_x(), 1.0);
    CHECK_EQ(p.get_y(), 2.0);
}

TEST_CASE("Distance of points") {
    Point a(1.0, 2.0);
    Point b(4.0, 6.0);

    // Check that the distance is simatric
    CHECK_EQ(a.distance(b), b.distance(a));

    // Check
    CHECK_EQ(a.distance(b), 5.0);

    b = Point(3.0, 5.0); // reset

    // 2^2 + 3^2 = 4 + 9 = 13
    CHECK_EQ(a.distance(b), sqrt(13.0));

    // another test of pure double value. like a.distance(b) = 32.520992401...
}

TEST_CASE("moveTowards function") {
    Point a = Point();
    Point b(3.0, 0);

    //....
}

TEST_CASE("Character initiallze") {
    Character champ("Champ", Point(0.0, 0.0), 100);

    CHECK_EQ(champ.getName(), "Champ");
    CHECK_EQ(champ.getLocation(), Point(0.0, 0.0));

    // more!
}

TEST_CASE("Functions of Character") {
    Character champ("Champ", Point(0.0, 0.0), 100);
    
    CHECK_EQ(champ.isAlive(), true);
    champ.hit(20);
    // a test with getHP?
    CHECK_EQ(champ.isAlive(), true);
    champ.hit(100);
    CHECK_EQ(champ.isAlive(), false);

    // throw error if hitting a dead Character?

}
