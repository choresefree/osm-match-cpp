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

namespace match {
    class Match {
    public:
        Match();

        bool load_track_from_json(const std::string &file_path);

        void print_track();
    private:
        osm::Map map;
        osm::NodeList track;
    };
}

#endif //CUPID_MATCH_H
