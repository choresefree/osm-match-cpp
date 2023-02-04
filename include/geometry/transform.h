/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/1/31 10:54
* @Description: TODO
*/

#ifndef CUPID_TRANSFORM_H
#define CUPID_TRANSFORM_H

#include "osm/node.h"

bool out_of_china(double lon, double lat);

double translate_lon(double lon, double lat);

double translate_lat(double lon, double lat);

Coordinate wgs2gcj(Coordinate wgs_coord);

Coordinate gcj2wgs(Coordinate gcj_coord);

Coordinates batch_wgs2gcj(const Coordinates &wgs_coords);

Coordinates batch_gcj2wgs(const Coordinates &gcj_coords);

Coordinates batch_wgs2gcj(const osm::NodeList &wgs_nodes);

Coordinates batch_gcj2wgs(const osm::NodeList &gcj_nodes);

#endif //CUPID_TRANSFORM_H
