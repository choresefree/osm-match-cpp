/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/11 13:40
* @Description: TODO
*/

#ifndef CUPID_INPUT_H
#define CUPID_INPUT_H

#include <iostream>

enum choice {
    ENTER, QUIT, MORE
};


choice input_choice(){
    static int deep = 0;
    std::string res;
    printf("\nEnter your choice:");
    getline(std::cin, res);
    deep += 1;
    if (res == "1"){
        return ENTER;
    }
    if (deep == 10 || res == "2" || res == "3"){
        return QUIT;
    }
    printf("your choice must be 1, 2 or 3");
    return input_choice();
}


std::string input_track() {
    std::string res;
    printf("Enter the track point route path:");
    getline(std::cin, res);
    return res;
}

std::string input_map() {
    std::string res;
    printf("Enter the map file path (download online if not entered):");
    getline(std::cin, res);
    return res;
}

#endif //CUPID_INPUT_H
