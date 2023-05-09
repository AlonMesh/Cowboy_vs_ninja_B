#include "Point.hpp"
#include <cmath> // for sqrt()

namespace ariel {

    Point::Point(double x_value, double y_value) : x_value(x_value), y_value(y_value) {
        if (x_value < 0 || y_value < 0) {
            throw std::invalid_argument("Point value's must be non-negative");
        }
    }

    Point::Point() : x_value(0), y_value(0) {};
    
    double Point::distance(Point other) {
        return sqrt(pow((this->get_x()-other.get_x()), 2) + pow((this->get_y()-other.get_y()), 2));
    }
    
    void Point::print() {
        std::cout << "(" << this->get_x() << ", " << this->get_y() << ")" << std::endl;
    }
    
    Point Point::moveTowards(Point currentPoint, Point targetPoint, int distance) {
        // First check for invalid argument
        if (distance < 0) {
            throw std::invalid_argument("Distance must be non-negative number"); 
        }

        // Calculate the distance between the current point and the target point
        double dist = currentPoint.distance(targetPoint);

        // If the distance is less than the desired distance, just return the target point
        if (dist <= distance) {
            return targetPoint;
        }

        // Calculate the displacement vector between the current and target points
        double dx = targetPoint.get_x() - currentPoint.get_x();
        double dy = targetPoint.get_y() - currentPoint.get_y();

        // Calculate the unit vector of the displacement vector
        double unitDx = dx / dist;
        double unitDy = dy / dist;

        // Calculate the new x and y coordinates that are distance away from the current point
        double newX = currentPoint.get_x() + (unitDx * distance);
        double newY = currentPoint.get_y() + (unitDy * distance);

        // Create and return the new point
        return Point(newX, newY);
    }
    
    bool Point::isOnLine(Point point1, Point point2) {
        // Check if the point is on the line defined by point1 and point2
        // using the equation of a line: y - y1 = (y2 - y1)/(x2 - x1) * (x - x1)
        // Rearrange the equation to: (y - y1) * (x2 - x1) - (x - x1) * (y2 - y1) = 0
        int x1 = point1.get_x();
        int y1 = point1.get_y();
        int x2 = point2.get_x();
        int y2 = point2.get_y();
        int x = this->get_x();
        int y = this->get_y();
        return (y - y1) * (x2 - x1) - (x - x1) * (y2 - y1) == 0;
    }
    
    double Point::get_x() {
        return this->x_value;
    }
    
    double Point::get_y() {
        return this->y_value;
    }
}
