/**
* @Projectname: cuM_PId
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/2 20:18
* @Description: TODO
*/

#include "osm/node.h"

const double A = 6378245.0;
const double E = 0.00669342162296594323;

bool out_of_china(double lon, double lat) {
    return lon < 72.004 || lon > 137.8374 || lat < 0.8293 || lat > 55.8271;
}

double translate_lon(double lon, double lat) {
    double ret = 300.0 + lon + 2.0 * lat + 0.1 * lon * lon + 0.1 * lon * lat + 0.1 * sqrt(abs(lon));
    ret += (20.0 * sin(6.0 * lon * M_PI) + 20.0 * sin(2.0 * lon * M_PI)) * 2.0 / 3.0;
    ret += (20.0 * sin(lon * M_PI) + 40.0 * sin(lon / 3.0 * M_PI)) * 2.0 / 3.0;
    ret += (150 * sin(lon / 12.0 * M_PI) + 300.0 * sin(lon / 30.0 * M_PI)) * 2.0 / 3.0;
    return ret;
}

double translate_lat(double lon, double lat) {
    double ret = -100 + 2.0 * lon + 3.0 * lat + 0.2 * lat * lat + 0.1 * lon * lat + 0.2 * sqrt((abs(lon)));
    ret += (20.0 * sin(6.0 * lon * M_PI) + 20 * sin(2.0 * lon * M_PI)) * 2.0 / 3.0;
    ret += (20.0 * sin(lat * M_PI) + 40.0 * sin(lat / 3.0 * M_PI)) * 2.0 / 3.0;
    ret += (160.0 * sin(lat / 12.0 * M_PI) + 320.0 * sin(lat / 30.0 * M_PI)) * 2.0 / 3.0;
    return ret;
}

Coordinate gcj2wgs(Coordinate gcj_coord) {
    auto gcj_lon = gcj_coord.lon, gcj_lat = gcj_coord.lat;
    Coordinate wgs_coord;
    if (out_of_china(gcj_lon, gcj_lat)) {
        wgs_coord.lon = gcj_lon;
        wgs_coord.lat = gcj_lat;
        return wgs_coord;
    } else {
        double d_lat = translate_lat(gcj_lon - 105.0, gcj_lat - 35.0);
        double d_lon = translate_lon(gcj_lon - 105.0, gcj_lat - 35.0);
        double rad_lat = gcj_lat / 180.0 * M_PI;
        double magic = sin(rad_lat);
        magic = 1 - E * magic * magic;
        double s_magic = sqrt(magic);
        d_lon = (d_lon * 180.0) / (A / s_magic * cos(rad_lat) * M_PI);
        d_lat = (d_lat * 180.0) / ((A * (1 - E)) / (magic * s_magic) * M_PI);
        wgs_coord.lon = gcj_lon - d_lon;
        wgs_coord.lat = gcj_lat - d_lat;
        return wgs_coord;
    }
}

Coordinate wgs2gcj(Coordinate wgs_coord) {
    auto wgs_lon = wgs_coord.lon, wgs_lat = wgs_coord.lat;
    Coordinate gcj_pos;
    if (out_of_china(wgs_lon, wgs_lat)) {
        gcj_pos.lon = wgs_lon;
        gcj_pos.lat = wgs_lat;
        return gcj_pos;
    } else {
        double d_lat = translate_lat(wgs_lon - 105.0, wgs_lat - 35.0);
        double d_lon = translate_lon(wgs_lon - 105.0, wgs_lat - 35.0);
        double rad_lat = wgs_lat / 180.0 * M_PI;
        double magic = sin(rad_lat);
        magic = 1 - E * magic * magic;
        double s_magic = sqrt(magic);
        d_lon = (d_lon * 180.0) / (A / s_magic * cos(rad_lat) * M_PI);
        d_lat = (d_lat * 180.0) / ((A * (1 - E)) / (magic * s_magic) * M_PI);
        gcj_pos.lon = wgs_lon + d_lon;
        gcj_pos.lat = wgs_lat + d_lat;
        return gcj_pos;
    }
}

Coordinates batch_wgs2gcj(const Coordinates &wgs_coords) {
    Coordinates res;
    for (auto wgs_coord: wgs_coords) {
        res.push_back(wgs2gcj(wgs_coord));
    }
    return res;
}

Coordinates batch_gcj2wgs(const Coordinates &gcj_coords) {
    Coordinates res;
    for (auto gcj_coord: gcj_coords) {
        res.push_back(gcj2wgs(gcj_coord));
    }
    return res;
}

Coordinates batch_wgs2gcj(const osm::NodeList &wgs_nodes) {
    Coordinates res;
    for (const auto &wgs_node: wgs_nodes) {
        res.push_back(wgs2gcj(wgs_node.coord));
    }
    return res;
}

Coordinates batch_gcj2wgs(const osm::NodeList &gcj_nodes) {
    Coordinates res;
    for (const auto &gcj_node: gcj_nodes) {
        res.push_back(gcj2wgs(gcj_node.coord));
    }
    return res;
}