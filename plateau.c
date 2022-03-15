#include <stdio.h>

#define SIZE 22


int main(){
    int plateau[SIZE][SIZE];
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if((i==0) || (i==SIZE-1) || (j==0) || (j==SIZE-1)){
                plateau[i][j]=5;
            }
            else{
                plateau[i][j]=0;
            }
        }
    }
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            printf("%d ",plateau[i][j]);
        }
        printf("\n");
    }
    return 0;
}