/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/9 21:03
* @Description: TODO
*/
#include "match/match.h"
#include "geometry/transform.h"

double cal_angle_score(double angle) {
    if (angle >= M_PI / 2) {
        return 0;
    }
    if (angle > M_PI / 2) {
        return 0.25;
    }
    if (angle > M_PI / 6) {
        return 0.5;
    }
    return 1 - angle / (M_PI / 3);
}

double cal_distance_score(double distance) {
    if (distance >= 500) {
        return 0;
    }
    if (distance >= 100) {
        return 0.25;
    }
    if (distance >= 50) {
        return 0.5;
    }
    return 1 - distance / 100;
}


ScoreMatrix match::Match::cal_score() {
    ScoreMatrix score_matrix;
    for (int i = 0; i < this->observation.size(); i++) {
        Scores scores;
        auto segment = this->track[i];
        auto p1 = segment.point1, p2 = segment.point2;
        auto coord1 = relative2coordinate(p1), coord2 = relative2coordinate(p2);
//        printf("node id: %s, coordinates: (%f, %f) --> (%f, %f)\n",
//               segment.id.c_str(), coord1.lon, coord1.lat, coord2.lon, coord2.lat);
        for (auto line: this->observation[i]) {
            double cur_angle = angle({line.points[0], line.points[line.points.size() - 1]}, segment);
            if (line.get_tag("oneway") == "yes") {
                cur_angle = std::min(cur_angle, M_PI - cur_angle);
            }
            double angle_score = cal_angle_score(cur_angle);
            if (angle_score == 0) {
                continue;
            }
            double cur_distance = (distance(segment.point1, line.points) +
                                   distance(segment.point2, line.points)) / 2;
            double distance_score = cal_distance_score(cur_distance);
            if (distance_score == 0) {
                continue;
            }
//            printf("way id:%s, angle:%f, angle score:%f, distance score:%f\n",
//                   line.id.c_str(), cur_angle, angle_score, distance_score);
            Score cur_way_score = Score{line.id, 0.5 * angle_score + 0.5 * distance_score};
            scores.push_back(cur_way_score);
        }
        score_matrix.push_back(scores);
    }
    return score_matrix;
}