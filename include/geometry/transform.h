/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/1/31 10:54
* @Description: TODO
*/

#ifndef CUPID_TRANSFORM_H
#define CUPID_TRANSFORM_H

#include "geometry.h"

bool in_china(double lon, double lat);

double translate_lon(double lon, double lat);

double translate_lat(double lon, double lat);

Coordinate wgs2gcj(Coordinate wgs_coord);

Coordinate gcj2wgs(Coordinate gcj_coord);

Coordinates batch_wgs2gcj(const Coordinates &wgs_coords);

Coordinates batch_gcj2wgs(const Coordinates &gcj_coords);

Point coordinate2relative(Coordinate coord);

Points coordinates2relative(const Coordinates &coords);

#endif //CUPID_TRANSFORM_H
