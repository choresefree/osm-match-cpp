/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/3 22:31
* @Description: TODO
*/

#include <iostream>
#include "match/match.h"
#include "json/json.h"
#include "common/common.h"
#include "geometry/transform.h"


double EXTEND_LEN = 1;

bool match::Match::load_track_from_json(const std::string &file_path) {
    Json::Value read_value;
    bool read_status = load_json(read_value, file_path);
    if (!read_status) {
        return false;
    }
    int node_id = 0;
    for (auto const &point: read_value) {
        osm::Node node;
        osm::Tags tags;
        for (const auto &key: point.getMemberNames()) {
            if (key == "lon") {
                node.coord.lon = point["lon"].asDouble();
            } else if (key == "lat") {
                node.coord.lat = point["lat"].asDouble();
            } else {
                tags[key] = point[key].asString();
            }
        }
        if (node.coord.lon == 0 || node.coord.lat == 0) {
            printf("lack necessary lon or lat\n");
            return false;
        }
        node.id = std::to_string(node_id++);
        node.tags = tags;
        this->track_nodes_mapping[node.id] = node;
    }
    return true;
}

bool match::Match::load_map_from_osm(const std::string &file_path) {
    this->osm_map.load_from_osm(file_path);
    return true;
}

match::Match::Match() = default;

void match::Match::print_track() {
    for (const auto &node: this->track_nodes_mapping) {
        printf("node id: %s, coordinate: (%f, %f)",
               node.first.c_str(), node.second.coord.lon, node.second.coord.lat);
        for (const auto &tag: node.second.tags) {
            printf(", %s: %s", tag.first.c_str(), tag.second.c_str());
        }
        printf("\n");
    }
}

void match::Match::geography2geometry() {
    osm::WayList ways = this->osm_map.get_ways();
    for (const auto &way: ways) {
        Points points;
        osm::NodeList nodes = this->osm_map.get_nodes_by_way_id(way.id);
        for (const auto &node: nodes) {
            auto cur_point = coordinate2relative(node.coord);
            cur_point.id = node.id;
            points.push_back(cur_point);
        }
        Line line = Line(way.id, points);
        this->map_line_mapping[line.id] = line;
    }
    for (const auto &node: this->track_nodes_mapping) {
        auto cur_point = coordinate2relative(node.second.coord);
        cur_point.id = node.first;
        this->track_points.push_back(cur_point);
    }
    for (const auto &line: this->map_line_mapping) {
        auto extend_bbox = bbox(line.second.points, EXTEND_LEN);
        double left_bottom[2] = {extend_bbox.first.x, extend_bbox.first.y};
        double right_top[2] = {extend_bbox.second.x, extend_bbox.second.y};
        this->rtree.Insert(left_bottom, right_top, line.second.id);
    }
}

osm::WayIDList cur_observation;

bool match::Match::observe_callback(const std::string &line_id) {
    cur_observation.push_back(line_id);
    return true;
}


void match::Match::observe() {
    for (const auto &point: this->track_points) {
        double left_bottom[2] = {point.x - EXTEND_LEN, point.y - EXTEND_LEN};
        double right_top[2] = {point.x + EXTEND_LEN, point.y + EXTEND_LEN};
        this->rtree.Search(left_bottom, right_top, this->observe_callback);
        this->observation[point.id] = cur_observation;
        cur_observation.clear();
    }
    cur_observation.clear();

}

