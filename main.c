#include <stdio.h>
#include <string.h>
#include <stdlib.h>









#include "url_play_list.h"

#define FILE_PATH_SIZE  256
char file_path[FILE_PATH_SIZE] = "url_play_list.txt";

_playProperty playHead;




#define URL_PLAY_LIST   "/mnt/uda1/url_play_list.txt"
//FILE * url_play_list_fp = NULL;



int main(void) {
    #if 1
    if(TextRead(file_path, &playHead) < 0) {
        printf("deal data fail\n");
        return -1;
    }
    #else
    if(GetPlayList(file_path, &playHead) < 0) {
        printf("get play list fail\n");
        return -1;
    }
    #endif
    //free(data);
    printf("\nget file end here\n");

    return 0;
}
