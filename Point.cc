#include "Point.hh"
#include <cmath>


// Default constructor:  initializes the point to (0, 0, 0).
Point::Point() {
  x_coord = 0;
  y_coord = 0;
  z_coord = 0;
}

// Initializes the point to (x, y, z) using member initialization.
Point::Point(double x, double y, double z) : x_coord(x), y_coord(y), z_coord(z) {}

// Destructor - Point allocates no dynamic resources.
Point::~Point() {
  // no-op
}

// Mutators:

void Point::setX(double val) {
  x_coord = val;
}

void Point::setY(double val) {
  y_coord = val;
}

void Point::setZ(double val) {
  z_coord = val;
} 

// Accessors:

double Point::getX() const {
  return x_coord;
}

double Point::getY() const {
  return y_coord;
}

double Point::getZ() const {
  return z_coord;
} 

double Point::distanceTo(const Point& target) const {

  double x_target = target.getX();
  double y_target = target.getY();
  double z_target = target.getZ();
 
  double Pythagor = sqrt( 
                          ((x_coord - x_target) * (x_coord - x_target)) + 
	                        ((y_coord - y_target) * (y_coord - y_target)) + 
			                    ((z_coord - z_target) * (z_coord - z_target))
                          );

  return Pythagor;
}

