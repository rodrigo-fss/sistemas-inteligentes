#ifndef BUSCA_HPP_INCLUDED
#define BUSCA_HPP_INCLUDED

#include <stdio.h>
#include <queue>
#include <stack>
using namespace std;

#define TAMANHO_LAB 10

typedef struct pos
{
    int x, y, flag;
    struct pos *pai;
}Position;

Position* busca_largura (int labirinto[TAMANHO_LAB][TAMANHO_LAB], Position *inicio, Position *fim);
Position* busca_aestrela (int labirinto[TAMANHO_LAB][TAMANHO_LAB], Position inicio, Position fim);
Position* pos_make(int x, int y);
void print_labirinto(int lab[TAMANHO_LAB][TAMANHO_LAB]);
Position** get_vizinhos(Position *pos, int labirinto[TAMANHO_LAB][TAMANHO_LAB]);

#endif // BUSCA_HPP_INCLUDED
