#ifndef BUSCA_HPP_INCLUDED
#define BUSCA_HPP_INCLUDED

#include <stdio.h>
using namespace std;

#define TAMANHO_LAB 10

typedef struct pos
{
    int x, y, flag;
}Position;

int* busca_largura (int labirinto[TAMANHO_LAB][TAMANHO_LAB], int* caminho, Position inicio, Position fim);
Position pos_make(int x, int y);
void print_labirinto(int lab[TAMANHO_LAB][TAMANHO_LAB]);

#endif // BUSCA_HPP_INCLUDED
