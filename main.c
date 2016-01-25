#include <stdio.h>
#include <string.h>
#include <stdlib.h>









#include "url_play_list.h"

#define FILE_PATH_SIZE  256
char file_path[FILE_PATH_SIZE] = "url_play_list.txt";

_playProperty playHead;



int main(void) {

    if(GetPlayList(file_path, &playHead) < 0) {
        printf("get play list fail\n");
        return -1;
    }

    printf("\nget file end here\n");

    return 0;
}
