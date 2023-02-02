/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/1/31 10:54
* @Description: TODO
*/

#ifndef CUPID_MAP_H
#define CUPID_MAP_H

#include "way.h"

typedef std::unordered_map<std::string, std::vector<std::string>> NodeParents;

namespace osm {
    class Map {
    public:
        Map();

        void init_map(const WayMap &ways, NodeMap nodes, bool only_highway);

        void dump_to_xml(const std::string &file_path) const;

        void load_from_osm(const std::string &file_path, bool only_highway = true);

        Node get_node_by_id(const std::string &node_id);

        Way get_way_by_id(const std::string &way_id);

        std::string add_node(Node node);

        NodeIDList add_nodes(const NodeMap& node);

        std::string add_way(const NodeIDList& node_ids, const Tags& tags);

        WayMap find_node_parents(const std::string& node_id);

        WayList get_ways() const;

        NodeList get_nodes() const;

    private:
        WayMap ways;
        NodeMap nodes;
        NodeParents node_parents;
        int add_node_id = -1;
        int add_way_id = -1;
    };
}
#endif //CUPID_MAP_H
