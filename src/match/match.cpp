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

const double EXTEND_LEN = 25;
const double THICK_TRACK_INTERVAL = 50;

bool match::Match::load_track_from_json(const std::string &file_path) {
    Json::Value read_value;
    bool read_status = load_json(read_value, file_path);
    if (!read_status) {
        return false;
    }
    int node_id = 0;
    Points ps;
    for (auto const &p: read_value) {
        osm::Node node;
        Tags tags;
        for (const auto &key: p.getMemberNames()) {
            if (key == "lon") {
                node.coord.lon = p["lon"].asDouble();
            } else if (key == "lat") {
                node.coord.lat = p["lat"].asDouble();
            } else {
                tags[key] = p[key].asString();
            }
        }
        if (node.coord.lon == 0 || node.coord.lat == 0) {
            printf("lack necessary lon or lat\n");
            return false;
        }
        Point point = coordinate2relative(node.coord);
        point.id = std::to_string(node_id++);
        point.tags = tags;
        ps.push_back(point);
    }
    if (ps.size() <= 1) {
        printf("at least two track points");
        return false;
    }
    ps = thick(ps, THICK_TRACK_INTERVAL);
    for (int i = 1; i < ps.size(); i++) {
        Segment seg = Segment(ps[i - 1].id, ps[i - 1], ps[i], ps[i - 1].tags);
        this->track.push_back(seg);
    }
    return true;
}

bool match::Match::load_map_from_osm(const std::string &file_path) {
    this->osm_map.load_from_osm(file_path);
    return true;
}

match::Match::Match() = default;

void match::Match::print_track() {
    for (const auto &segment: this->track) {
        auto p1 = segment.point1, p2 = segment.point2;
        auto coord1 = relative2coordinate(p1), coord2 = relative2coordinate(p2);
        printf("node id: %s, coordinates: (%f, %f) --> (%f, %f)",
               segment.id.c_str(), coord1.lon, coord1.lat, coord2.lon, coord2.lat);
        for (const auto &tag: segment.tags) {
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
        Line line = Line(way.id, points, way.get_tags());
        auto extend_bbox = bbox(line.points, EXTEND_LEN);
        double left_bottom[2] = {extend_bbox.first.x, extend_bbox.first.y};
        double right_top[2] = {extend_bbox.second.x, extend_bbox.second.y};
        this->rtree.Insert(left_bottom, right_top, line);
    }
}

Lines cur_observation;

bool match::Match::observe_callback(const Line &line) {
    cur_observation.push_back(line);
    return true;
}


void match::Match::observe() {
    for (const auto &segment: this->track) {
        auto p1 = segment.point1, p2 = segment.point2;
        auto coord1 = relative2coordinate(p1), coord2 = relative2coordinate(p2);
        auto seg_bbox = bbox({p1, p2}, EXTEND_LEN);
        double left_bottom[2] = {seg_bbox.first.x, seg_bbox.first.y};
        double right_top[2] = {seg_bbox.second.x , seg_bbox.second.y};
        this->rtree.Search(left_bottom, right_top, this->observe_callback);
        this->observation.push_back(cur_observation);
        cur_observation.clear();
    }
    cur_observation.clear();
}