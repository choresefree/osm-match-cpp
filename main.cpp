/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/1/31 10:54
* @Description: TODO
*/

#include <iostream>
#include "osm/map.h"
#include "xml/pugixml.h"
#include "xml/pugiconfig.h"

using namespace pugi;
using namespace std;
using namespace osm;

int main() {
    Map map = osm::Map();
    map.load_from_osm_offline("/Users/xiezhenyu/CLionProjects/cupid/input.osm", true);
    map.dump_to_xml("/Users/xiezhenyu/CLionProjects/cupid/output.osm");
    return 0;
}
