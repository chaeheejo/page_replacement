//
//  ESC.c
//  Enhanced Second Chance
//  page_replacement
//
//  Created by chaehee on 2022/11/16.
//

#include "ESC.h"

extern int REF_SIZE;
extern int FRAME_SIZE;

void ESC(int* ref, int output_flag, FILE* fp){
    printf("\n==ESC simulation start==\n\n");
    
    if(output_flag)
        fprintf(fp, "\n\n==ESC simulation start==\n\n");
    
    int page_fault=0;
    
    int** frame = (int**) calloc(FRAME_SIZE, sizeof(int*));
    for(int i=0;i<FRAME_SIZE;i++){
        frame[i] = (int*) calloc(3, sizeof(int));
    }
    
    int flag=0, frame_size=0;
    int cur=0, hit_index=0;
    
    int i=0, ref_cur=0, bit_cur=0;
    while(i<REF_SIZE*2){
        flag=0;
        ref_cur = ref[i];
        bit_cur = ref[++i];
        if((hit_index=is_exist_dimension(frame, ref_cur))==NOTFOUND){
            if(frame_size<FRAME_SIZE){
                frame[frame_size][0] = ref_cur;
                frame_size++;
                
                if(bit_cur==0){
                    frame[cur][1] = 1;
                }
                else{
                    frame[cur][2] = 1;
                }
                flag=1;
                page_fault++;
                cur = (cur+1)%FRAME_SIZE;
            }
            else{
                int low_page = lowest_priority(frame, cur);
                frame[low_page][0] = ref_cur;
                frame[low_page][1] = 0;
                frame[low_page][2] = 0;
                
                if(bit_cur==0){
                    frame[low_page][1] = 1;
                }
                else{
                    frame[low_page][2] = 1;
                }
                cur = (low_page+1)%FRAME_SIZE;
                flag=1;
                page_fault++;
            }
        }
        else{  
            if(bit_cur==0){
                frame[hit_index][1] = 1;
            }
            else{
                frame[hit_index][2] = 1;
            }
        }
        i++;
        
        printf("#%-5d page : %-3d  ", i/2, ref_cur);
        
        if(output_flag)
            fprintf(fp, "#%-5d page : %-3d  ", i/2, ref[i]);
        
        
        if(bit_cur==0){
            printf("bit : R");
            
            if(output_flag)
                fprintf(fp, "bit : R");
        }
        else{
            printf("bit : W");
            
            if(output_flag)
                fprintf(fp, "bit : W");
        }
        
        printf("   frame : ");
        
        if(output_flag)
            fprintf(fp, "   frame : ");
            
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
    printf("==ESC simulation end==\n\n\n");
    
    if(output_flag){
        fprintf(fp, "\nTotal number of page fault %d\n", page_fault);
        fprintf(fp, "==ESC simulation end==\n\n\n");
    }
}
