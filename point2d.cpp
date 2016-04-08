#include "point2d.h"

//
// Display 2D point
//
ostream &operator<<(ostream &os, Point2D const &pt) {
    return os << "(" << pt.x() << "," << pt.y() << ")";
}
ostream &operator<<(ostream &os, Point2D* const &p) {
    return os << *p;
}

bool Point2D::operator==(const Point2D &pt) const{
    return _x == pt.x() && _y == pt.y();
}

bool Point2D::operator<(const Point2D &pt) const {
    	return _x < pt._x || (_x == pt._x &&_y < pt._y);
    }
