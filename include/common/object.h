/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/7 10:14
* @Description: TODO
*/

#ifndef CUPID_OBJECT_H
#define CUPID_OBJECT_H

#include <unordered_map>
#include <string>

typedef std::unordered_map<std::string, std::string> Tags;

class Object {
public:
    Tags get_tags() const;
    std::string get_tag(const std::string& key);
    int set_tag(const std::string& key, const std::string& value);


    std::string id;
    Tags tags;

};

#endif //CUPID_OBJECT_H
