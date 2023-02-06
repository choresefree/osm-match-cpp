/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/3 22:31
* @Description: TODO
*/

#include "match/match.h"

using namespace match;

int main() {
    Match match = Match();
    match.load_track_from_json("/Users/xiezhenyu/数据集/GPS/json/Taxi_2034_0_7.json");
    match.load_map_from_osm("/Users/xiezhenyu/GithubProjects/cupid/test/resource/online.osm");
    match.geography2geometry();
    match.observe();
    for (const auto& ob_ways: match.observation) {
        auto coord = match.track_nodes_mapping[ob_ways.first].coord;
        printf("node id:%s\n (%f, %f)\n", ob_ways.first.c_str(), coord.lon, coord.lat);
        for (const auto& way_id : ob_ways.second){
            printf("%s ", way_id.c_str());
        }
        printf("\n");
    }
}