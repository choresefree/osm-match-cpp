/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/2 01:12
* @Description: TODO
*/

#include <iostream>
#include "osm/map.h"
#include "xml/pugixml.h"

using namespace pugi;
using namespace std;
using namespace osm;

int main() {
    Map map = osm::Map();
    map.load_from_osm_offline("/Users/xiezhenyu/GIthubProjects/cupid/input.osm", true);
    Node node1 = Node("test1", 121.43355809975877, 31.340975601141277);
    Node node2 = Node("test1", 121.4301971, 31.3505044);
    Node node3 = Node("test2", 121.43847165767913, 31.359978913324564);
    string id1 = map.add_node(node1);
    NodeIDList ids = map.add_nodes({{"node2", node2}, {"node3", node3}});
    printf("new node id: %s %s %s\n", id1.c_str(), ids[0].c_str(), ids[1].c_str());
    string way_id1 = map.add_way({id1, ids[0], ids[1], map.get_nodes().begin()->first}, {{"test", "success"}});
    printf("new way id: %s\n", way_id1.c_str());
    auto ways = map.find_node_parents("-1");
    for (const auto &way: ways) {
        printf("parents %s\n", way.second.id.c_str());
    }
    map.dump_to_xml("/Users/xiezhenyu/GIthubProjects/cupid/output.osm");
    return 0;
}