/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/3 01:18
* @Description: TODO
*/

#ifndef CUPID_COMMON_H
#define CUPID_COMMON_H

#include <fstream>
#include "json/json.h"

bool dump_file(const std::string &content, const std::string &file_path);

bool dump_json(const Json::Value &json, const std::string &file_path);

bool load_json(Json::Value &json, const std::string &file_path);

#endif //CUPID_COMMON_H
