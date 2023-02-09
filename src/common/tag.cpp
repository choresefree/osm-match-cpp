/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/7 10:18
* @Description: TODO
*/
#include "common/object.h"

Tags Object::get_tags() const {
    return this->tags;
}

std::string Object::get_tag(const std::string& key) {
    if (this->tags.find(key) == this->tags.end()){
        return "";
    } else{
        return this->tags.find(key)->second;
    }
}

int Object::set_tag(const std::string& key, const std::string& value) {
    if (this->tags.find(key) == this->tags.end()){
        this->tags[key] = value;
        return 1;
    } else{
        this->tags[key] = value;
        return 0;
    }
}
