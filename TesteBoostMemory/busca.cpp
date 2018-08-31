#include "busca.hpp"


Position pos_make(int x, int y)
{
    Position pos;
    pos.x = x;
    pos.y = y;
    return pos;
}

void print_labirinto(int lab[TAMANHO_LAB][TAMANHO_LAB])
{
    int i,l;
    for(i = 0; i < TAMANHO_LAB; i++)
    {
        for(l = 0; l < TAMANHO_LAB; l++)
        {
            printf("%d..", lab[i][l]);
        }
        printf("\n");
    }
}









int* busca_largura (int labirinto[TAMANHO_LAB][TAMANHO_LAB], int* caminho, Position inico, Position fim){

    caminho[0] = 5;

    return caminho;
}




