/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/5 01:14
* @Description: geometry definition in plane coordinate system
*/

#ifndef CUPID_GEOMETRY_H
#define CUPID_GEOMETRY_H

#include <vector>

class Point {
public:
    Point();

    Point(double x, double y);

    double x{};
    double y{};
};

typedef std::vector<Point> Points;

class Segment {
public:
    Segment();

    Segment(Point point1, Point point2);

    Point point1;
    Point point2;
};


class Line {
public:
    Line();

    Line(std::vector<Point> points);

    Points points;
};

class Coordinate {
public:
    Coordinate();

    Coordinate(double lon, double lat);

    double lon{};
    double lat{};

};

typedef std::vector<Coordinate> Coordinates;

double cal_length(const Points &points);

Point pedal(Point point, Segment segment);

double distance(Point point1, Point point2);

double distance(Point point, Segment segment);

double distance(Point point, Line line);

double angle(Segment seg1, Segment seg2);

bool intersect(Segment seg1, Segment seg2);

bool vertical(Segment seg1, Segment seg2);

bool parallel(Segment seg1, Segment seg2);

enum POLYGON_TYPE {
    CONVEX, CONCAVE
};

Points polygon(const Line& line, POLYGON_TYPE type = CONVEX);

Points convex_hull(Points ps);

#endif //CUPID_GEOMETRY_H
