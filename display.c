//
//  display.c
//  page_replacement
//
//  Created by chaehee on 2022/11/15.
//

#include "display.h"

extern int STREAM_SIZE;
extern int FRAME_SIZE;

void display(void){
    while(1){
        char command[10];
        char simulator_num[3]={'0','0','0'};
        printf("Select page replacement algorithm simulator (maximum 3 but (8) can only be selected by itself) \n");
        printf("(1) OPTIMAL  (2) FIFO  (3) LIFO  (4) LRU  (5) LFU  (6) SC  (7) ESC  (8) ALL\n>");
        
        scanf(" %[^\n]", command);
        
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
        
        int esc_flag=0;
        for(int i=0;i<=index;i++){
            if(simulator_num[i]=='8' || simulator_num[i]=='7'){
                esc_flag=1;
                break;
            }
        }
        
        int* ref=0;
        int* esc_ref=0;
        if(esc_flag==0){
            if(input_way==1)
                ref = get_random_input(0);
            else
                ref = get_file_input(0);
        }
        else{
            if(input_way==1){
                esc_ref = get_random_input(1);
                ref = convert_esc_to_normal(esc_ref);
            }
            else{
                esc_ref = get_file_input(1);
                ref = convert_esc_to_normal(esc_ref);
            }
        }
        
        char ans;
        int output_way=0;
        while(1){
            printf("\nDo you want to save the output to output.txt? (Y/N)\n");
            scanf(" %c", &ans);
            if(ans=='N'){
                output_way=1;
                break;
            }
            else if(ans=='Y')
                break;
            else{
                printf("USAGE : selecet Y or N\n");
            }
        }
        
        FILE* fp=0;
        if(output_way==1){
            fp = fopen("output.txt", "w");
            
            if(fp==NULL){
                printf("ERROR : create file output.txt\n");
                exit(0);
            }
        }
        
        for(int i=0;i<=index;i++){
            switch (simulator_num[i]) {
                case '1':
                    OPTIMAL(ref);
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
                    SC(ref);
                    continue;
                case '7':
                    ESC(esc_ref);
                    continue;
                case '8':
                    OPTIMAL(ref);
                    FIFO(ref);
                    LIFO(ref);
                    LRU(ref);
                    LFU(ref);
                    SC(ref);
                    ESC(esc_ref);
                    break;
            }
        }
        
        char answer;
        int exit_flag=0;
        while(1){
            printf("Do you want to be continue the simulator? (Y/N)\n");
            scanf(" %c", &answer);
            if(answer=='N'){
                exit_flag=1;
                break;
            }
            else if(answer=='Y')
                break;
            else{
                printf("USAGE : selecet Y or N\n");
            }
        }
        
        if(exit_flag==1)
            exit(0);
        
        printf("\n\n");
        
        free(ref);
        free(esc_ref);
    }
}
