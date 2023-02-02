/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/1 00:29
* @Description: TODO
*/
#include <vector>
#include <cmath>
#include "common.h"

const double REF_TO_DEGREE = 57.29577951308232;
const double DEGREE_TO_RAD = 0.017453292519943295;
const double BASE_LON = 120;
const double BASE_LAT = 30;
const double M = 6352352.378748541;
const double N = 6383807.635861196;
const double R = 5471991.159432675;

coordinate coordinate2relative(const coordinate coord) {
    double lon = (coord.first - BASE_LON) * DEGREE_TO_RAD;
    double lat = (coord.second - BASE_LAT) * DEGREE_TO_RAD;
    coordinate res = {lon * R, lat * M};
    return res;
}

coordinates coordinates2relative(const coordinates &coords) {
    coordinates res;
    for (auto coord: coords) {
        auto relative_coord = coordinate2relative(coord);
        res.push_back(relative_coord);
    }
    return res;
}

double distance(coordinate coord1, coordinate coord2) {
    return sqrt(pow(coord1.first - coord2.first, 2) + pow(coord1.second - coord2.second, 2));
}

double cal_length(const std::vector<coordinate> &coords) {
    if (coords.size() <= 1) {
        return 0;
    }
    double len = 0;
    for (int i = 1; i < coords.size(); i++) {
        len += distance(coords[i], coords[i - 1]);
    }
    return len;
}