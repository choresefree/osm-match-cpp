/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/1/31 10:54
* @Description: TODO
*/

#ifndef CUPID_NODE_H
#define CUPID_NODE_H

#include <utility>
#include <string>
#include <vector>
#include <unordered_map>
#include "tag.h"
#include "common.h"

namespace osm {
    class Node {
    public:
        Node();

        Node(std::string id, double lon, double lat);

        Node(std::string id, double lon, double lat, Tags tags);

        std::string id;
        coordinate coord;
        Tags tags;
    };

    typedef std::vector<std::string> NodeIDList;
    typedef std::unordered_map<std::string, Node> NodeList;
}

#endif //CUPID_NODE_H
