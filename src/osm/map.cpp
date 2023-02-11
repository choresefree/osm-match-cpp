/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/1/31 10:54
* @Description: TODO
*/

#include <cstdio>
#include "osm/map.h"
#include "xml/pugixml.h"
#include "http/httplib.h"
#include "common/common.h"

const std::string DOWNLOAD_OSM_PATH = "/api/map?bbox=";
const std::string DOWNLOAD_OSM_URL = "http://overpass-api.de";
const std::string OSM_CACHE_DIR = "/Users/xiezhenyu/GithubProjects/cupid/test/resource/";

osm::NodeList osm::Map::get_nodes() const {
    NodeList res;
    for (const auto &node: this->nodes) {
        res.push_back(node.second);
    }
    return res;
}

osm::WayList osm::Map::get_ways() const {
    WayList res;
    for (const auto &way: this->ways) {
        res.push_back(way.second);
    }
    return res;
}

void osm::Map::build_map(const WayMap &input_ways, NodeMap input_nodes, bool only_highway = true) {
    for (auto way: input_ways) {
        bool high_way = true;
        if (way.second.tags.find("highway") == way.second.tags.end()) {
            high_way = false;
        }
        if (only_highway && !high_way) {
            continue;
        }
        NodeIDList cur_way_node_ids;
        for (const auto &node_id: way.second.get_node_ids()) {
            if (input_nodes.find(node_id) == input_nodes.end()) {
                printf("node%s in way%s does not exist in input input_nodes\n", node_id.c_str(), way.first.c_str());
                continue;
            }
            cur_way_node_ids.push_back(node_id);
        }
        this->ways.insert(way);
        for (const auto &node_id: cur_way_node_ids) {
            this->nodes[node_id] = input_nodes[node_id];
            this->node_parents[node_id].push_back(way.second.id);
        }
    }
}

osm::Map::Map() = default;

bool osm::Map::load_from_osm(const std::string &file_path, bool only_highway) {
    Map map = Map();
    pugi::xml_document doc;
    if (!doc.load_file(file_path.c_str())) {
        printf("load file %s failed\n", file_path.c_str());
    }
    pugi::xml_node root = doc.child("osm");
    auto xml_nodes = root.children("node");
    auto xml_ways = root.children("way");
    NodeMap map_nodes;
    WayMap map_ways;
    for (auto node: xml_nodes) {
        std::string node_id = node.attribute("id").as_string();
        double lon = node.attribute("lon").as_double();
        double lat = node.attribute("lat").as_double();
        if (lon == 0 || lat == 0) {
            continue;
        }
        auto node_tags = node.children("tag");
        Tags map_node_tags;
        for (auto tag: node_tags) {
            map_node_tags[tag.attribute("k").as_string()] = tag.attribute("v").as_string();
        }
        Node map_node = Node(node_id, lon, lat, map_node_tags);
        map_nodes[node_id] = map_node;
    }
    for (auto way: xml_ways) {
        std::string way_id = way.attribute("id").as_string();
        auto way_nodes = way.children("nd");
        NodeIDList map_way_node_ids;
        for (auto node_id: way_nodes) {
            std::string cur_node_id = node_id.attribute("ref").as_string();
            if (map_nodes.find(cur_node_id) == map_nodes.end()) {
                continue;
            }
            map_way_node_ids.push_back(node_id.attribute("ref").as_string());
        }
        auto way_tags = way.children("tag");
        Tags map_way_tags;
        for (auto tag: way_tags) {
            map_way_tags[tag.attribute("k").as_string()] = tag.attribute("v").as_string();
        }
        Way map_way = Way(way_id, map_way_node_ids, map_way_tags);
        map_ways[way_id] = map_way;
    }
    this->build_map(map_ways, map_nodes, only_highway);
    return true;
}

bool osm::Map::load_from_osm(double min_lon, double min_lat, double max_lon, double max_lat, bool only_highway) {
    std::string path = DOWNLOAD_OSM_PATH + std::to_string(min_lon) + "," + std::to_string(min_lat) + ","
            + std::to_string(max_lon) + "," + std::to_string(max_lat);
    printf("download osm from %s  %s\n", DOWNLOAD_OSM_URL.c_str(), path.c_str());
    httplib::Client cli(DOWNLOAD_OSM_URL);
    cli.set_connection_timeout(60  *5);
    cli.set_read_timeout(60 * 5);
    if (auto res = cli.Get(path)) {
        if (res->status == 200) {
            dump_file(res->body, OSM_CACHE_DIR + "http.osm");
        } else {
            printf("http status exception: %d\n", res->status);
            return false;
        }
    } else {
        auto err = res.error();
        printf("http error: %s\n", httplib::to_string(err).c_str());
        return false;
    }
    this->load_from_osm(OSM_CACHE_DIR + "http.osm", only_highway);
    return true;
//    remove((OSM_CACHE_DIR + "http.osm").c_str());
}

