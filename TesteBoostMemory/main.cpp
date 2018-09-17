//TesteBoostMemory
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

#include <stdio.h>
#include <iostream>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/offset_ptr.hpp>

using namespace boost::interprocess;

using namespace std;
#define NOME_DA_MEMORIA "memoria"
#define NOME_DA_MEMORIA2 "memoria2"
#define TAMANHO_DA_MEMORIA 65536
#define NOME_DO_INT_NA_MEMORIA1 "comando1"
#define NOME_DO_INT_NA_MEMORIA2 "comando2"

//para usar kbhit
#include <sys/ioctl.h>
#include <termios.h>

#include "busca.hpp"

int main()
{
    /**
    ==================================================
    ||          Parâmetros para Labirinto           ||
    ==================================================
    **/
    int labirinto[TAMANHO_LAB][TAMANHO_LAB];
    Position *caminho, *pos_init, *pos_end;

    int tam_caminho, i, l, *movimentos;

    pos_init = pos_make(INICIO_X,INICIO_Y);
    pos_end = pos_make(FIM_X,FIM_Y);

    switch(TIPO_BUSCA)
    {
    case 1:
    {
        /**===================
        ||      LARGURA     ||
        ====================**/

        printf("\n============\n LARGURA\n============\n");

        for(i = 0; i < TAMANHO_LAB; i++)
        {
            for(l = 0; l < TAMANHO_LAB; l++)
            {
                labirinto[i][l] = 0;
            }
        }

        labirinto[5][4] = 1;
        labirinto[5][5] = 1;
        labirinto[5][6] = 1;
        labirinto[5][7] = 1;
        labirinto[5][8] = 1;
        labirinto[5][9] = 1;
        labirinto[pos_init->x][pos_init->y] = 2;
        labirinto[pos_end->x][pos_end->y] = 3;
        printf("Labirinto computado\n");
        print_labirinto(labirinto);
        cout.flush();

        caminho = busca_largura(labirinto, pos_init, pos_end, &tam_caminho);
        printf("Busca em Largura Concluida\n");

        movimentos = new int[tam_caminho*3];
        movimentos = get_moves(caminho, tam_caminho);
        printf("movimentos computados\nSendo:\n");

        for(i = 0; movimentos[i] != -1; i++)
        {
            printf("movimento: %d\n", movimentos[i]);
        }

        printf("tamanho do caminho é: %d\nSendo:\n", tam_caminho);
        for(i = 0; i < tam_caminho; i++)
        {
            printf("X: %d, Y: %d\n",caminho[i].x,caminho[i].y);
        }
        cout.flush();
        break;
    }
    case 2:
    {
        /**=====================
        ||      A ESTRELA     ||
        ======================**/

        printf("\n============\n A ESTRELA\n============\n");


        for(i = 0; i < TAMANHO_LAB; i++)
        {
            for(l = 0; l < TAMANHO_LAB; l++)
            {
                labirinto[i][l] = 0;
            }
        }

        labirinto[5][4] = 1;
        labirinto[5][5] = 1;
        labirinto[5][6] = 1;
        labirinto[5][7] = 1;
        labirinto[5][8] = 1;
        labirinto[5][9] = 1;
        labirinto[pos_init->x][pos_init->y] = 2;
        labirinto[pos_end->x][pos_end->y] = 3;
        printf("Labirinto computado\n");
        print_labirinto(labirinto);
        cout.flush();

        caminho = busca_aestrela(labirinto, pos_init, pos_end, &tam_caminho);
        printf("Busca A Estrela Concluída\n");

        movimentos = new int[tam_caminho*3];
        movimentos = get_moves(caminho, tam_caminho);
        printf("movimentos computados\nSendo:\n");

        for(i = 0; movimentos[i] != -1; i++)
        {
            printf("movimento: %d\n", movimentos[i]);
        }

        printf("tamanho do caminho é: %d\nSendo:\n", tam_caminho);
        for(i = 0; i < tam_caminho; i++)
        {
            printf("X: %d, Y: %d\n",caminho[i].x,caminho[i].y);
        }
        cout.flush();
        break;
    }
    }

    /**
    ==============================================
    ||          Integração com V-REP            ||
    ==============================================
    **/
    std::cout<<"Comecou!!!" << endl;
    cout.flush();
    shared_memory_object::remove(NOME_DA_MEMORIA);

    managed_shared_memory* dinamica;
    dinamica = new managed_shared_memory(open_or_create, NOME_DA_MEMORIA, TAMANHO_DA_MEMORIA);
    int* comando1;
    comando1 = dinamica->construct<int>(NOME_DO_INT_NA_MEMORIA1)();

    std::cout<<"Alocou!!!" << endl;
    cout.flush();

    //abrindo as variaveis da memoria
    //(parte que seria feita no outro programa)
    managed_shared_memory* abrindo_memoria;
    bool opened = false;
    while(!opened)
    {
        try
        {
            abrindo_memoria = new managed_shared_memory (open_only, NOME_DA_MEMORIA2);
            opened = true;
        }
        catch(...)
        {
            std::cout<<"erro ao abrir memoria 2"<<std::endl;
            sleep(1);
        }
    }
    std::cout<<"Abriu a memoria compartilhada!!!" << endl;
    cout.flush();

    printf("começando controle\n");
    int movimento_atual = 0;
    while(movimentos[movimento_atual] != -1)
    {
        pair<int*, managed_shared_memory::size_type> comando2;
        comando2 = abrindo_memoria->find<int>(NOME_DO_INT_NA_MEMORIA2);

        cout << "8)Frente" << endl << "6)Direita " << endl << "4)Esquerda" << endl;
//        cin >> (*comando1);

        printf("Executando movimento: %d\n",movimentos[movimento_atual]);
        *comando1 = movimentos[movimento_atual];
        movimento_atual++;

        shared_memory_object::remove(NOME_DA_MEMORIA);
        sleep(6);
    }
    printf("Destino alcançado com sucesso!\n");
    std::cout<<"Terminou!!" << endl;
    cout.flush();
    return 0;
}
