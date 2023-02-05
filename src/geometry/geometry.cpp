/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/5 01:14
* @Description: TODO
*/

#include <vector>
#include <cmath>
#include "geometry/geometry.h"


Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

double Point::distance(Point point) {
    return 0;
}

Line::Line(std::vector<Point> points) {
    this->points = std::move(points);
}

Coordinate::Coordinate() = default;

Coordinate::Coordinate(double lon, double lat) {
    this->lon = lon;
    this->lat = lat;
}

double cal_length(const Points &points) {
    if (points.size() <= 1) {
        return 0;
    }
    double len = 0;
    for (int i = 1; i < points.size(); i++) {
        len += distance(points[i], points[i - 1]);
    }
    return len;
}

double distance(Point point1, Point point2) {
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

double distance(Point point, Line line);

double distance(Line line1, Line line2);

bool is_intersect(Line line1, Line line2);

bool is_vertical(Line line1, Line line2);

bool is_parallel(Line line1, Line line2);

Points cal_polygon(Line line);
