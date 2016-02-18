#include "url_play_list.h"

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "str_separate.h"

#define     WEBSITE_STR         "website"
#define     FILE_STYLE_STR      "file_style"
#define     PROG_INDEX_STR      "prog_index"
#define     PROG_NAME_STR       "prog_name"
#define     MEDIA_TYPE_STR      "media_type"
#define     URL_STR                 "url"





#define MAX_WEB_SITE_NUM    21
#define MAX_STYLE_NUM       21

#define BUF_SIZE       1024

#define OPEN_PLAY_DEBUG

#ifdef OPEN_PLAY_DEBUG
#define SelPrintf(fmt, args...)    printf(fmt, ##args)
#else
#define SelPrintf(fmt, args...)
#endif



int max_website_id = 0;
int max_web_style_id[MAX_WEB_SITE_NUM] = {0};
int max_web_style_file_id[MAX_WEB_SITE_NUM][MAX_STYLE_NUM] = {0};
int max_web_file_id[MAX_WEB_SITE_NUM] = {0};

int current_website_id = 1;
int current_style_id = 1;
int current_file_id = 1;


int last_website_id = -1;
int last_style_id = -1;
int last_file_id = -1;




int current_webTop = 0;
int current_styleTop = 0;
int current_fileTop = 0;

int last_webTop = -1;
int last_styleTop = -1;
int last_fileTop = -1;

_webSiteIdProperty webNum[MAX_WEB_SITE_NUM];

_styleIdProperty styleNum[MAX_WEB_SITE_NUM][MAX_STYLE_NUM];



int PutIntoHead(_playProperty *tmp, _playProperty *play_head) {

    _playProperty *p;

    p = (_playProperty*)malloc(sizeof(_playProperty));

    if(p == NULL) {
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

    p->website_id = tmp->website_id;
    p->file_style_id = tmp->file_style_id;

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
        SelPrintf("\n\n");
    }







}


int ShowWebIdStyleId(int web_id, int style_id) {
    _styleIdProperty *styleTmp;
    _playProperty *p;


    if (style_id == 0) {
        SelPrintf("you should deal style_id before use it\n");
        return -1;
    }
    styleTmp = styleNum[web_id][style_id].next;
    if (styleTmp == NULL) {
        SelPrintf("url_play_list did not have this data(web_id:%d, style_id:%d)", web_id, style_id);    
        return -1;
    }

    while(styleTmp != NULL) {
        p = styleTmp->current_play;
        SelPrintf("~~~~~~~style~~~~~~~~\n");
        SelPrintf("website_id = %d\n", p->website_id);
        SelPrintf("%s = %s\n", WEBSITE_STR, p->website);
        SelPrintf("file_style_id = %d\n", p->file_style_id);
        SelPrintf("%s = %s\n", FILE_STYLE_STR, p->file_style);
        SelPrintf("%s = %d\n", PROG_INDEX_STR, p->prog_index);
        SelPrintf("%s = %s\n", PROG_NAME_STR, p->prog_name);
        SelPrintf("%s = %d\n", MEDIA_TYPE_STR, p->media_type);
        SelPrintf("%s = %s\n", URL_STR, p->url);    
        SelPrintf("\n");

        max_web_style_file_id[web_id][style_id]++;
        styleTmp = styleTmp->next;
    }
    return 0;

}

