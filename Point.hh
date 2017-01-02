#ifndef POINT_H
#define POINT_H

// A 3-dimensional point class!
// Coordinates are double-precision floating point.
class Point {

  double x_coord;
  double y_coord;
  double z_coord;

public:
  // Constructors
  Point();
  Point(double x, double y, double z);

  // Destructor
  ~Point();

  // Mutator methods
  void setX(double);
  void setY(double);
  void setZ(double);

  // Accessor methods
  double getX() const;
  double getY() const;
  double getZ() const;

  //distanceTo method
  double distanceTo(const Point&) const;
};

#endif
