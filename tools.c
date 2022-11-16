//
//  tools.c
//  page_replacement
//
//  Created by chaehee on 2022/11/15.
//

#include "tools.h"

int STREAM_SIZE=0;
int FRAME_SIZE=0;

int lowest_priority(int** frame, int cur){
    int cur_priority=0, priority=0;
    
    while(1){
        for(int i=0;i<FRAME_SIZE;i++){
            cur_priority = 1*frame[cur][1] + 2*frame[cur][2];
            
            if(cur_priority==priority)
                return cur;
            else
                cur = (cur+1)%FRAME_SIZE;
        }
        priority++;
    }
}

int how_far(int* ref, int pos, int page_num){
    int dist=0;
    for(int i=pos+1;i<STREAM_SIZE;i++){
        if(ref[i]!=page_num)
            dist++;
        else
            break;
    }
    
    return ++dist;
}

int is_exist(int* frame, int page_num){
    for(int i=0;i<FRAME_SIZE;i++){
        if(frame[i]==page_num)
            return i;
    }
    return NOTFOUND;
}

int is_exist_dimension(int** frame, int page_num){
    for(int i=0;i<FRAME_SIZE;i++){
        if(frame[i][0]==page_num)
            return i;
    }
    return NOTFOUND;
}

void print_frame(int* frame){
    for(int i=0;i<FRAME_SIZE;i++)
        printf("%5d", frame[i]);
}

void print_frame_dimension(int** frame){
    for (int i=0;i<FRAME_SIZE;i++)
        printf("%5d",frame[i][0]);
}

int* get_random_input(int esc_flag){
    STREAM_SIZE = 500;
    
    srand((unsigned int)time(NULL));
    int* ref;
    
    if(esc_flag==1){
        ref = (int*) calloc(STREAM_SIZE*2, sizeof(int));
        
        for (int i = 0; i < STREAM_SIZE*2; i++) {
            if(i%2==0){
                ref[i] = rand()%30+1;
            }
            else{
                ref[i] = rand()%2;
            }
        }
    }
    else{
        ref = (int*) calloc(STREAM_SIZE, sizeof(int));
        
        for (int i = 0; i < STREAM_SIZE*2; i++) {
            ref[i] = rand()%30+1;
        }
    }
    
    return ref;
}

int* get_file_input(int esc_flag){
    FILE* fp = fopen("input.txt", "r");
    if(fp==NULL){
        printf("ERROR : open file input.txt\n");
        exit(0);
    }
    
    fseek(fp, 0, SEEK_END);
    int size = (int) ftell(fp);
    
    char* buffer = (char*) calloc(size, sizeof(char));
     
    fseek(fp, 0, SEEK_SET);
    fread(buffer, size, 1, fp);
    
    int index=1;
    int* ref = (int*) calloc(1, sizeof(int));
    
    char* ptr = strtok(buffer, " ");
    while(ptr!=NULL){
        ref[index-1] = atoi(ptr);
        
        ptr = strtok(NULL, " ");
        if(ptr!=NULL)
            ref = realloc(ref, sizeof(int)*(++index));
    }
    
    if(esc_flag==1)
        STREAM_SIZE = index/2;
    else
        STREAM_SIZE = index;
    
    free(buffer);
    fclose(fp);
    
    return ref;
}

int* convert_esc_to_normal(int* esc_ref){
    int* ref = (int*) calloc(STREAM_SIZE, sizeof(int));
     
    for (int i = 0; i < STREAM_SIZE*2; i++) {
        if(i%2==0){
            ref[i] = esc_ref[i];
        }
    }
    
    return ref;
}
