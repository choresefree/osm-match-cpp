/**
* @Projectname: cupid
* @Author: sefree
* @Email: 1836662622@qq.com
* @Data:2023/2/2 01:12
* @Description: TODO
*/

#include "match/match.h"
#include "menu/input.h"
#include "menu/icon.h"


int main() {
    printf("%s", ICON.c_str());
    while (true) {
        auto choice = input_choice();
        if (choice == QUIT) {
            return 0;
        }
        if (choice == MORE) {
            // do something
            return 0;
        }
        auto track_file_path = input_track();
        auto map_file_path = input_map();
        match::Match match = match::Match();
        auto match_result = match.match(track_file_path, map_file_path);
        if (!match_result.empty()) {
            printf("match result: ");
            for (const auto &way_id: match_result) {
                printf("%s ", way_id.c_str());
            }
            printf("\n");
        }
    }
}