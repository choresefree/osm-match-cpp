/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/2 21:05
* @Description: TODO
*/

#include "geometry/transform.h"

int main() {
    Point point1(100, 250);
    Point point2(150, 250);
    Point point3(200, 300);
    Point point4(175, 500);
    Point point5(175, 250);
    Point target(145, 278);
    Points ps = Points{point1, point2, point3, point4, point5};
    Line line = Line(ps);
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            for (int k = j + 1; k < 5; k++) {
                auto segment = Segment(ps[j], ps[k]);
                printf("point: (%.0f, %.0f), segment: [(%.0f, %.0f), (%.0f, %.0f)]", ps[i].x, ps[i].y, ps[j].x, ps[j].y,
                       ps[k].x, ps[k].y);
                auto ans = pedal(ps[i], segment);
                printf(" pedal: (%.0f, %.0f)\n", ans.x, ans.y);
            }
        }
    }
    printf("angle: %f\n", angle({{0, 1}, {1, 0}}, {{0, 0}, {1, 0}}));
    printf("angle: %f\n", angle({{0, 1}, {1, 0}}, {{1, 2}, {3, 1}}));
    printf("angle: %f\n", angle({{0, -1}, {-1, 0}}, {{1, 2}, {3, 1}}));
    printf("intersect: %d\n", intersect({{0, 1}, {1, 0}}, {{0, 0}, {1, 0}}));
    printf("intersect: %d\n", intersect({{0, 1}, {1, 0}}, {{0, 0}, {1, 1}}));
    printf("intersect: %d\n", intersect({{0, 1}, {1, 0}}, {{2, 3}, {5, 6}}));

//    // 2、transform
//    Coordinate c1 = Coordinate(121.18356323242188, 30.937633514404297);
//    Coordinate c2 = Coordinate(121.17948150634766, 30.938278198242188);
//    Coordinate c3 = Coordinate(121.17994689941406, 30.93960952758789);
//
//    Coordinate c_target = Coordinate(121.182, 30.938);
//    Coordinates cs = {c1, c2, c3};
//    Points rcs = batch_coordinate2relative(cs);
//    printf("geography-->geometry\n");
//    for (auto c: rcs) {
//        printf("(%f, %f) ", c.x, c.y);
//    }
//    Point target = coordinate2relative(c_target);
//    printf("point to line: %f\n", distance(target, rcs));
//    auto len = cal_length(rcs);
//    printf("\n%f", len);
//    Coordinates cs2 = batch_relative2coordinate(rcs);
//    printf("\ngeometry-->geography\n");
//    for (auto c: cs2) {
//        printf("(%f, %f) ", c.lon, c.lat);
//    }
//    printf("wgs84-->gcj02\n");
//    for (auto c: batch_wgs2gcj(cs)) {
//        printf("(%f, %f) ", c.lon, c.lat);
//    }
//    printf("\ngcj02-->wgs84\n");
//    for (auto c: batch_gcj2wgs(cs)) {
//        printf("(%f, %f) ", c.lon, c.lat);
//    }
    return 0;
}