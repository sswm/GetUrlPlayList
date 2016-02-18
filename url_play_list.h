#ifndef _URL_PLAY_LIST_H_

#define _URL_PLAY_LIST_H_

#define ADDRESS_SIZE             200
#define STYLE_SIZE                50
#define PROG_NAME_SIZE          50
#define URL_SIZE                   1024
typedef struct playProperty {
    int website_id;
    char website[ADDRESS_SIZE];
    int file_style_id;
    char file_style[STYLE_SIZE];
    int prog_index;
    char prog_name[PROG_NAME_SIZE];
    int media_type;
    char url[URL_SIZE];
    struct playProperty *next;
}_playProperty;


typedef struct webSiteIdProperty {
    _playProperty *current_play;
    struct webSiteIdProperty *next;
}_webSiteIdProperty;

typedef struct styleIdProperty {
    _playProperty *current_play;
    struct styleIdProperty *next;
}_styleIdProperty;



int TextRead(char *file_path, _playProperty *play_head);


void DealGetData(_playProperty *play_head);


int GetPlayList(char *file_path, _playProperty *play_head);


#endif

