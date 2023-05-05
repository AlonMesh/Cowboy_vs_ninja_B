#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>

namespace ariel {
    class Point {
        private:
            double x_value;
            double y_value;

        public:
            Point(double x_value, double y_value) : x_value(x_value), y_value(y_value) {} ;
            Point() : x_value(0.0), y_value(0.0) {};

            double distance(Point other);

            void print();

            static Point moveTowards(Point currentPoint, Point targetPoint, int distance);

            // mine
            bool isOnLine(Point point1, Point point2);

            double get_x();

            double get_y();
    };
}
#endif