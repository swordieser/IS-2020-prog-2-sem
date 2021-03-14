#include "geometry.h"

//Point
Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

Point::Point(const Point &point) {
    this->x = point.x;
    this->y = point.y;
}

int Point::getX() const {
    return this->x;
}

int Point::getY() const {
    return this->y;
}

Point::~Point() = default;

Point &Point::operator=(const Point &p) = default;


//PolygonalChain
PolygonalChain::PolygonalChain() {
    this->n = 0;
}

PolygonalChain::PolygonalChain(int n, Point points[]) {
    this->n = n;
    for (int i = 0; i < n; i++) {
        this->points.push_back(points[i]);
    }
}

PolygonalChain::PolygonalChain(const PolygonalChain &pc) = default;

int PolygonalChain::getN() const {
    return this->n;
}

Point PolygonalChain::getPoint(int k) const {
    return this->points.at(k);
}

double PolygonalChain::range(const Point &p1, const Point &p2) {
    double distance = sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
    return distance;
}

double PolygonalChain::perimeter() const {
    double p = 0;
    for (int i = 0; i < this->n - 1; i++) {
        p += range(this->getPoint(i), this->getPoint(i + 1));
    }
    return p;
}

PolygonalChain &PolygonalChain::operator=(const PolygonalChain &pc) = default;


//ClosedPolygonalChain
ClosedPolygonalChain::ClosedPolygonalChain() : PolygonalChain() {};

ClosedPolygonalChain::ClosedPolygonalChain(int n, Point points[]) : PolygonalChain(n, points) {};

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain &cpc) = default;

double ClosedPolygonalChain::perimeter() const {
    double p = PolygonalChain::perimeter();
    p += range(this->getPoint(0), this->getPoint(this->getN() - 1));
    return p;
}

ClosedPolygonalChain &ClosedPolygonalChain::operator=(const ClosedPolygonalChain &cpc) = default;


//Polygon
Polygon::Polygon() : ClosedPolygonalChain() {};

Polygon::Polygon(int n, Point points[]) : ClosedPolygonalChain(n, points) {};

Polygon::Polygon(const Polygon &p) = default;

double Polygon::area() const {
    double a;
    double s_first = 0;
    for (int i = 0; i < getN() - 1; i++) {
        s_first += this->getPoint(i).getX() * this->getPoint(i + 1).getY();
    }
    s_first += this->getPoint(getN() - 1).getX() * this->getPoint(0).getY();

    double s_second = 0;
    for (int i = 0; i < getN() - 1; i++) {
        s_second += this->getPoint(i).getY() * this->getPoint(i + 1).getX();
    }
    s_second += this->getPoint(getN() - 1).getY() * this->getPoint(0).getX();

    a = abs(s_first - s_second) / 2;

    return a;
}

Polygon &Polygon::operator=(const Polygon &p) = default;


//Triangle
Triangle::Triangle() : Polygon() {};

Triangle::Triangle(int n, Point points[]) : Polygon(n, points) {};

Triangle::Triangle(const Triangle &tr) = default;

bool Triangle::hasRightAngle() const {
    double a = pow(getPoint(0).getX() - getPoint(1).getX(), 2) + pow(getPoint(0).getY() - getPoint(1).getY(), 2);
    double b = pow(getPoint(1).getX() - getPoint(2).getX(), 2) + pow(getPoint(1).getY() - getPoint(2).getY(), 2);
    double c = pow(getPoint(2).getX() - getPoint(0).getX(), 2) + pow(getPoint(2).getY() - getPoint(0).getY(), 2);

    bool answer = ((a + b == c) || (a + c == b) || (b + c == a));

    return answer;
}

Triangle &Triangle::operator=(const Triangle &tr) = default;


//Trapezoid
Trapezoid::Trapezoid() : Polygon() {};

Trapezoid::Trapezoid(int n, Point points[]) : Polygon(n, points) {};

Trapezoid::Trapezoid(const Trapezoid &tr) = default;

double Trapezoid::height() const {
    double h;
    h = (2 * area()) / (range(getPoint(1), getPoint(2)) + range(getPoint(3), getPoint(0)));
    return h;
}

Trapezoid &Trapezoid::operator=(const Trapezoid &trp) = default;


//RegularPolygon
RegularPolygon::RegularPolygon() : Polygon() {};

RegularPolygon::RegularPolygon(int n, Point points[]) : Polygon(n, points) {};

RegularPolygon::RegularPolygon(const RegularPolygon &rp) = default;

RegularPolygon &RegularPolygon::operator=(const RegularPolygon &rp) = default;

double RegularPolygon::perimeter() const {
    double a = range(getPoint(0), getPoint(1));
    return a * getN();
}

double RegularPolygon::area() const {
    double a = range(getPoint(0), getPoint(1));
    return ((getN() * pow(a, 2)) / (4 * tan(M_PI / getN())));
}