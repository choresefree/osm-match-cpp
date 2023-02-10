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
//    match.load_track_from_json("/Users/xiezhenyu/数据集/GPS/json/Taxi_2034_51_64.json");
//    match.load_map_from_osm("/Users/xiezhenyu/GithubProjects/cupid/test/resource/map.osm");
//    match.geography2geometry();
//    match.observe();
//    auto match_result = match.viterbi();
    auto match_result = match.match("/Users/xiezhenyu/数据集/GPS/json/Taxi_2034_743_746.json");
    for (const auto& way_id: match_result){
        printf("%s ", way_id.c_str());
    }
    return 0;
}