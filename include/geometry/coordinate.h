/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/1/31 10:54
* @Description: TODO
*/
#ifndef CUPID_COORDINATE_H
#define CUPID_COORDINATE_H


coordinate coordinate2relative(coordinate coord);

coordinates coordinates2relative(const coordinates &coords);

double distance(coordinate coord1, coordinate coord2);

double cal_length(const std::vector<coordinate> &coords);

#endif //CUPID_COORDINATE_H