//
//  display.c
//  page_replacement
//
//  Created by chaehee on 2022/11/15.
//

#include "display.h"

extern int STREAM_SIZE;
extern int FRAME_SIZE;

int* get_random_input(void){
    STREAM_SIZE = 500;
    int* ref = (int*) calloc(STREAM_SIZE, sizeof(int));
    
    srand((unsigned int)time(NULL));
    
    for (int i = 0; i < STREAM_SIZE; i++) {
        ref[i] = rand()%30+1;
        //printf("%d ", ref[i]);
    }
    
    return ref;
}

int* get_file_input(void){
    FILE* fp = fopen("input.txt", "r");
    if(fp==NULL){
        printf("ERROR : open file\n");
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
    
    STREAM_SIZE = index;
    
    free(buffer);
    fclose(fp);
    
    return ref;
}

void user_menu(void){
    char command[10];
    char simulator_num[3]={'0','0','0'};
    printf("Select page replacement algorithm simulator (maximum 3 but (8) can only be selected by itself) \n");
    printf("(1) OPTIMAL  (2) FIFO  (3) LIFO  (4) LRU  (5) LFU  (6) SC  (7) ESC  (8) ALL\n>");
    
    scanf("%[^\n]", command);
    
    int index=0, len=0;
    while (command[len]!=0) {
        if(command[len]>'0' && command[len]<'9'){
            if(command[len+1]!=0){
                if(command[len+1]==' ' && index<3){
                    simulator_num[index]=command[len];
                    index++;
                }
                else{
                    printf("USAGE : please select 1~8 simulator\n");
                    exit(0);
                }
            }
            else{
                simulator_num[index]=command[len];
                index++;
            }
            
        }
        else if(command[len]!=' '){
            printf("USAGE : please select 1~8 simulator\n");
            exit(0);
        }
        len++;
    }
    
    if(index==0){
        printf("USAGE : please select simulator\n");
        exit(0);
    }
    
    for(int i=0;i<=index;i++){
        if(simulator_num[i]=='8' && index>1){
            printf("USAGE : (8) should only be selected by itslef\n");
            exit(0);
        }
    }
    
    if(index>0){
        if(simulator_num[0]==simulator_num[1]){
            printf("USAGE : duplicated number is not allowed\n");
            exit(0);
        }
    }
    if(index>1){
        if(simulator_num[0]==simulator_num[2]){
            printf("USAGE : duplicated number is not allowed\n");
            exit(0);
        }
        else if(simulator_num[1]==simulator_num[2]){
            printf("USAGE : duplicated number is not allowed\n");
            exit(0);
        }
    }
    
    printf("\nEnter number of page frame (3~10)\n>");
    scanf("%d", &FRAME_SIZE);
    if(FRAME_SIZE<3 || FRAME_SIZE>10){
        printf("USAGE : number of page frame should be between 3 and 10\n");
        exit(0);
    }
    
    int input_way=0;
    printf("\nSelect how to input data\n");
    printf("(1) Randomly  (2) File\n>");
    scanf("%d", &input_way);
    if(input_way<1 || input_way>2){
        printf("USAGE : selecet 1 way or 2 way\n");
        exit(0);
    }
    
    int* ref;
    if(input_way==1)
        ref = get_random_input();
    else
        ref = get_file_input();
    
    for(int i=0;i<=index;i++){
        switch (simulator_num[i]) {
            case '1':
                //OPTIMAL(ref);
                continue;
            case '2':
                FIFO(ref);
                continue;
            case '3':
                LIFO(ref);
                continue;
            case '4':
                LRU(ref);
                continue;
            case '5':
                LFU(ref);
                continue;
            case '6':
                //SC(ref);
                continue;
            case '7':
                //ESC(ref, esc_bit);
                continue;
            case '8':
                //OPTIMAL(ref);
                FIFO(ref);
                LIFO(ref);
                LRU(ref);
                LFU(ref);
                //SC(ref);
                //ESC(ref, esc_bit);
                break;
        }
    }
}
