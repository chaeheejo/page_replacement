//
//  SC.c
//  Second Chance
//  page_replacement
//
//  Created by chaehee on 2022/11/16.
//

#include "SC.h"

extern int REF_SIZE;
extern int FRAME_SIZE;

void SC(int* ref, int output_flag, FILE* fp){
    printf("\n\n==SC simulation start==\n\n");
    
    if(output_flag)
        fprintf(fp, "\n\n==SC simulation start==\n\n");
    
    int page_fault=0;
    
    
    int** frame = (int**) calloc(FRAME_SIZE, sizeof(int*));
    for(int i=0;i<FRAME_SIZE;i++){
        frame[i] = (int*) calloc(2, sizeof(int));
    }
    
    int flag=0, frame_size=0;
    int cur=0, hit_index=0;
    
    for(int i=0;i<REF_SIZE;i++){
        flag=0;
        
        if((hit_index=is_exist_dimension(frame, ref[i]))==NOTFOUND){
            if(frame_size<FRAME_SIZE){
                frame[frame_size][0] = ref[i];
                frame_size++;
                cur = (cur+1)%FRAME_SIZE;
                
                page_fault++;
                flag=1;
            }
            else{
                while(frame[cur][1]==1){
                    frame[cur][1]=0;
                    cur = (cur+1)%FRAME_SIZE;
                }
                frame[cur][0]=ref[i];
                cur = (cur+1)%FRAME_SIZE;
                
                page_fault++;
                flag=1;
            }
        }
        else{
            frame[hit_index][1]=1;
        }
        
        printf("#%-5d page : %-3d   frame :", i+1, ref[i]);
        
        if(output_flag)
            fprintf(fp, "#%-5d page : %-3d   frame :", i+1, ref[i]);
        
        print_frame_dimension(frame, fp, output_flag);
        
        if(flag){
            printf("%5c\n", 'F');
            
            if(output_flag)
                fprintf(fp, "%5c\n", 'F');
        }
        else{
            printf("%5c\n", ' ');
            
            if(output_flag)
                fprintf(fp, "%5c\n", ' ');
        }
    }
    
    for(int i=0;i<FRAME_SIZE;i++){
        free(frame[i]);
    }
    
    free(frame);
    
    printf("\nTotal number of page fault %d\n", page_fault);
    printf("==SC simulation end==\n\n\n");
    
    if(output_flag){
        fprintf(fp, "\nTotal number of page fault %d\n", page_fault);
        fprintf(fp, "==SC simulation end==\n\n\n");
    }
}
