/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/1 00:29
* @Description: TODO
*/

#include <cmath>
#include "geometry/coordinate.h"

const double REF_TO_DEGREE = 57.29577951308232;
const double DEGREE_TO_RAD = 0.017453292519943295;
const double BASE_LON = 120;
const double BASE_LAT = 30;
const double M = 6352352.378748541;
const double N = 6383807.635861196;
const double R = 5471991.159432675;


Coordinate::Coordinate(double lon, double lat) {
    this->lon = lon;
    this->lat = lat;
}

Coordinate::Coordinate() = default;


Coordinate coordinate2relative(const Coordinate coord) {
    double lon = (coord.lon - BASE_LON) * DEGREE_TO_RAD;
    double lat = (coord.lat - BASE_LAT) * DEGREE_TO_RAD;
    Coordinate res = {lon * R, lat * M};
    return res;
}

Coordinates coordinates2relative(const Coordinates &coords) {
    Coordinates res;
    for (auto coord: coords) {
        auto relative_coord = coordinate2relative(coord);
        res.push_back(relative_coord);
    }
    return res;
}

double distance(Coordinate coord1, Coordinate coord2) {
    return sqrt(pow(coord1.lon - coord2.lon, 2) + pow(coord1.lat - coord2.lat, 2));
}

double cal_length(const Coordinates &coords) {
    if (coords.size() <= 1) {
        return 0;
    }
    double len = 0;
    for (int i = 1; i < coords.size(); i++) {
        len += distance(coords[i], coords[i - 1]);
    }
    return len;
}