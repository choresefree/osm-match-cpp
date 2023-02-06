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


namespace match {
    class Match {
    public:
        Match();

        bool load_track_from_json(const std::string &file_path);

        bool load_map_from_osm(const std::string &file_path);

        void print_track();

        void geography2geometry();

        static bool observe_callback(const std::string &line_id);

        void observe();

        void cal_score_matrix();

        void viterbi();

        osm::NodeMap track_nodes_mapping;
        std::unordered_map<std::string, osm::WayIDList> observation;

    private:
        Points track_points;
        RTree<std::string, double, DIM, double> rtree;
        osm::Map osm_map;
        std::unordered_map<std::string, Line> map_line_mapping;
    };
}

#endif //CUPID_MATCH_H
