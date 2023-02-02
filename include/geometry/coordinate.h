/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/1/31 10:54
* @Description: TODO
*/
#ifndef CUPID_COORDINATE_H
#define CUPID_COORDINATE_H

#include <vector>

class Coordinate {
public:
    Coordinate();

    Coordinate(double lon, double lat);

    double lon{};
    double lat{};

};

typedef std::vector<Coordinate> Coordinates;

Coordinate coordinate2relative(Coordinate coord);

Coordinates coordinates2relative(const Coordinates &coords);

double distance(Coordinate coord1, Coordinate coord2);

double cal_length(const std::vector<Coordinate> &coords);

#endif //CUPID_COORDINATE_H