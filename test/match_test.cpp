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
    match.load_track_from_json("/Users/xiezhenyu/数据集/GPS/json/Taxi_2034_51_64.json");
    match.load_map_from_osm("/Users/xiezhenyu/GithubProjects/cupid/test/resource/map.osm");
    match.geography2geometry();
    match.observe();
    auto score_matrix = match.cal_score();
    for (const auto &scores: score_matrix) {
        for (const auto &score: scores) {
            printf("way id:%s, score:%f\n", score.way_id.c_str(), score.score);
        }
        printf("------------------------------------------------------\n");
    }
}