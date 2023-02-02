/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/1/31 10:54
* @Description: TODO
*/

#ifndef CUPID_WAY_H
#define CUPID_WAY_H

#include "node.h"

namespace osm {
    class Way {
    public:
        Way();

        Way(std::string id, NodeIDList node_ids);

        Way(std::string id, NodeIDList node_ids, Tags tags);

        NodeIDList get_node_ids() const;


        std::string id;
        Tags tags;
    private:
        NodeIDList node_ids;
    };

    typedef std::vector<std::string> WayIDList;
    typedef std::vector<Way> WayList;
    typedef std::unordered_map<std::string, Way> WayMap;
}

#endif //CUPID_WAY_H
