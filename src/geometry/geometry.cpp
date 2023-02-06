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
    this->length = cal_length(this->points);
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

Point pedal(const Point &point, const Segment &segment) {
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


double distance(const Point &point1, const Point &point2) {
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

double distance(const Point &point, const Segment &segment) {
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

double distance(const Point &point, const Line &line) {
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

double angle(const Segment &seg1, const Segment &seg2) {
    auto x1 = seg1.point2.x - seg1.point1.x;
    auto y1 = seg1.point2.y - seg1.point1.y;
    auto x2 = seg2.point2.x - seg2.point1.x;
    auto y2 = seg2.point2.y - seg2.point1.y;
    auto dot = x1 * x2 + y1 * y2;
    auto det = x1 * y2 - y1 * x2;
    auto cal_angle = atan2(det, dot);
    return abs(cal_angle);
}

bool intersect(const Segment &seg1, const Segment &seg2) {
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

bool vertical(const Segment &seg1, const Segment &seg2) {
    auto x1 = seg1.point2.x - seg1.point1.x;
    auto y1 = seg1.point2.y - seg1.point1.y;
    auto x2 = seg2.point2.x - seg2.point1.x;
    auto y2 = seg2.point2.y - seg2.point1.y;
    return (x1 * x2 + y1 * y2) == 0;
}

bool parallel(const Segment &seg1, const Segment &seg2) {
    auto x1 = seg1.point2.x - seg1.point1.x;
    auto y1 = seg1.point2.y - seg1.point1.y;
    auto x2 = seg2.point2.x - seg2.point1.x;
    auto y2 = seg2.point2.y - seg2.point1.y;
    return (x1 * y2) == (x2 * y1);
}

bool cmp(Point a, Point b) {
    return (a.x < b.x || (a.x == b.x && a.y < b.y));
}

double mul(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

Points convex_hull(const Points &ps) {
    // Andrew
    Point CHP[ps.size()];
    Points order_ps = ps;
    sort(order_ps.begin(), order_ps.end(), cmp);
    int tot = 0;
    for (auto &p: order_ps) {
        while (tot > 1 && mul(CHP[tot - 2], CHP[tot - 1], p) < 0)
            --tot;
        CHP[tot++] = p;
    }
    int k = tot;
    for (auto p = order_ps.end() - 2; p >= order_ps.begin(); --p) {
        while (tot > k && mul(CHP[tot - 2], CHP[tot - 1], *p) < 0)
            --tot;
        CHP[tot++] = *p;
    }
    if (order_ps.size() > 1)
        --tot;
    Points res;
    for (int i = 0; i < tot; ++i) {
        res.push_back(CHP[i]);
    }
    return res;
}

Segment midline(const Segment &segment, double extend_length){
    auto x1 = segment.point1.x, y1 = segment.point1.y;
    auto x2 = segment.point2.x, y2 = segment.point2.y;
    auto mid_x = (x1+x2)/ 2, mid_y = (y1+y2)/ 2;
    auto t = sqrt(pow(extend_length / 2, 2) / (pow(x2-x1, 2) + pow(y2-y1, 2)));
    auto x3 = mid_x - t*(y2 - y1);
    auto y3 = mid_y + t*(x2 - x1);
    auto x4 = mid_x + t*(y2 - y1);
    auto y4 = mid_y - t*(x2 - x1);
    Point point3 = Point(x3, y3);
    Point point4 = Point(x4, y4);
    Segment res = Segment(point3, point4);
    return res;
}


Points polygon(const Line &line, double extend_length, POLYGON_TYPE type) {
    Points more_ps;
    more_ps.push_back(line.points[0]);
    for (int i=1; i<line.points.size(); i++){
        auto mid = midline({line.points[i], line.points[i-1]}, extend_length);
        more_ps.push_back(line.points[i]);
        more_ps.push_back(mid.point1);
        more_ps.push_back(mid.point2);
    }
    if (type == CONVEX) {
        return convex_hull(more_ps);
    }
    if (type == CONCAVE) {
    }
    return more_ps;
}

bool in_polygon(const Points &polygon, const Point &point) {
    int n_cross = 0;
    for (int i = 0; i < polygon.size(); i++) {
        Point p1 = polygon[i];
        Point p2 = polygon[(i + 1) % polygon.size()];
        if (p1.y == p2.y)
            continue;
        if (point.y < std::min(p1.y, p2.y))
            continue;
        if (point.y >= std::max(p1.y, p2.y))
            continue;
        double x = (double) (point.y - p1.y) * (double) (p2.x - p1.x) / (double) (p2.y - p1.y) + p1.x;
        if (x > point.x) {
            n_cross++;
        }
    }
    if (n_cross % 2 == 1) {
        return true;
    }
    return false;
}

int num_in_in_polygon(const Points &polygon, const Line &line) {
    int n_in = 0;
    for (auto const p: line.points) {
        if (in_polygon(polygon, p)) {
            n_in += 1;
        }
    }
    return n_in;
}


bool in_polygon(const Points &polygon, const Line &line) {
    int n_in = num_in_in_polygon(polygon, line);
    if (n_in == polygon.size()) {
        return true;
    }
    return false;
}

bool out_polygon(const Points &polygon, const Line &line) {
    int n_in = num_in_in_polygon(polygon, line);
    if (n_in == 0) {
        return true;
    }
    return false;
}

bool intersect(const Points &polygon, const Line &line) {
    int n_in = num_in_in_polygon(polygon, line);
    if (n_in > 0 && n_in < polygon.size()) {
        return true;
    }
    return true;
}