void SortStyleByWebId(int web_id, _playProperty *play_head) {
    _playProperty *p;
    _playProperty *q;
    _webSiteIdProperty *webTmp;

    _webSiteIdProperty *webTmpTmp;

    int start_id = 0;

    _styleIdProperty *styleTmp;


    //styleNum


    webTmp = webNum[web_id].next;

    while(webTmp != NULL) {
        p = webTmp->current_play;
        max_web_file_id[web_id]++;
        if(p->file_style_id == 0) {
            p->file_style_id = ++start_id;
            max_web_style_id[web_id] = p->file_style_id;
            styleTmp = (_styleIdProperty *)malloc(sizeof(_styleIdProperty));
            if (styleTmp == NULL) {
                SelPrintf("malloc fail:%s   %d\n", __FUNCTION__, __LINE__);    
                return;
            }
            styleTmp->current_play = p;
            styleTmp->next = styleNum[web_id][p->file_style_id].next;
            styleNum[web_id][p->file_style_id].next = styleTmp;


            webTmpTmp = webTmp->next;
            while(webTmpTmp != NULL) {

                q = webTmpTmp->current_play;
                if (q->file_style_id == 0) {
                    if(!strncmp(p->file_style, q->file_style, strlen(p->file_style))) {
                        q->file_style_id = p->file_style_id;

                        styleTmp = (_styleIdProperty *)malloc(sizeof(_styleIdProperty));
                        if (styleTmp == NULL) {
                            SelPrintf("malloc fail:%s   %d\n", __FUNCTION__, __LINE__);    
                            return;
                        }
                        styleTmp->current_play = q;
                        styleTmp->next = styleNum[web_id][q->file_style_id].next;
                        styleNum[web_id][q->file_style_id].next = styleTmp;


                    }
                }
                webTmpTmp = webTmpTmp->next;
            }

        }

        SelPrintf("XXXXX\n");
        SelPrintf("website_id = %d\n", p->website_id);
        SelPrintf("%s = %s\n", WEBSITE_STR, p->website);
        SelPrintf("file_style_id = %d\n", p->file_style_id);
        SelPrintf("%s = %s\n", FILE_STYLE_STR, p->file_style);
        SelPrintf("%s = %d\n", PROG_INDEX_STR, p->prog_index);
        SelPrintf("%s = %s\n", PROG_NAME_STR, p->prog_name);
        SelPrintf("%s = %d\n", MEDIA_TYPE_STR, p->media_type);
        SelPrintf("%s = %s\n", URL_STR, p->url);    
        SelPrintf("\n");


        webTmp = webTmp->next;
    }

}




void SortByWebSite(_playProperty *play_head) {
    _playProperty *p;
    _playProperty *tmp;
    int start_id = 0;

    _webSiteIdProperty *webTmp;

    int i;

    p = play_head->next;
    if(p == NULL) {
        SelPrintf("not data here\n");
        return;
    }





    while(p != NULL) {
        if(p->website_id == 0) {
            p->website_id = ++start_id;
            max_website_id = p->website_id;
            if (p->website_id > (MAX_WEB_SITE_NUM - 1)) {
                SelPrintf("Only Support %d (web sites)\n", MAX_WEB_SITE_NUM - 1);  
                return;
            }
            webTmp = (_webSiteIdProperty *)malloc(sizeof(_webSiteIdProperty));
            if (webTmp == NULL) {
                SelPrintf("malloc fail:%s   %d\n", __FUNCTION__, __LINE__);    
                return;
            }
            webTmp->current_play = p;
            webTmp->next = webNum[p->website_id].next;
            webNum[p->website_id].next = webTmp;

            tmp = p->next;
            while(tmp != NULL) {
                if(tmp->website_id == 0) {
                    if(!strncmp(p->website, tmp->website, strlen(p->website))) {
                        tmp->website_id = p->website_id;


                        webTmp = (_webSiteIdProperty *)malloc(sizeof(_webSiteIdProperty));
                        if (webTmp == NULL) {
                            SelPrintf("malloc fail:%s   %d\n", __FUNCTION__, __LINE__);    
                            return;
                        }
                        webTmp->current_play = tmp;
                        webTmp->next = webNum[p->website_id].next;
                        webNum[p->website_id].next = webTmp;



                    }
                }
                tmp = tmp->next;
            }
        }
        p = p->next;
    }


#if 0    
    for(i = 1; i <= max_website_id; i++) {
        p = play_head->next;
        while(p != NULL) {
            if(p->website_id == i) {
                SelPrintf("~~~~~~~~~~~~~~~\n");
                SelPrintf("website_id = %d\n", p->website_id);
                SelPrintf("%s = %s\n", WEBSITE_STR, p->website);
                SelPrintf("file_style_id = %d\n", p->file_style_id);
                SelPrintf("%s = %s\n", FILE_STYLE_STR, p->file_style);
                SelPrintf("%s = %d\n", PROG_INDEX_STR, p->prog_index);
                SelPrintf("%s = %s\n", PROG_NAME_STR, p->prog_name);
                SelPrintf("%s = %d\n", MEDIA_TYPE_STR, p->media_type);
                SelPrintf("%s = %s\n", URL_STR, p->url);    
                SelPrintf("\n");
            }
            p = p->next;
        }

    }

#endif

}



