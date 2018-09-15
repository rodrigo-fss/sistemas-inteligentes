#include "busca.hpp"


Position* pos_make(int x, int y)
{
    Position *pos = new Position();
    pos->x = x;
    pos->y = y;
    return pos;
}

void print_labirinto(int lab[TAMANHO_LAB][TAMANHO_LAB])
{
    int i,l;
    for(i = 0; i < TAMANHO_LAB; i++)
    {
        printf("x:%d:   ",i);
        for(l = 0; l < TAMANHO_LAB; l++)
        {
            printf("%d..", lab[i][l]);
        }
        printf("\n");
    }
}

Position** get_vizinhos(Position *pos, int labirinto[TAMANHO_LAB][TAMANHO_LAB])
{
    Position **vizinhos;
    vizinhos = new Position*[4];
    // POS:
    // [0] = FRENTE Y+1
    // [1] = DIREITA X+1
    // [2] = TRÁS Y-1
    // [3] = ESQUERDA X-1
    if(pos->y + 1 < TAMANHO_LAB)
    {
        vizinhos[0] = pos_make(pos->x, pos->y + 1);
    }else
    {
        vizinhos[0] = pos_make(-1,-1);
    }
    if(pos->x + 1 < TAMANHO_LAB)
    {
        vizinhos[1] = pos_make(pos->x + 1, pos->y);
    }else
    {
        vizinhos[1] = pos_make(-1,-1);
    }
    if(pos->y - 1 >= 0)
    {
        vizinhos[2] = pos_make(pos->x, pos->y - 1);
    }else
    {
        vizinhos[2] = pos_make(-1,-1);
    }
    if(pos->x - 1 >= 0)
    {
        vizinhos[3] = pos_make(pos->x - 1, pos->y);
    }
    else
    {
        vizinhos[3] = pos_make(-1,-1);
    }

    return vizinhos;
}


Position* busca_largura (int labirinto[TAMANHO_LAB][TAMANHO_LAB], Position *inicio, Position *fim, int *tam_caminho)
{
    Position **vizinhos;
    Position *caminho, *atual = inicio;
std:
    queue<Position*> fila;
    stack<Position> pilha;

    labirinto[atual->x][atual->y] = 7;
    atual->pai = NULL;
    fila.push(atual);

    while(!fila.empty())
    {
        //pegar o próximo
        atual = fila.front();
        //visitar os vizinhos
        vizinhos = get_vizinhos(atual, labirinto);
        int i;

        for(i=0; i<4; i++)
        {
            if(vizinhos[i]->x == -1)
            {
                continue;
            }else if(labirinto[vizinhos[i]->x][vizinhos[i]->y] != 7 && labirinto[vizinhos[i]->x][vizinhos[i]->y] != 1) //se não está marcado;
            {
                labirinto[vizinhos[i]->x][vizinhos[i]->y] = 7; /**visita vizinho**/
                vizinhos[i]->pai = atual;
                fila.push(vizinhos[i]);
                if(vizinhos[i]->x == fim->x && vizinhos[i]->y == fim->y)
                {
                    Position *voltando = vizinhos[i];
                    //faz caminho de volta
                    while(voltando->pai != NULL)
                    {
                        pilha.push(*voltando);
                        voltando = voltando->pai;
                    }
                    //insere caminho em ordem
                    caminho = new Position[pilha.size()];
                    *tam_caminho = (int)pilha.size();
                    int h = 0;
                    while(!pilha.empty())
                    {
                        caminho[h] = pilha.top();
                        h++;
                        pilha.pop();
                    }
                    return caminho;
                }
            }
        }
        fila.pop();
    }
    return caminho;
}

Position* busca_aestrela (int labirinto[TAMANHO_LAB][TAMANHO_LAB], Position *inicio, Position *fim)
{
    Position **vizinhos;
    Position *caminho, *atual = inicio;




/**
    std:
    queue<Position*> fila;
    stack<Position> pilha;

    labirinto[atual->x][atual->y] = 7;
    atual->pai = NULL;
    fila.push(atual);

    while(!fila.empty())
    {
        //pegar o próximo
        atual = fila.front();
        //visitar os vizinhos
        vizinhos = get_vizinhos(atual, labirinto);
        int i;

        for(i=0; i<4; i++)
        {
            if(vizinhos[i]->x == -1)
            {
                continue;
            }else if(labirinto[vizinhos[i]->x][vizinhos[i]->y] != 7 && labirinto[vizinhos[i]->x][vizinhos[i]->y] != 1) //se não está marcado;
            {
                labirinto[vizinhos[i]->x][vizinhos[i]->y] = 7;
                vizinhos[i]->pai = atual;
                fila.push(vizinhos[i]);
                if(vizinhos[i]->x == fim->x && vizinhos[i]->y == fim->y)
                {
                    Position *voltando = vizinhos[i];
                    //faz caminho de volta
                    while(voltando->pai != NULL)
                    {
                        pilha.push(*voltando);
                        voltando = voltando->pai;
                    }
                    //insere caminho em ordem
                    caminho = new Position[pilha.size()];
                    int h = 0;
                    while(!pilha.empty())
                    {
                        caminho[h] = pilha.top();
                        h++;
                        pilha.pop();
                    }
                    return caminho;
                }
            }
        }
        fila.pop();
    }
    return caminho;**/
}


