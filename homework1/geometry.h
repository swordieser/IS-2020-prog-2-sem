#ifndef IS_2020_PROG_2_SEM_GEOMETRY_H
#define IS_2020_PROG_2_SEM_GEOMETRY_H

#include <vector>
#include <cmath>

using namespace std;

//fixed cpp
class Point {
private:
    int x;
    int y;
public:
    Point();

    Point(int x, int y);

    Point(const Point &point);

    int getX() const;

    int getY() const;

    virtual ~Point();

    Point &operator=(const Point &p);
};

class PolygonalChain : public Point {
private:
    vector<Point> points;
    int n;
public:
    PolygonalChain();

    PolygonalChain(int n, Point points[]);

    PolygonalChain(const PolygonalChain &pc);

    int getN() const;

    Point getPoint(int k) const;

    static double range(const Point &p1, const Point &p2);

    virtual double perimeter() const;

    PolygonalChain &operator=(const PolygonalChain &pc);
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain();

    ClosedPolygonalChain(int n, Point points[]);

    ClosedPolygonalChain(const ClosedPolygonalChain &cpc);
    //fixed copy-paster perimeter
    double perimeter() const override;

    ClosedPolygonalChain &operator=(const ClosedPolygonalChain &cpc);
};

class Polygon : public ClosedPolygonalChain {
public:
    Polygon();

    Polygon(int n, Point points[]);

    Polygon(const Polygon &p);

    virtual double area() const;

    Polygon &operator=(const Polygon &p);
};

class Triangle : public Polygon {
public:
    Triangle();

    Triangle(int n, Point points[]);

    Triangle(const Triangle &tr);

    //fixed without sqrt
    bool hasRightAngle() const;

    Triangle &operator=(const Triangle &tr);
};

class Trapezoid : public Polygon {
public:
    Trapezoid();

    Trapezoid(int n, Point points[]);

    Trapezoid(const Trapezoid &tr);

    double height() const ;

    Trapezoid &operator=(const Trapezoid &trp);
};

//fixed regular polygon area and perimeter
class RegularPolygon : public Polygon {
public:
    RegularPolygon();

    RegularPolygon(int n, Point points[]);

    RegularPolygon(const RegularPolygon &rp);

    RegularPolygon &operator=(const RegularPolygon &rp);

    double perimeter() const override;

    double area() const override;
};

#endif