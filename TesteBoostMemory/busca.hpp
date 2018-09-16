#ifndef BUSCA_HPP_INCLUDED
#define BUSCA_HPP_INCLUDED

#include <stdio.h>
#include <math.h>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

#define TAMANHO_LAB 10

typedef struct pos
{
    int x, y, walked, heuristic;
    struct pos *pai;
} Position;

typedef struct robot{
	Position* in;
	Position* olhando;
}Robot;

Position* busca_largura (int labirinto[TAMANHO_LAB][TAMANHO_LAB], Position *inicio, Position *fim, int *tam_caminho);
Position* busca_aestrela (int labirinto[TAMANHO_LAB][TAMANHO_LAB], Position *inicio, Position *fim, int *tam_caminho);
int get_heuristica (Position *pos, Position *fim);
Position* get_menor_heuristica (vector<Position*> &lista, Position *pos);
int remove_pos (vector<Position*> &lista);
Position* pos_make(int x, int y);
int* get_moves(Position* caminho, int tam_caminho);
void print_labirinto(int lab[TAMANHO_LAB][TAMANHO_LAB]);
Position** get_vizinhos(Position *pos, int labirinto[TAMANHO_LAB][TAMANHO_LAB]);

#endif // BUSCA_HPP_INCLUDED
