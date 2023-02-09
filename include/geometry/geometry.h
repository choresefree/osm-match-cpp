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
#include <string>
#include "common/object.h"

class Point :public Object{
public:
    Point();

    Point(double x, double y);

    Point(const std::string& id, double x, double y);

    Point(const std::string& id, double x, double y, const Tags &tags);

    double x;
    double y;
};

typedef std::vector<Point> Points;

typedef std::pair<Point, Point> BBox; // <left bottom, right top>

class Segment :public Object{
public:
    Segment();

    Segment(Point point1, Point point2);

    Segment(const std::string& id, Point point1, Point point2);

    Segment(const std::string& id, Point point1, Point point2, Tags tags);

    Point point1;
    Point point2;
};

typedef std::vector<Segment> Segments;


class Line :public Object{
public:
    Line();

    Line(std::vector<Point> points);

    Line(const std::string &id, std::vector<Point> points, const Tags& tags);

    Points points;
    double length{};
};

typedef std::vector<Line> Lines;

class Coordinate :public Object{
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

bool overlap(const BBox &bbox1, const BBox &bbox2);

bool intersect(const Segment &seg1, const Segment &seg2);

bool intersect(const Points &polygon, const Line &line);

bool vertical(const Segment &seg1, const Segment &seg2);

bool parallel(const Segment &seg1, const Segment &seg2);

Points thick(const Points &points, double min_interval=20);

enum POLYGON_TYPE {
    CONVEX, CONCAVE
};

Segment midline(const Segment &segment, double extend_length = 50);

BBox bbox(const Points &points, double extend_length = 0);

Points polygon(const Line &line, double extend_length = 50, POLYGON_TYPE type = CONVEX);

Points convex_hull(const Points &ps);

bool in_polygon(const Points &polygon, const Point &point);

bool in_polygon(const Points &polygon, const Line &line);

bool out_polygon(const Points &polygon, const Line &line);

#endif //CUPID_GEOMETRY_H