void osm::Map::dump_to_xml(const std::string &file_path) const {
    pugi::xml_document doc;
    pugi::xml_node declaration_node = doc.append_child(pugi::node_declaration);
    declaration_node.append_attribute("version") = "1.0";
    declaration_node.append_attribute("encoding") = "UTF-8";
    pugi::xml_node root = doc.append_child("osm"); //根节点
    root.append_attribute("version") = "0.6";
    for (const auto &map_node: this->get_nodes()) {
        pugi::xml_node cur_xml_node = root.append_child("node");
        cur_xml_node.append_attribute("id") = map_node.id.c_str();
        double lon = map_node.coord.lon, lat = map_node.coord.lat;
        cur_xml_node.append_attribute("lon") = std::to_string(lon).c_str();
        cur_xml_node.append_attribute("lat") = std::to_string(lat).c_str();
        cur_xml_node.append_attribute("version") = 1;
        for (const auto &map_node_tag: map_node.tags) {
            pugi::xml_node cur_xml_tag = cur_xml_node.append_child("tag");
            cur_xml_tag.append_attribute("k") = map_node_tag.first.c_str();
            cur_xml_tag.append_attribute("v") = map_node_tag.second.c_str();
        }
    }
    for (const auto &map_way: this->get_ways()) {
        pugi::xml_node cur_xml_way = root.append_child("way");
        cur_xml_way.append_attribute("id") = map_way.id.c_str();
        cur_xml_way.append_attribute("version") = 1;
        for (const auto &node_id: map_way.get_node_ids()) {
            pugi::xml_node cur_xml_node_id = cur_xml_way.append_child("nd");
            cur_xml_node_id.append_attribute("ref") = node_id.c_str();
        }
        for (const auto &map_way_tag: map_way.tags) {
            pugi::xml_node cur_xml_tag = cur_xml_way.append_child("tag");
            cur_xml_tag.append_attribute("k") = map_way_tag.first.c_str();
            cur_xml_tag.append_attribute("v") = map_way_tag.second.c_str();
        }
    }
    doc.save_file(file_path.c_str());
}

osm::Node osm::Map::get_node_by_id(const std::string &node_id) {
    return this->nodes[node_id];
}

osm::NodeList osm::Map::get_nodes_by_way_id(const std::string &way_id) {
    NodeList res;
    Way way = this->get_way_by_id(way_id);
    for (const auto &n_id: way.get_node_ids()) {
        res.push_back(this->get_node_by_id(n_id));
    }
    return res;
}

osm::Way osm::Map::get_way_by_id(const std::string &way_id) {
    return this->ways[way_id];
}

osm::WayMap osm::Map::find_node_parents(const std::string &node_id) {
    WayMap parents;
    if (this->nodes.find(node_id) == this->nodes.end()) {
        return parents;
    }
    for (const auto &parent_way_id: this->node_parents[node_id]) {
        parents[parent_way_id] = this->get_way_by_id(parent_way_id);
    }
    return parents;
}

std::string osm::Map::add_node(osm::Node node) {
    node.id = std::to_string(this->add_node_id--);
    this->nodes[node.id] = node;
    return node.id;
}

osm::NodeIDList osm::Map::add_nodes(const osm::NodeMap &add_nodes) {
    NodeIDList added_node_ids;
    for (const auto &node: add_nodes) {
        std::string node_id = this->add_node(node.second);
        added_node_ids.push_back(node_id);
    }
    return added_node_ids;
}

std::string osm::Map::add_way(const osm::NodeIDList &node_ids, const Tags &tags) {
    NodeIDList legal_node_ids;
    for (const auto &node_id: node_ids) {
        if (this->nodes.find(node_id) == this->nodes.end()) {
            continue;
        }
        legal_node_ids.push_back(node_id);
        this->node_parents[node_id].push_back(std::to_string(this->add_way_id));
    }
    Way add_way = Way(std::to_string(this->add_way_id), legal_node_ids, tags);
    this->ways[std::to_string(add_way_id--)] = add_way;
    return add_way.id;
}

bool osm::Map::connect(const std::string &way_id1, const std::string &way_id2) {
    Way way1 = this->get_way_by_id(way_id1);
    Way way2 = this->get_way_by_id(way_id2);
    NodeIDList way1_node_ids = way1.get_node_ids();
    NodeIDList way2_node_ids = way2.get_node_ids();
    for (std::string &node_id1: way1_node_ids) {
        for (std::string &node_id2: way2_node_ids) {
            if (node_id1 == node_id2) {
                return true;
            }
        }
    }
    return false;
}
