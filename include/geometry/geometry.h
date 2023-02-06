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
    double length;
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

Point pedal(const Point &point, const Segment &segment);

double distance(const Point &point1, const Point &point2);

double distance(const Point &point, const Segment &segment);

double distance(const Point &point, const Line &line);

double angle(const Segment &seg1, const Segment &seg2);

bool intersect(const Segment &seg1, const Segment &seg2);

bool intersect(const Points &polygon, const Line &line);

bool vertical(const Segment &seg1, const Segment &seg2);

bool parallel(const Segment &seg1, const Segment &seg2);

enum POLYGON_TYPE {
    CONVEX, CONCAVE
};

Segment midline(const Segment &segment, double extend_length = 500);

Points polygon(const Line &line, double extend_length = 500, POLYGON_TYPE type = CONVEX);

Points convex_hull(const Points &ps);

bool in_polygon(const Points &polygon, const Point &point);

bool in_polygon(const Points &polygon, const Line &line);

bool out_polygon(const Points &polygon, const Line &line);

#endif //CUPID_GEOMETRY_H
