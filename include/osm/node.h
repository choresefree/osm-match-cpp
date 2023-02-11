/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/1/31 10:54
* @Description: TODO
*/

#ifndef CUPID_NODE_H
#define CUPID_NODE_H

#include <string>
#include "geometry/geometry.h"
#include "common/object.h"

namespace osm {
    class Node :public Object{
    public:
        Node();

        Node(std::string id, double lon, double lat);

        Node(std::string id, double lon, double lat, Tags tags);

        std::string id;
        Coordinate coord;
    };

    typedef std::vector<std::string> NodeIDList;
    typedef std::vector<Node> NodeList;
    typedef std::unordered_map<std::string, Node> NodeMap;
}

#endif //CUPID_NODE_H