void InitAllData(void) {
    int i,j;

    for(i = 0; i < MAX_WEB_SITE_NUM; i++) {
        max_web_style_id[i] = 0;
        max_web_file_id[i] = 0;
        for(j = 0; j < MAX_STYLE_NUM; j++) {
            max_web_style_file_id[i][j] = 0;
        }
    }
    current_website_id = 1;
    current_style_id = 1;
    current_file_id = 1;
    
    last_website_id = -1;
    last_style_id = -1;
    last_file_id = -1;
    

    current_webTop = 0;
    current_styleTop = 0;
    current_fileTop = 0;
    
    last_webTop = -1;
    last_styleTop = -1;
    last_fileTop = -1;

    

}

void FreeMallocData(_playProperty *play_head) {
    int i,j;
    _styleIdProperty *styleTmp;
     _styleIdProperty *free_styleTmp;

    _webSiteIdProperty *webTmp;
    
    _webSiteIdProperty *free_webTmp;


    _playProperty *playHeadTmp;
    _playProperty *free_playHeadTmp;

    



    for(i = 0; i < MAX_WEB_SITE_NUM; i++) {
        for(j = 0; j < MAX_STYLE_NUM; j++) {
            free_styleTmp = styleNum[i][j].next; 
            styleNum[i][j].next = NULL;
            styleNum[i][j].current_play = NULL;
            while(free_styleTmp != NULL) {
                styleTmp = free_styleTmp->next;
                //SelPrintf("free :%d %d %s\n", i, j, free_styleTmp->current_play->prog_name);
                //osal_task_sleep(200);
                free_styleTmp->next = NULL;
                free_styleTmp->current_play = NULL;
                free(free_styleTmp);
                free_styleTmp = styleTmp;
            }
        }
        
        free_webTmp = webNum[i].next;
        webNum[i].next = NULL;
        webNum[i].current_play = NULL;
        while(free_webTmp != NULL) {
            webTmp = free_webTmp->next;
            //SelPrintf("free web here :%d %d %s\n", i, j, free_webTmp->current_play->prog_name);
            //osal_task_sleep(200);
            free_webTmp->next = NULL;
            free_webTmp->current_play = NULL;
            free(free_webTmp);
            free_webTmp = webTmp;
        }

    }


    free_playHeadTmp = play_head->next;
    play_head->next = NULL;
    bzero(play_head, sizeof(_playProperty));
    while(free_playHeadTmp != NULL) {
        playHeadTmp = free_playHeadTmp->next;
        free_playHeadTmp->next = NULL;
        //SelPrintf("free data here:%s\n", free_playHeadTmp->prog_name);
        //osal_task_sleep(200);
        bzero(free_playHeadTmp, sizeof(_playProperty));
        free(free_playHeadTmp);
        free_playHeadTmp = playHeadTmp;

    }
    SelPrintf("free all data here~~\n");

}


void FreeAllLocate(_playProperty *play_head) {
    //free maclloc here
    FreeMallocData(play_head);
    InitAllData();

}

int ReadLineBuf(char *tmp_buf, int size, char *src) {
    char *p;
    int read_size = 0;
    
    p = src;
    while((*p != '\n' )&& (*p != '\0')) {
        read_size++;
        p++;
    }
    //if(*p != '\0') {
        read_size++;
    //}
    
    if(read_size > size) {
        read_size = size;
    }
    strncat(tmp_buf, src, read_size);
    //SelPrintf("size:%d tmp_buf:%s  len:%d\n", size, tmp_buf, read_size);
    
    return read_size;
}



