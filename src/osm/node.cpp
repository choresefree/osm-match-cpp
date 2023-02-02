/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/1/31 10:54
* @Description: TODO
*/

#include <utility>
#include "osm/tag.h"
#include "osm/node.h"

osm::Node::Node(std::string id, double lon, double lat) {
    this->id = std::move(id);
    this->coord = {lon, lat};
}

osm::Node::Node(std::string id, double lon, double lat, Tags tags) {
    this->id = std::move(id);
    this->coord = {lon, lat};
    this->tags = std::move(tags);
}

osm::Node::Node() {
}
