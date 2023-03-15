/// TAD Algoritmo Construtivo Guloso (ACG)

#include "No.h"
#include <iostream>
#include <iterator>
#include "ACG.h"
#include <list>
#include <algorithm>
#include <cmath>
#include <random>

using namespace std;

ACG::ACG(Grafo *graph)
{
    this->grafoNaoDirecionado = graph;
}
ACG::~ACG()
{
    this->grafoNaoDirecionado = nullptr;
    this->limparGrafo();
}

void ACG::limparGrafo()
{
    this->conectadosNaSolucao.clear();
    this->subconjuntoDomPond.clear();
}

bool ACG::verificaFimDaSolucao()
{
    int quantidadeDeNos = this->grafoNaoDirecionado->getQuantidadeNos();
    bool fim = (this->conectadosNaSolucao.size() == quantidadeDeNos);
    // cout << "quantidadeDeNos: " << quantidadeDeNos << endl;
    // cout << "conectadosNaSolucao.size(): " << this->conectadosNaSolucao.size() << endl;

    return fim;
}

bool ACG::verificaConexao(No *e)
{
    list<No *>::iterator it;
    for (it = this->conectadosNaSolucao.begin(); it != this->conectadosNaSolucao.end(); it++)
    {
        if ((*it)->getId() == e->getId())
        {
            return true;
        }
    }
    return false;
}

void ACG::atualizaHeuristica(list <No *> listaNosAdjacentes)
{   
    int heuristica;
    for (list<No*>::iterator it = listaNosAdjacentes.begin(); it != listaNosAdjacentes.end(); it++)
    {   
        heuristica = (*it)->getHeuristica() - 1;
        (*it)->setHeuristica(heuristica);
    }
}

void ACG::encontraSubconjuntoDomPond()
{   
    // lista de todos os nós do grafo
    list <No *> listaNos;

    // Preenche o vetor dos nós e inicializa as heurísticas
    int i = 0;

    for (No *aux = this->grafoNaoDirecionado->getPrimeiro(); aux != nullptr; aux = aux->getProx())
    {   
        if(aux->getGrau()== 0){
            this->subconjuntoDomPond.push_back(aux);
            if(!verificaConexao(aux))
                this->conectadosNaSolucao.push_back(aux);    
        }

        else{

            listaNos.push_back(aux);
            float grau = aux->getGrau();
            float peso = aux->getPeso();
            listaNos.back()->setHeuristica(grau/peso);
            i++;
        }
    }

    ///////ORDENAR OS NÓS DE ACORDO COM A HEURÍSTICA
    listaNos.sort([](const No* no1, const No* no2) { return no1->heur > no2->heur; });

    while (!verificaFimDaSolucao()){

        No* melhorEscolha = listaNos.front();

        // pegar o primeiro nó da lista dos ordenados
        // colocar na solução              
        this->subconjuntoDomPond.push_back(melhorEscolha);
        if(!verificaConexao(melhorEscolha))
            this->conectadosNaSolucao.push_back(melhorEscolha);

        // colocar ele e os adjacentes na lista de conectados na solução
        list <No*> nosAdjacentesAoVertice = this->grafoNaoDirecionado->encontraNosAdjacentes(melhorEscolha);
        for (list<No*>::iterator it = nosAdjacentesAoVertice.begin(); it != nosAdjacentesAoVertice.end(); it++)
        {   
            if(!verificaConexao(*it))
                this->conectadosNaSolucao.push_back(*it);
        }

        // atualizar a heuristica dos nós adjacentes a ele
        this->atualizaHeuristica(nosAdjacentesAoVertice);
        
        // remover ele da lista dos nós
        listaNos.pop_front();        

        // reordenar os nós pelo valor da heuristica
        listaNos.sort([](const No* no1, const No* no2) { return no1->heur > no2->heur; });
    }
    
}

void ACG::encontraSubconjuntoDomPondRandomizado(float alfa)
{
    //CONFIGURAÇÂO PARA GERAR VALOR ALEATÓRIO
    std::random_device rd;
    std::mt19937 gen(rd());

   // lista de todos os nós do grafo
    list <No *> listaNos;

    // Preenche o vetor dos nós e inicializa as heurísticas
    int i = 0;
    for (No *aux = this->grafoNaoDirecionado->getPrimeiro(); aux != nullptr; aux = aux->getProx())
    {   
        if(aux->getGrau()== 0){
            this->subconjuntoDomPond.push_back(aux);
            if(!verificaConexao(aux))
                this->conectadosNaSolucao.push_back(aux);    
        }

        else{

            listaNos.push_back(aux);
            float grau = aux->getGrau();
            float peso = aux->getPeso();
            listaNos.back()->setHeuristica(grau/peso);
            i++;
        }
    }

    ///////ORDENAR OS NÓS DE ACORDO COM A HEURÍSTICA
    listaNos.sort([](const No* no1, const No* no2) { return no1->heur > no2->heur; });

    while (!verificaFimDaSolucao()){

        //PEGAR UM NÚMERO ALEATÓRIO ENTRE OS alfa primeiros da lista
        float espacoEscolhaNo = alfa * listaNos.size();
        std::uniform_int_distribution<> distrib(0, espacoEscolhaNo);
        // Gera um número aleatório
        int aleatorio = distrib(gen);

        auto iterator = listaNos.begin();
        advance(iterator, aleatorio);
        No* melhorEscolha = *iterator;

        // pegar o primeiro nó da lista dos ordenados
        // colocar na solução              
        this->subconjuntoDomPond.push_back(melhorEscolha);
        if(!verificaConexao(melhorEscolha))
            this->conectadosNaSolucao.push_back(melhorEscolha);

        // colocar ele e os adjacentes na lista de conectados na solução
        list <No*> nosAdjacentesAoVertice = this->grafoNaoDirecionado->encontraNosAdjacentes(melhorEscolha);
        for (list<No*>::iterator it = nosAdjacentesAoVertice.begin(); it != nosAdjacentesAoVertice.end(); it++)
        {   
            if(!verificaConexao(*it))
                this->conectadosNaSolucao.push_back(*it);
        }

        // atualizar a heuristica dos nós adjacentes a ele
        this->atualizaHeuristica(nosAdjacentesAoVertice);
        
        // remover ele da lista dos nós
        listaNos.erase(iterator);   

        // reordenar os nós pelo valor da heuristica
        listaNos.sort([](const No* no1, const No* no2) { return no1->heur > no2->heur; });
    }
    
}

int ACG::encontraNoComId(vector<No *> vet, int id)
{

    for (int i = 0; i < vet.size(); i++)
    {
        if (vet.at(i)->getId() == id)
            return i;
    }

    return -1;
}
void ACG::imprimeSolucao()
{
    std::cout << "\nImprime a solucao:" << endl;
    list<No *>::iterator it;

    for (it = this->subconjuntoDomPond.begin(); it != this->subconjuntoDomPond.end(); it++)
    {
        std::cout << (*it)->getId() << " ";
    }
}