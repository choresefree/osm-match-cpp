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

struct ViterbiT {
    std::string way_id;
    osm::WayIDList tracing;
    double score;
};

typedef std::vector<Score> Scores;

typedef std::vector<Scores> ScoreMatrix;

namespace match {
    class Match {
    public:
        Match();

        osm::WayIDList match(const std::string &track_file_path, const std::string &map_file_path = "");

        void dump_result(const std::string& save_path);

        void dump_map(const std::string& save_path);

        void dump_track(const std::string& save_path);

    private:
        bool load_track_from_json(const std::string &file_path);

        void print_track();

        void geography2geometry();

        static bool observe_callback(const Line &line);

        void observe();

        ScoreMatrix cal_score();

        void viterbi();

        std::vector<Lines> observation;
        osm::Map osm_map;
        double min_lon = INFINITY, min_lat = INFINITY, max_lon = 0, max_lat = 0;
        Segments track;
        RTree<Line, double, DIM, double> rtree;
        osm::WayIDList match_result;
    };
}

#endif //CUPID_MATCH_H
