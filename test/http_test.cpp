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
    std::string url = "http://overpass-api.de";
    std::string api = "/api/map?bbox=121.458000,31.199600,121.472500,31.244500";
    httplib::Client cli(url);
    cli.set_connection_timeout(500);
    cli.set_read_timeout(500);
    if (auto res = cli.Get(api)) {
        if (res->status == 200) {
            std::cout << res->body << std::endl;
            dump_file(res->body, "/Users/xiezhenyu/GithubProjects/cupid/test/resource/new.osm");
        }else{
            printf("http status exception: %d\n", res->status);
        }
    } else {
        auto err = res.error();
        std::cout << "http error: " << httplib::to_string(err) << std::endl;
    }
}