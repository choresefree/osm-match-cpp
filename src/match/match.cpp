/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/3 22:31
* @Description: TODO
*/

#include "match/match.h"
#include "json/json.h"
#include "common/common.h"

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
            } else{
                tags[key] = point[key].asString();
            }
        }
        if (node.coord.lon == 0 || node.coord.lat == 0){
            printf("lack necessary lon or lat\n");
            return false;
        }
        node.id = std::to_string(node_id++);
        node.tags = tags;
        this->track.push_back(node);
    }
    return true;
}

match::Match::Match() = default;

void match::Match::print_track() {
    for (const auto& node : this->track){
        printf("node id: %s, coordinate: (%f, %f)", node.id.c_str(), node.coord.lon, node.coord.lat);
        for (const auto& tag : node.tags){
            printf(", %s: %s", tag.first.c_str(), tag.second.c_str());
        }
        printf("\n");
    }
}