#define READ_SIZE   8000
int TextRead(char *file_path, _playProperty *play_head) {
    FILE *fp;
    int size;
    char buf[READ_SIZE];
    char *p;
    char line_buf[256];
    int tmp_len;
    
    fp = fopen(file_path, "r");
    
    if(fp == NULL) {
        SelPrintf("[%s:%d]open %s fail use before file list\n", __FUNCTION__, __LINE__, file_path); 
        return -1;
    }

    size = fread(buf, 1, READ_SIZE, fp);
    SelPrintf("read size is %d strlen:%d\n", size, strlen(buf));

    fclose(fp);
    
    SelPrintf("start printf:\n");

    
    p = buf;
    while(size > 0) {
        bzero(line_buf, sizeof(line_buf));
        tmp_len = ReadLineBuf(line_buf, size, p);


        
        SelPrintf("%s\n", line_buf);
        if(PutToStruct(line_buf, play_head) < 0) {
                return -1;
        }
        
        p += tmp_len;        
        size -= tmp_len;
    }


    DealGetData(play_head);
    
    return 0;
}

int PutToStruct(char *buf, _playProperty *play_head) {
    _playProperty tmp;

    
    if((buf[0] != '\r') && (buf[0] != '\n')) {

        if(buf[0] != '#') {
            //SelPrintf("%s", buf); 

            //buf[strlen(buf) - 1] = '\0';
            trim(buf);
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
                tmp.website_id = 0;
                tmp.file_style_id = 0;
                if(PutIntoHead(&tmp, play_head) < 0) {
                    return -1;
                }
                SelPrintf("\n");
            }

        }
    }

    return 0;
}

void DealGetData(_playProperty *play_head) {
    int i, j;

    ShowUrlList(play_head);

    SortByWebSite(play_head);    

    for(i = 0; i < max_website_id; i++) {
        SortStyleByWebId(i+1, play_head);
    }

    for(i = 1; i <= max_website_id; i++) {
        for(j = 1; j <= max_web_style_id[i]; j++) {
            ShowWebIdStyleId(i, j);
        }

    }



    SelPrintf("max_website_id:%d\n", max_website_id);
    for(i = 1; i <= max_website_id; i++) {
        SelPrintf("max_style is %d\n", max_web_style_id[i]);

    }

    for(i = 1; i <= max_website_id; i++) {
        for(j = 1; j <= max_web_style_id[i]; j++) {
            SelPrintf("max web sytle file is %d\n", max_web_style_file_id[i][j]);
        }
    }

    
    /*
       ShowWebIdStyleId(1, 1);
       ShowWebIdStyleId(1, 2);
       ShowWebIdStyleId(1, 3);
       ShowWebIdStyleId(1, 4);
       ShowWebIdStyleId(2, 1);
       ShowWebIdStyleId(2, 2);
       */

}


int GetPlayList(char *file_path, _playProperty *play_head) {
    FILE *fp;
    char buf[BUF_SIZE];
    int ret;
    
    
    static int getPlayListFlag = -1;
    fp = fopen(file_path, "r");
    if(fp == NULL) {
        SelPrintf("[%s:%d]open %s fail use before file list\n", __FUNCTION__, __LINE__, file_path); 
        return getPlayListFlag;
    }

    if (getPlayListFlag == 1) {

        FreeAllLocate(play_head);
        //return 0; 
    }


    
    SelPrintf("start here\n\n");

    play_head->next = NULL;
    while(!feof(fp)) {
        bzero(buf, sizeof(buf));
        if(fgets(buf, BUF_SIZE, fp)) {

            if(PutToStruct(buf, play_head) < 0) {
                return -1;
            }
        } else {
            break;
        }

    }

    fclose(fp);

    DealGetData(play_head);
    
    getPlayListFlag = 1;
    return 0;
}


