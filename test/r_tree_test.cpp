/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/6 23:54
* @Description: TODO
*/
#include "geometry/rtree.h"
#include "geometry/geometry.h"

using namespace std;

Lines res;


bool search_callback(const Line& line)
{
    res.push_back(line);
    return true;
}

int main() {
    RTree<Line, double, 2> rtree;
    double min[2] = {2, 3};
    double max[2] = {5, 9};
    Line l1 = Line("test", {{0, 0}, {1, 1}});
    rtree.Insert(min, max, l1);

    double min2[2] = {0, 0};
    double max2[2] = {2, 3};

    int hits = rtree.Search(min2, max2, search_callback);
    for (const auto& line : res){
        printf("%s", line.id.c_str());
    }
    return 0;
}