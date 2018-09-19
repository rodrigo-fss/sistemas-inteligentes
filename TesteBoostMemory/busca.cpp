/**
==========================================================
||      UNIVERSIDADE TECNOLÓGICA FEDERAL DO PARANÁ      ||
||                  Curitiba, 2018/2                    ||
||                                                      ||
||      Eduardo Darrazão    RA: 1906399                 ||
||      Rodrigo Faria       RA:                         ||
||                                                      ||
||      Disciplina: Sistemas Inteligentes - CSI30-S73   ||
||      Professor:  João Alberto Fabro                  ||
==========================================================
**/

#include "busca.hpp"

//
//
//
Position* pos_make(int x, int y)
{
    Position *pos = new Position();
    pos->x = x;
    pos->y = y;
    return pos;
}

//
//
//
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

//
//
//
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
    }
    else
    {
        vizinhos[0] = pos_make(-1,-1);
    }
    if(pos->x + 1 < TAMANHO_LAB)
    {
        vizinhos[1] = pos_make(pos->x + 1, pos->y);
    }
    else
    {
        vizinhos[1] = pos_make(-1,-1);
    }
    if(pos->y - 1 >= 0)
    {
        vizinhos[2] = pos_make(pos->x, pos->y - 1);
    }
    else
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

//
//
//
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
            if(vizinhos[i]->x == -1
                    || labirinto[vizinhos[i]->x][vizinhos[i]->y] == 7
                    || labirinto[vizinhos[i]->x][vizinhos[i]->y] == 1)  //se for parede continue
            {
                continue;
            }

            //Atualiza informações e joga na fila
            labirinto[vizinhos[i]->x][vizinhos[i]->y] = 7; /**visita vizinho**/
            vizinhos[i]->pai = atual;
            fila.push(vizinhos[i]);

            //Verifica se é o objetivo
            if(vizinhos[i]->x == fim->x && vizinhos[i]->y == fim->y)
            {
                Position *voltando = vizinhos[i];
                //faz caminho de volta
                while(voltando->pai != NULL)
                {
                    pilha.push(*voltando);
                    voltando = voltando->pai;
                }
                pilha.push(*voltando);
                //insere caminho em ordem
                caminho = new Position[(int)pilha.size()];
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
        fila.pop();
    }
    return caminho;
}

//
//
//
int* get_moves(Position* caminho, int tam_caminho)
{
    int *movimentos, ind_movimentos = 0, xo, yo, ind_vizinhos, i, diferencaX, diferencaY;
    movimentos = new int[tam_caminho*3];
    Robot robo;

    robo.in = pos_make(caminho->x, caminho->y);
    robo.olhando = pos_make(caminho->x-1, caminho->y);

    for(i = 1; i < tam_caminho; i++)
    {
        ind_vizinhos = 0 ;
        while(caminho[i].x != robo.olhando->x || caminho[i].y != robo.olhando->y)
        {
            if(ind_vizinhos > 3)
            {
                printf("Caminho quebrado | ");
                break;
            }

            if(robo.in->x != robo.olhando->x)
            {
                if(robo.in->x < robo.olhando->x)
                {
                    robo.olhando->x--;
                    robo.olhando->y++;
                }
                else
                {
                    robo.olhando->x++;
                    robo.olhando->y--;
                }
            }
            else
            {
                if(robo.in->y < robo.olhando->y)
                {
                    robo.olhando->x--;
                    robo.olhando->y--;
                }
                else
                {
                    robo.olhando->x++;
                    robo.olhando->y++;
                }
            }

            ind_vizinhos++;
        }

        switch(ind_vizinhos){
            case 1:
                movimentos[ind_movimentos] = 4;
                ind_movimentos++;
                break;
            case 3:
                movimentos[ind_movimentos] = 6;
                ind_movimentos++;
                break;

        }
        diferencaX = robo.in->x - robo.olhando->x;
        diferencaY = robo.in->y - robo.olhando->y;

        robo.in->x = robo.olhando->x;
        robo.in->y = robo.olhando->y;

        robo.olhando->x -= diferencaX;
        robo.olhando->y -= diferencaY;

        movimentos[ind_movimentos] = 8;
        ind_movimentos++;


    }
    movimentos[ind_movimentos] = -1;
    return movimentos;
}


/**=====================
    FUNÇÕES REFERENTES
        A ESTRELA
=======================**/

//
//
//
int get_heuristica (Position *pos, Position *fim)
{
    return (int)sqrt(pow(fim->x - pos->x, 2) + pow(fim->y - pos->y, 2));
}

//
//
//
Position* get_melhor_heuristica (vector<Position*> &lista)
{
    Position *melhor = lista[0];
    int i;

    //acha o melhor
    for(i = 1; i < lista.size(); i++)
    {
        if(melhor->walked + melhor->heuristic > lista[i]->walked + lista[i]->heuristic)
        {
            melhor = lista[i];
        }
    }
    return melhor;
}

//
//
//
int remove_pos (vector<Position*> &lista, Position *pos)
{
    int i;
    for(i = 0; i < lista.size(); i++)
    {
        if(lista[i] == pos)
        {
            lista.erase(lista.begin()+i);
            return 1;
        }
    }
    return 0;
}

//
//
//
Position* busca_aestrela (int labirinto[TAMANHO_LAB][TAMANHO_LAB], Position *inicio, Position *fim, int *tam_caminho)
{
    Position **vizinhos;
    Position *caminho, *atual = inicio;
std:
    vector<Position*> aberta, fechada;
    stack<Position> pilha;

    atual->walked = 0;
    atual->heuristic = get_heuristica(atual,fim);
    atual->pai = NULL;
    aberta.push_back(atual);
    labirinto[atual->x][atual->y] = 7;

    while(!aberta.empty())
    {
        //pegar o melhor de aberta
        atual = get_melhor_heuristica(aberta);
        //retirá-lo da aberta
        if(!remove_pos(aberta, atual))
        {
            printf("erro removendo nó.\n");
            return NULL;
        }
        //adiciona em fechada
        fechada.push_back(atual);



        //confere se é o objetivo
        if(atual->x == fim->x && atual->y == fim->y)
        {
            //faz caminho de volta
            while(atual->pai != NULL)
            {
                pilha.push(*atual);
                atual = atual->pai;
            }
            pilha.push(*atual);
            //insere caminho em ordem
            caminho = new Position[(int)pilha.size()];
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



        //Se nao for, descobre vizinhos
        vizinhos = get_vizinhos(atual, labirinto);
        int i;
        for(i = 0; i < 4; i++)
        {
            if(vizinhos[i]->x == -1 || labirinto[vizinhos[i]->x][vizinhos[i]->y] == 1 || labirinto[vizinhos[i]->x][vizinhos[i]->y] == 7) //se for parede continue
            {
                continue;
            }
            labirinto[vizinhos[i]->x][vizinhos[i]->y] = 7; /**visita vizinho**/
            vizinhos[i]->pai = atual;
            vizinhos[i]->walked = atual->walked + 1; //aumenta o "G"
            vizinhos[i]->heuristic = get_heuristica(vizinhos[i], fim); //aumenta o "H'"

            /**
                http://www.dainf.ct.utfpr.edu.br/~fabro/IA_I/busca/Algoritmo_A_Estrela.pdf

                teria ainda que analisar antes de jogar na aberta se ela já está na aberta ou fechada,
                para assim quebrar ciclos... explicado nesse link
            **/

            aberta.push_back(vizinhos[i]);
        }
    }
    return caminho;
}
