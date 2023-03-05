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
//    match.load_map_from_osm("/Users/xiezhenyu/MomentaProject/DeepLearning/osm-match/osm_match/map.osm");
//    match.geography2geometry();
//    match.observe();
//    auto match_result = match.viterbi();
    auto match_result = match.match(
            "/Users/xiezhenyu/GithubProjects/cupid/resource/Taxi_2034_496_501.json",
            "/Users/xiezhenyu/GithubProjects/cupid/resource/map.osm");
    for (const auto& way_id: match_result){
        printf("%s ", way_id.c_str());
    }
//    match.dump_map("/Users/xiezhenyu/GithubProjects/cupid/resource/map.osm");
//    match.dump_map("/Users/xiezhenyu/GithubProjects/cupid/resource/map.osm");
    match.dump_track("/Users/xiezhenyu/GithubProjects/cupid/resource/track.osm");
    match.dump_result("/Users/xiezhenyu/GithubProjects/cupid/resource/res.osm");
    return 0;
}