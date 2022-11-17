//
//  tools.c
//  page_replacement
//
//  Created by chaehee on 2022/11/15.
//

#include "tools.h"

int REF_SIZE=0;
int FRAME_SIZE=0;

int lowest_priority(int** frame, int cur){
    int cur_priority=0, priority=0;
    
    while(1){
        for(int i=0;i<FRAME_SIZE;i++){
            cur_priority = 2*frame[cur][1] + 1*frame[cur][2];
            
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
    for(int i=pos+1;i<REF_SIZE;i++){
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

void print_frame(int* frame, FILE* fp, int output_flag){
    for(int i=0;i<FRAME_SIZE;i++){
        printf("%5d", frame[i]);
        
        if(output_flag)
            fprintf(fp, "%5d", frame[i]);
    }
}

void print_frame_dimension(int** frame, FILE* fp, int output_flag){
    for (int i=0;i<FRAME_SIZE;i++){
        printf("%5d",frame[i][0]);
        
        if(output_flag)
            fprintf(fp, "%5d", frame[i][0]);
    }
}

int* get_random_input(int esc_flag){
    srand((unsigned int)time(NULL));
    printf("\nreference string : \n");
    
    int* ref;
    
    if(esc_flag==1){
        ref = (int*) calloc(REF_SIZE*2, sizeof(int));
        
        for (int i = 0; i < REF_SIZE*2; i++) {
            if(i%2==0){
                ref[i] = rand()%30+1;
                printf("%d ", ref[i]);
            }
            else{
                ref[i] = rand()%2;
                
                if(ref[i]==0)
                    printf("%c ", 'R');
                else
                    printf("%c ", 'W');
            }
        }
    }
    else{
        ref = (int*) calloc(REF_SIZE, sizeof(int));
        
        for (int i = 0; i < REF_SIZE; i++) {
            ref[i] = rand()%30+1;
            printf("%d ", ref[i]);
        }
    }
    
    printf("\n");
    return ref;
}

int* convert_esc_to_normal(int* esc_ref){
    int* ref = (int*) calloc(REF_SIZE, sizeof(int));
    
    int index=0;
    for (int i = 0; i < REF_SIZE*2; i++) {
        if(i%2==0){
            ref[index++] = esc_ref[i];
        }
    }
    
    return ref;
}

int* get_file_input(int esc_flag, char* file_name){
    FILE* fp = fopen(file_name, "r");
    if(fp==NULL){
        printf("ERROR : open file '%s'\n", file_name);
        exit(0);
    }
    
    printf("\nreference string : \n");
    
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
        
        if(esc_flag==1 && (index-1)%2==1){
            if(ref[index-1]==0)
                printf("%c ", 'R');
            else
                printf("%c ", 'W');
        }
        else
            printf("%d ", ref[index-1]);
        
        ptr = strtok(NULL, " ");
        if(ptr!=NULL)
            ref = realloc(ref, sizeof(int)*(++index));
    }
    
    if(esc_flag==1)
        REF_SIZE = index/2;
    else
        REF_SIZE = index;
    
    free(buffer);
    fclose(fp);
    
    printf("\n");
    return ref;
}
