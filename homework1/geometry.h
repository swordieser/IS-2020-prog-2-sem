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
        double a = perimeter() / 2;
        for (int i = 0; i < getN() - 1; i++) {
            a *= perimeter() / 2 - range(getPoint(i), getPoint(i + 1));
        }
        a *= perimeter() / 2 - range(getPoint(0), getPoint(getN() - 1));
        return sqrt(a);
    }

    Polygon &operator=(const Polygon &p) = default;
};

#endif