#include "url_play_list.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>


#define     WEBSITE_STR         "website"
#define     FILE_STYLE_STR      "file_style"
#define     PROG_INDEX_STR      "prog_index"
#define     PROG_NAME_STR       "prog_name"
#define     MEDIA_TYPE_STR      "media_type"
#define     URL_STR                 "url"



#define OPEN_PLAY_DEBUG


#define BUF_SIZE       1024

#ifdef OPEN_PLAY_DEBUG
#define SelPrintf(fmt, args...)    printf(fmt, ##args)
#else
#define SelPrintf(code)
#endif



int PutIntoHead(_playProperty *tmp, _playProperty *play_head) {

    _playProperty *p;

    p = (_playProperty*)malloc(sizeof(_playProperty));

    if (p == NULL) {
        SelPrintf("malloc _playProperty fail:%s   %d\n", __FUNCTION__, __LINE__);
        return -1;
    }
    
    p->next = play_head->next;
    play_head->next = p;

    strncpy(p->website, tmp->website, ADDRESS_SIZE);
    strncpy(p->file_style, tmp->file_style, STYLE_SIZE);
    p->prog_index = tmp->prog_index;
    strncpy(p->prog_name, tmp->prog_name, PROG_NAME_SIZE);
    p->media_type = tmp->media_type;
    strncpy(p->url, tmp->url, URL_SIZE);
    
    return 0;

}

void ShowUrlList(_playProperty *play_head) {

    _playProperty *p;

    p = play_head->next;

    while(p != NULL) {
        SelPrintf("%s = %s\n", WEBSITE_STR, p->website);
        SelPrintf("%s = %s\n", FILE_STYLE_STR, p->file_style);
        SelPrintf("%s = %d\n", PROG_INDEX_STR, p->prog_index);
        SelPrintf("%s = %s\n", PROG_NAME_STR, p->prog_name);
        SelPrintf("%s = %d\n", MEDIA_TYPE_STR, p->media_type);
        SelPrintf("%s = %s\n", URL_STR, p->url);
        p = p->next;
        printf("\n\n");
    }







}


int GetPlayList(char *file_path, _playProperty *play_head) {
    FILE *fp;
    char buf[BUF_SIZE];
    int ret;
    _playProperty tmp;

    memset(&tmp, 0, sizeof(_playProperty));
    fp= fopen(file_path, "r");
    if (fp == NULL) {
        SelPrintf("[%s:%d]open %s fail", __FUNCTION__, __LINE__, file_path); 
        return -1;
    }
    printf("start here\n\n");
    play_head->next = NULL;
    while(!feof(fp)) {
        bzero(buf, sizeof(buf));
        if(fgets(buf, BUF_SIZE, fp)) {
            if ((buf[0] != '\r') && (buf[0] != '\n')) {
                
                if (buf[0] != '#') {
                    //SelPrintf("%s", buf); 
                    
                    buf[strlen(buf) - 1] = '\0';
                    
                    if(!strncmp(buf, WEBSITE_STR, strlen(WEBSITE_STR))) {
                        strcpy(tmp.website, &buf[strlen(WEBSITE_STR) + 1]);   
                        //SelPrintf("%s = %s\n", WEBSITE_STR, tmp.website);
                    } else if(!strncmp(buf, FILE_STYLE_STR, strlen(FILE_STYLE_STR)))  {
                        strcpy(tmp.file_style, &buf[strlen(FILE_STYLE_STR) + 1]);  
                        //SelPrintf("%s = %s\n", FILE_STYLE_STR, tmp.file_style);
                    } else if(!strncmp(buf, PROG_INDEX_STR, strlen(PROG_INDEX_STR)))  {
                        tmp.prog_index = atoi(&buf[strlen(PROG_INDEX_STR) + 1]);
                        //SelPrintf("%s = %d\n", PROG_INDEX_STR, tmp.prog_index);
                    } else if(!strncmp(buf, PROG_NAME_STR, strlen(PROG_NAME_STR)))  {
                        strcpy(tmp.prog_name, &buf[strlen(PROG_NAME_STR) + 1]);  
                        //SelPrintf("%s = %s\n", PROG_NAME_STR, tmp.prog_name);
                    } else if(!strncmp(buf, MEDIA_TYPE_STR, strlen(MEDIA_TYPE_STR)))  {
                        tmp.media_type = atoi(&buf[strlen(MEDIA_TYPE_STR) + 1]); 
                        //SelPrintf("%s = %d\n", MEDIA_TYPE_STR, tmp.media_type);
                    } else if(!strncmp(buf, URL_STR, strlen(URL_STR)))  {
                        strcpy(tmp.url, &buf[strlen(URL_STR) + 1]);  
                        //SelPrintf("%s = %s\n", URL_STR, tmp.url);
                    }

                    
                    if(!strncmp(buf, "url=", 4)) {
                        if(PutIntoHead(&tmp, play_head) < 0) {
                            return -1;
                        }
                        SelPrintf("\n");
                    }
                    
                }
            }
        } else {
            break;
        }

    }
    
    fclose(fp);


    ShowUrlList(play_head);

    
    return 0;
}

