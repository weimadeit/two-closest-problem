//
// Created by Chang WEI on 2020/8/28.
//

#ifndef CLOSEST_TWO_POINTS_POINT_CLASS_H
#define CLOSEST_TWO_POINTS_POINT_CLASS_H
#include <cmath>
#include <iostream>
#include <random>
class Point {
public:
    double x;
    double y;
    Point(double n1, double n2, int l) : x(n1), y(n2){}
    Point() {
        std::random_device rd;
        std::default_random_engine rng(rd());
        std::uniform_real_distribution<> dist(0, 10);
        x = dist(rng);
        y = dist(rng);
    }
    friend std::ostream& operator<<(std::ostream& os, const Point& p)
    {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};
double Dist(const Point &p1, const Point &p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
bool LesserX(const Point &p1, const Point &p2)
{return p1.x < p2.x;}
bool LesserY(const Point &p1, const Point &p2)
{return p1.y < p2.y;}
#endif //CLOSEST_TWO_POINTS_POINT_CLASS_H
