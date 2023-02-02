/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/1/31 10:54
* @Description: TODO
*/

#include "osm/way.h"

osm::Way::Way(std::string id, osm::NodeIDList node_ids) {
    this->id = std::move(id);
    this->node_ids = std::move(node_ids);
}

osm::Way::Way(std::string id, osm::NodeIDList node_ids, Tags tags) {
    this->id = std::move(id);
    this->node_ids = std::move(node_ids);
    this->tags = std::move(tags);
}

std::vector<std::string> osm::Way::get_node_ids() const {
    return this->node_ids;
}

osm::Way::Way() {

}
