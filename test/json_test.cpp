/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/2 01:12
* @Description: TODO
*/

#include <iostream>
#include "common/common.h"

using namespace std;

int main() {
    // dump成json文件
    Json::Value write_value;
    write_value["id"] = 123;
    write_value["name"] = "James";
    write_value["score"] = Json::Value();
    write_value["score"]["math"] = 99;
    write_value["score"]["english"] = 84;
    string str_json = write_value.toStyledString();
    dump_json(write_value, "/Users/xiezhenyu/GithubProjects/cupid/test/resource/write.json");
    // 从json字符串加载数据
    Json::Reader reader;
    Json::Value read_value;
    if (reader.parse(str_json, read_value)) {
        if (!read_value["id"].isNull()) {
            cout << read_value["id"].asInt() << endl;
            cout << read_value["name"].asString() << endl;
        }
    }
    // 从json文件读取数据
    Json::Value read_value2;
    bool read_status = load_json(read_value2, "/Users/xiezhenyu/GithubProjects/cupid/test/resource/read.json");
    if (read_status){
        cout << read_value2["id"].asInt() << endl;
        cout << read_value2["score"]["math"].asInt() << endl;
    }
    return 0;
}