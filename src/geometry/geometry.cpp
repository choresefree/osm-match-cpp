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

Point::Point() = default;

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

Segment::Segment() = default;

Segment::Segment(Point point1, Point point2) {
    this->point1 = point1;
    this->point2 = point2;
}

Line::Line() = default;

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

Point pedal(Point point, Segment segment) {
    Point begin = segment.point1;
    Point end = segment.point2;
    double dx = begin.x - end.x;
    double dy = begin.y - end.y;
    if (abs(dx) < 0.00000001 && abs(dy) < 0.00000001) {
        return begin;
    }
    double u = (point.x - begin.x) * (begin.x - end.x) + (point.y - begin.y) * (begin.y - end.y);
    u = u / ((dx * dx) + (dy * dy));
    Point res = Point(begin.x + u * dx, begin.y + u * dy);
    return res;
}


double distance(Point point1, Point point2) {
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

double distance(Point point, Segment segment) {
    auto min_x = std::min(segment.point1.x, segment.point2.x);
    auto max_x = std::max(segment.point1.x, segment.point2.x);
    auto min_y = std::min(segment.point1.y, segment.point2.y);
    auto max_y = std::max(segment.point1.y, segment.point2.y);
    double d1 = distance(point, segment.point1);
    double d2 = distance(point, segment.point2);
    auto pd = pedal(point, segment);
    if (pd.x > min_x && pd.x < max_x && pd.y > min_y & pd.y < max_y) {
        return distance(point, pd);
    }
    return std::min(d1, d2);
}

double distance(Point point, Line line) {
    double dis = INFINITY;
    if (line.points.size() == 1) {
        return distance(point, line.points[0]);
    }
    for (int i = 1; i < line.points.size(); i++) {
        auto cur_dis = distance(point, {line.points[i], line.points[i - 1]});
        dis = std::min(dis, cur_dis);
//        printf("\npoint: (%.0f, %.0f), segment: [(%.0f, %.0f), (%.0f, %.0f)] distance: %f\n", point.x, point.y, line.points[i].x,
//               line.points[i].y, line.points[i - 1].x, line.points[i - 1].y, cur_dis);
    }
    return dis;
}

double angle(Segment seg1, Segment seg2) {
    auto x1 = seg1.point2.x - seg1.point1.x;
    auto y1 = seg1.point2.y - seg1.point1.y;
    auto x2 = seg2.point2.x - seg2.point1.x;
    auto y2 = seg2.point2.y - seg2.point1.y;
    auto dot = x1 * x2 + y1 * y2;
    auto det = x1 * y2 - y1 * x2;
    auto cal_angle = atan2(det, dot);
    return abs(cal_angle);
}

bool intersect(Segment seg1, Segment seg2) {
    auto x1 = seg1.point1.x, y1 = seg1.point1.y;
    auto x2 = seg1.point2.x, y2 = seg1.point2.y;
    auto x3 = seg2.point1.x, y3 = seg2.point1.y;
    auto x4 = seg2.point2.x, y4 = seg2.point2.y;
    auto a = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    auto b = (x2 - x1) * (y4 - y1) - (y2 - y1) * (x4 - x1);
    auto c = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
    auto d = (x4 - x3) * (y2 - y3) - (y4 - y3) * (x2 - x3);
    if (std::max(x1, x2) < std::min(x3, x4) || std::max(x3, x4) < std::min(x1, x2)
        || std::max(y1, y2) < std::min(y3, y4) || std::max(y3, y4) < std::min(y1, y2)) {
        return false;
    }
    if (a * b <= 0 && c * d <= 0) {
        return true;
    }
    return false;
}

bool vertical(Segment seg1, Segment seg2) {
    auto x1 = seg1.point2.x - seg1.point1.x;
    auto y1 = seg1.point2.y - seg1.point1.y;
    auto x2 = seg2.point2.x - seg2.point1.x;
    auto y2 = seg2.point2.y - seg2.point1.y;
    return (x1 * x2 + y1 * y2) == 0;
}

bool parallel(Segment seg1, Segment seg2) {
    auto x1 = seg1.point2.x - seg1.point1.x;
    auto y1 = seg1.point2.y - seg1.point1.y;
    auto x2 = seg2.point2.x - seg2.point1.x;
    auto y2 = seg2.point2.y - seg2.point1.y;
    return (x1 * y2) == (x2 * y1);
}

Points polygon(const Line &line, POLYGON_TYPE type) {
    if (type == CONVEX) {
        return convex_hull(line.points);
    }
    if (type == CONCAVE) {
    }
    return line.points;
}

bool cmp(Point a, Point b) {
    return (a.x < b.x || (a.x == b.x && a.y < b.y));
}

double mul(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

Points convex_hull(Points ps) {
    // Andrew
    Point CHP[ps.size()];
    sort(ps.begin(), ps.end(), cmp);
    int tot = 0;
    for (auto &p: ps) {
        while (tot > 1 && mul(CHP[tot - 2], CHP[tot - 1], p) < 0)
            --tot;
        CHP[tot++] = p;
    }
    int k = tot;
    for (auto p = ps.end() - 2; p >= ps.begin(); --p) {
        while (tot > k && mul(CHP[tot - 2], CHP[tot - 1], *p) < 0)
            --tot;
        CHP[tot++] = *p;
    }
    if (ps.size() > 1)
        --tot;
    Points res;
    for (int i = 0; i < tot; ++i) {
        res.push_back(CHP[i]);
    }
    return res;
}
