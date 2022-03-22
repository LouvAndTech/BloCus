#include "plateau.c"

#define SIZE_PLAT 22

/**
 * @brief Main
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    int tab[SIZE_PLAT][SIZE_PLAT];
    plateau(tab,SIZE_PLAT);

    for(int i=0; i<SIZE_PLAT; i++){
        for(int j=0; j<SIZE_PLAT; j++){
            printf("%d ",tab[i][j]);
        }
        printf("\n");
    }
    return 0;
}
