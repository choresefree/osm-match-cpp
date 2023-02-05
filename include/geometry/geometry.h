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
    Point(double x, double y);

    double distance(Point point);

    double x;
    double y;
};

typedef std::vector<Point> Points;

class Line {
public:
    explicit Line(std::vector<Point> points);

    std::vector<Point> points;
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

double distance(Point point1, Point point2);

double distance(Point point, Line line);

double distance(Line line1, Line line2);

bool is_intersect(Line line1, Line line2);

bool is_vertical(Line line1, Line line2);

bool is_parallel(Line line1, Line line2);

Points cal_polygon(Line line);


#endif //CUPID_GEOMETRY_H
