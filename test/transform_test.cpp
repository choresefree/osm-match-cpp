/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/2 21:05
* @Description: TODO
*/

#include "geometry/transform.h"

int main() {
    Coordinate c1 = Coordinate(121.18356323242188, 30.937633514404297);
    Coordinate c2 = Coordinate(121.17948150634766, 30.938278198242188);
    Coordinate c3 = Coordinate(121.17994689941406, 30.93960952758789);
    Coordinates cs = {c1, c2, c3};
    printf("wgs84-->gcj02\n");
    for (auto c: batch_wgs2gcj(cs)) {
        printf("(%f, %f) ", c.lon, c.lat);
    }
    printf("\ngcj02-->wgs84\n");
    for (auto c: batch_gcj2wgs(cs)) {
        printf("(%f, %f) ", c.lon, c.lat);
    }
    return 0;
}