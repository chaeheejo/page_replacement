//
//  Optimal.c
//  page_replacement
//
//  Created by chaehee on 2022/11/16.
//

#include "Optimal.h"

extern int REF_SIZE;
extern int FRAME_SIZE;

void OPTIMAL(int* ref, int output_flag, FILE* fp){
    printf("\n\n==OPTIMAL simulation start==\n\n");
    
    if(output_flag)
        fprintf(fp, "\n\n==OPTIMAL simulation start==\n\n");
    
    int page_fault=0;
    
    int* frame = (int*) calloc(FRAME_SIZE, sizeof(int));
    
    int frame_size=0, flag=0;
    
    for(int i=0;i<REF_SIZE;i++){
        flag=0;
        
        if(is_exist(frame,ref[i])==NOTFOUND){
            if(frame_size<FRAME_SIZE){
                frame[frame_size] = ref[i];
                frame_size++;
                
                page_fault++;
                flag=1;
            }
            else{
                int long_dist=0, long_index=0;
                for(int j=0;j<FRAME_SIZE;j++){
                    int dist =how_far(ref, i, frame[j]);
                    
                    if(long_dist<dist){
                        long_dist = dist;
                        long_index = j;
                    }
                }
                
                frame[long_index] = ref[i];
                page_fault++;
                flag=1;
            }
        }
        
        printf("#%-5d page : %-3d   frame :", i+1, ref[i]);
        
        if(output_flag)
            fprintf(fp, "#%-5d page : %-3d   frame :", i+1, ref[i]);
        
        print_frame(frame, fp, output_flag);
        
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
    
    free(frame);
    
    printf("\nTotal number of page fault %d\n", page_fault);
    printf("==OPTIMAL simulation end==\n\n\n");
    
    if(output_flag){
        fprintf(fp, "\nTotal number of page fault %d\n", page_fault);
        fprintf(fp, "==OPTIMAL simulation end==\n\n\n");
    }
}
