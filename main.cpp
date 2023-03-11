#include <iostream>
#include "Leitura.h"
#include <string>
#include <vector>
#include "ACG.h"
#include <time.h>
#include <stdio.h>

using namespace std;

void menuParte1(int escolha, Grafo *grafo){
        switch(escolha){
            case 1:
            {
                Grafo *grafo_uniao = new Grafo(grafo->getDirecionado(),grafo->getPesoAresta());
                cout << "Digite o arquivo que esta o grafo que deseja unir ao atual:" << endl;
                string nome_arquivo;
                cin >> nome_arquivo;
                ///Leitura l2;    
                //l2.leitura(nome_arquivo,grafo_uniao);
                grafo_uniao->leitura(nome_arquivo);
                grafo->uniao(grafo_uniao);
                break;
            }
            case 2:
            {
                Grafo *grafo_intersecao = new Grafo(grafo->getDirecionado(),grafo->getPesoAresta());
                cout << "Digite o arquivo que esta o grafo que deseja obter a intersecao ao atual:" << endl;
                string nome_arquivo;
                cin >> nome_arquivo;
                //Leitura l2;    
                //l2.leitura(nome_arquivo,grafo_intersecao);
                grafo_intersecao->leitura(nome_arquivo);
                grafo->intersecao(grafo_intersecao);
                break;
            }
            case 3:
            {
                Grafo *grafo_diferenca = new Grafo(grafo->getDirecionado(),grafo->getPesoAresta());
                cout << "Digite o arquivo que esta o grafo que deseja obter a diferenca ao atual:" << endl;
                string nome_arquivo;
                cin >> nome_arquivo;
                //Leitura l2;    
                //l2.leitura(nome_arquivo,grafo_diferenca);
                grafo_diferenca->leitura(nome_arquivo);
                grafo->diferenca(grafo_diferenca);
                break;
            }
            case 4:
            {
                grafo->imprimir();
                break;
            }
            default:
            {
                cout << endl;
            }
        }
    }

void menuParte2(int escolha, Grafo *grafo){
        clock_t tempoInicial;
        clock_t tempoFinal;

        switch(escolha){
            case 1:
            {   
                ACG *acg = new ACG(grafo);
                tempoInicial = clock();
                cout << "Tempo Inicial: " << tempoInicial << endl;
                acg->encontraSubconjuntoDomPond();
                tempoFinal = clock();
                acg->imprimeSolucao();
                cout << "Tempo Final: " << tempoFinal << endl;
                cout << "Tempo de execução do Algoritmo: " << (tempoFinal - tempoInicial) << endl;
                break;
            }
            case 2:
            {
                ACG *acg = new ACG(grafo);
                tempoInicial = clock();
                float alfa[3] = {0.15, 0.3, 0.5};
                // for(int a = 0; a < 3; a++) {
                    // acg->limparGrafo();
                    acg->encontraSubconjuntoDomPondRandomizado(0.15);
                    //acg->imprimeSolucao();
                // }
                tempoFinal = clock();
                cout << "Tempo de execução do Algoritmo: " << (tempoFinal - tempoInicial) << endl;
                break;
            }
            default:
            {
                cout << "RODAR O TERCEIRO ALGORITMO" << endl;
                break;
            }
        }
    }

int main (int argc, char const *argv[]){

    cout << argc <<endl;

    if (argc == 6){
        cout << "PRIMEIRA PARTE DO TRABALHO" << endl;
        Grafo *grafo = new Grafo(atoi(argv[3]),atoi(argv[4]));
        //Leitura l1;
        //l1.leitura(argv[1],grafo);
        grafo->leitura(argv[1]);
        int escolha = -1;
        while(escolha != 0){
            cout << "----- MENU -----" << endl;
            cout << "Para obter a uniao de dois grafos digite 1" << endl;
            cout << "Para obter a intersecao de dois grafos digite 2" << endl;
            cout << "Para obter a diferenca entre dois grafos digite 3" << endl;
            cout << "Rede Pert digite 4" << endl;
            cout << "Para sair digite 0" << endl;
            cin >> escolha;
            menuParte1(escolha,grafo);
        }
    }
    else if (argc == 3){
        cout << "SEGUNDA PARTE DO TRABALHO" << endl;
        Grafo *grafo = new Grafo(true,false);
        //Leitura l1;
        //l1.leituraParte2(argv[1],grafo);
        grafo->leituraParte2(argv[1]);
        int escolha = -1;
        while(escolha != 0){
            cout << "----- MENU -----" << endl;
            cout << "Para obter o Algoritmo Construtivo Guloso 1" << endl;
            cout << "Para obter o Algoritmo Guloso Randomizado Adaptavivo 2" << endl;
            cout << "Para obter o Algorirtmo Guloso Randomizado Reativo 3" << endl;
            cout << "Para imprimir o grafo digite 4" << endl;
            cout << "Para sair digite 0" << endl;
            cin >> escolha;
            if(escolha!=0){
                if(escolha == 1 || escolha == 2 || escolha == 3)
                    menuParte2(escolha,grafo);
                else if(escolha == 4)
                    grafo->imprimir();
                else
                    cout << "Opção inválida, tente novamente." << endl;
            }                
        }
    }
    else{
        cout << "ERRO NA ENTRADA" << endl;  
    }

    return 0;
}