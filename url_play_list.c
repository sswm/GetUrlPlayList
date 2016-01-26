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
        
        if(p->file_style_id == 0) {
            p->file_style_id = ++start_id;

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

int GetPlayList(char *file_path, _playProperty *play_head) {
    FILE *fp;
    char buf[BUF_SIZE];
    int ret;
    _playProperty tmp;
    int i;

    
    memset(&tmp, 0, sizeof(_playProperty));
    fp = fopen(file_path, "r");
    if(fp == NULL) {
        SelPrintf("[%s:%d]open %s fail", __FUNCTION__, __LINE__, file_path); 
        return -1;
    }
    SelPrintf("start here\n\n");
    play_head->next = NULL;
    while(!feof(fp)) {
        bzero(buf, sizeof(buf));
        if(fgets(buf, BUF_SIZE, fp)) {
            if((buf[0] != '\r') && (buf[0] != '\n')) {
                
                if(buf[0] != '#') {
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
                        tmp.website_id = 0;
                        tmp.file_style_id = 0;
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

    SortByWebSite(play_head);    

    for(i = 0; i < max_website_id; i++) {
        SortStyleByWebId(i+1, play_head);
    }


    ShowWebIdStyleId(1, 1);
    ShowWebIdStyleId(1, 2);
    ShowWebIdStyleId(1, 3);
    ShowWebIdStyleId(1, 4);
    ShowWebIdStyleId(2, 1);
    ShowWebIdStyleId(2, 2);
    return 0;
}

