/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/5 22:18
* @Description: TODO
*/

#include "geometry/geometry.h"


int main() {
    Points ps = {
            {0.15,   -3.65},
            {2.475,  -3.275},
            {1.15,   -3.175},
            {1.0,    -2.175},
            {2.325,  -1.775},
            {4.725,  -1.725},
            {6.225,  -1.175},
            {6.95,   -0.05},
            {6.625,  1.775},
            {4.775,  4.15},
            {3.4,    4.275},
            {2.425,  3.175},
            {2.575,  1.925},
            {1.825,  0.0},
            {1.05,   -0.15},
            {-2.225, 1.175},
            {-3.4,   0.3},
            {-3.95,  -1.25},
            {-3.35,  -2.5},
            {-1.05,  -3.625}};
    Line line = Line(ps);
    Points poly = polygon(line, 4);
    printf("convex hull\n");
    for (auto p: poly) {
        printf("[%.3f, %.3f],  ", p.x, p.y);
    }
    if (in_polygon(poly, {-3.95, -1.25})) {
        printf("\nin polygon");
    } else {
        printf("\nnot in polygon");
    }
    return 0;
}