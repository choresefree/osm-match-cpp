/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/1/31 10:54
* @Description: matching algorithm implementation class
*/

#ifndef CUPID_MATCH_H
#define CUPID_MATCH_H

#include <string>
#include "osm/map.h"
#include "geometry/rtree.h"

const int DIM = 2;

struct Score {
    std::string way_id;
    double score;
};

typedef std::vector<Score> Scores;

typedef std::vector<Scores> ScoreMatrix;

namespace match {
    class Match {
    public:
        Match();

        bool load_track_from_json(const std::string &file_path);

        bool load_map_from_osm(const std::string &file_path);

        void print_track();

        void geography2geometry();

        static bool observe_callback(const Line &line);

        void observe();

        ScoreMatrix cal_score();

        void viterbi();

        std::vector<Lines> observation;

        osm::Map osm_map;

        Segments track;
    private:
        RTree<Line, double, DIM, double> rtree;
    };
}

#endif //CUPID_MATCH_H
