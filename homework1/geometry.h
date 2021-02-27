#ifndef IS_2020_PROG_2_SEM_GEOMETRY_H
#define IS_2020_PROG_2_SEM_GEOMETRY_H

#include <vector>
#include <cmath>

using namespace std;

class Point {
private:
    int x;
    int y;
public:
    Point() {
        this->x = 0;
        this->y = 0;
    }

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Point(const Point &point) {
        this->x = point.x;
        this->y = point.y;
    }

    int getX() const {
        return this->x;
    }

    int getY() const {
        return this->y;
    }

    Point &operator=(const Point &p) = default;
};

class PolygonalChain : public Point {
private:
    vector<Point> points;
    int n;
public:
    PolygonalChain() {
        this->n = 0;
        points.resize(0);
    }

    PolygonalChain(int n, Point points[]) {
        this->n = n;
        for (int i = 0; i < n; i++) {
            this->points.push_back(points[i]);
        }
    }

    PolygonalChain(const PolygonalChain &pc) = default;

    int getN() const {
        return this->n;
    }

    Point getPoint(int k) const {
        return this->points.at(k);
    }

    static double range(const Point &p1, const Point &p2) {
        double distance = sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
        return distance;
    }

    virtual double perimeter() const {
        double p = 0;
        for (int i = 0; i < this->n - 1; i++) {
            p += range(this->getPoint(i), this->getPoint(i + 1));
        }
        return p;
    }

    PolygonalChain &operator=(const PolygonalChain &pc) = default;
};

class ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain() : PolygonalChain() {};

    ClosedPolygonalChain(int n, Point points[]) : PolygonalChain(n, points) {};

    ClosedPolygonalChain(const ClosedPolygonalChain &cpc) = default;

    double perimeter() const override {
        double p = 0;
        for (int i = 0; i < this->getN() - 1; i++) {
            p += range(this->getPoint(i), this->getPoint(i + 1));
        }
        p += range(this->getPoint(0), this->getPoint(this->getN() - 1));
        return p;
    }

    ClosedPolygonalChain &operator=(const ClosedPolygonalChain &cpc) = default;
};

class Polygon : public ClosedPolygonalChain {
public:
    Polygon() : ClosedPolygonalChain() {};

    Polygon(int n, Point points[]) : ClosedPolygonalChain(n, points) {};

    Polygon(const Polygon &p) = default;

    virtual double area() const {
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

    Polygon &operator=(const Polygon &p) = default;
};

class Triangle : public Polygon {
public:
    Triangle() : Polygon() {};

    Triangle(int n, Point points[]) : Polygon(n, points) {};

    Triangle(const Triangle &tr) = default;

    bool hasRightAngle() const {
        double a = range(getPoint(0), getPoint(1));
        double b = range(getPoint(1), getPoint(2));
        double c = range(getPoint(0), getPoint(2));

        bool answer = ((pow(a, 2) + pow(b, 2) == pow(c, 2)) ||
                       (pow(a, 2) + pow(c, 2) == pow(b, 2) ||
                        (pow(c, 2) + pow(b, 2) == pow(a, 2))));

        return answer;
    }

    Triangle &operator=(const Triangle &tr) = default;
};

class Trapezoid : public Polygon {
public:
    Trapezoid() : Polygon() {};

    Trapezoid(int n, Point points[]) : Polygon(n, points) {};

    Trapezoid(const Trapezoid &tr) = default;

    double height() const {
        double h;
        h = (2 * area()) / (range(getPoint(1), getPoint(2)) + range(getPoint(3), getPoint(0)));
        return h;
    }

    Trapezoid &operator=(const Trapezoid &trp) = default;
};

class RegularPolygon : public Polygon {
public:
    RegularPolygon() : Polygon() {};

    RegularPolygon(int n, Point points[]) : Polygon(n, points) {};

    RegularPolygon(const RegularPolygon &rp) = default;

    RegularPolygon &operator=(const RegularPolygon &rp) = default;
};

#endif