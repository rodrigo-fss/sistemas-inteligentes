//TesteBoostMemory

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
//    while(!opened)
//    {
//        try
//        {
//            abrindo_memoria = new managed_shared_memory (open_only, NOME_DA_MEMORIA2);
//            opened = true;
//        }
//        catch(...)
//        {
//            std::cout<<"erro ao abrir memoria 2"<<std::endl;
//            sleep(1);
//        }
//    }
    std::cout<<"Abriu a memoria compartilhada!!!" << endl;
    cout.flush();

    /**============================================**/
    int labirinto[TAMANHO_LAB][TAMANHO_LAB];
    Position *caminho, *pos_init, *pos_end;

    pos_init = pos_make(0,0);
    pos_end = pos_make(3,9);

    int i,l;
    for(i = 0; i < TAMANHO_LAB; i++)
    {
        for(l = 0; l < TAMANHO_LAB; l++)
        {
            labirinto[i][l] = 0;
        }
    }

    labirinto[0][4] = 1;
    labirinto[1][4] = 1;
    labirinto[2][4] = 1;
    labirinto[3][4] = 1;
    labirinto[4][4] = 1;
    labirinto[5][4] = 1;


    print_labirinto(labirinto);
    cout.flush();
    printf("chamei busca\n");
    caminho = busca_largura(labirinto, pos_init, pos_end);
    printf("sai busca\n");

    for(i = 0; i < 18; i++)
    {
        printf("X: %d, Y: %d\n",caminho[i].x,caminho[i].y);
    }


    print_labirinto(labirinto);
    cout.flush();


    //delete(caminho);
    /**==========================================================**/


    /**============================================**/


    /**============================================**/


    printf("começando controle\n");


    /****/
    int qnt_caminho = 5;cout.flush();
    int caminho_atual = 0;
    /****/

    int controle = 0;
    while(controle <= 2)
    {
        pair<int*, managed_shared_memory::size_type> comando2;
        comando2 = abrindo_memoria->find<int>(NOME_DO_INT_NA_MEMORIA2);


        cout << "8)Frente" << endl << "6)Direita " << endl << "4)Esquerda" << endl;
//        cin >> (*comando1);

        /****/
//        printf("\n Executando comando: %d .\n", caminho[caminho_atual]);
//        (*comando1) << caminho[caminho_atual];
//        *comando1 = caminho[caminho_atual];
//        std::cout << *comando1 << endl;
//        caminho[caminho_atual] >> *comando1;
//        std::cout << *comando1 << endl;
//        caminho_atual++;
//        /****/

        shared_memory_object::remove(NOME_DA_MEMORIA);
        sleep(5);
    }

    std::cout<<"Terminou!!" << endl;
    cout.flush();
    return 0;
}
