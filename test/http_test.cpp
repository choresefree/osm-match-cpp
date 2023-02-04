/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/4 00:19
* @Description: TODO
*/

#include <iostream>
#include "http/httplib.h"
#include "common/common.h"

int main()
{
    httplib::Client cli("http://overpass-api.de");
    if (auto res = cli.Get("/api/map?bbox=121.473600,31.176300,121.489100,31.214100")) {
        if (res->status == 200) {
            std::cout << res->body << std::endl;
            dump_file(res->body, "/Users/xiezhenyu/GithubProjects/cupid/test/resource/new.osm");
        }else{
            printf("http status exception: %d\n", res->status);
        }
    } else {
        auto err = res.error();
        std::cout << "HTTP error: " << httplib::to_string(err) << std::endl;
    }
}