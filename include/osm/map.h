/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/1/31 10:54
* @Description: the osm osm_map class, which carries the geographic information in the osm file, currently only supports
 * coordinate points and way
*/

#ifndef CUPID_MAP_H
#define CUPID_MAP_H

#include "way.h"
#include "common/object.h"

typedef std::unordered_map<std::string, std::vector<std::string>> NodeParents;

namespace osm {
    class Map :public Object{
    public:
        Map();

        void init_map(const WayMap &ways, NodeMap nodes, bool only_highway);

        void dump_to_xml(const std::string &file_path) const;

        bool load_from_osm(const std::string &file_path, bool only_highway = false);

        bool load_from_osm(double min_lon, double min_lat, double max_lon, double max_lat, bool only_highway = false);

        Node get_node_by_id(const std::string &node_id);

        NodeList get_nodes_by_way_id(const std::string &way_id);

        Way get_way_by_id(const std::string &way_id);

        std::string add_node(Node node);

        NodeIDList add_nodes(const NodeMap &add_nodes);

        std::string add_way(const NodeIDList &node_ids, const Tags &tags);

        WayMap find_node_parents(const std::string &node_id);

        WayList get_ways() const;

        NodeList get_nodes() const;

        bool connect(const std::string &way_id1, const std::string &way_id2);

    private:
        WayMap ways;
        NodeMap nodes;
        NodeParents node_parents;
        int add_node_id = -1;
        int add_way_id = -1;
    };
}
#endif //CUPID_MAP_H
