/// TAD Algoritmo Construtivo Guloso (ACG)

#include "No.h"
#include <iostream>
#include <iterator>
#include "ACG.h"
#include <list>
#include <algorithm>
#include <cmath>

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
    int quantidadeNos = this->grafoNaoDirecionado->getQuantidadeNos();
    return !this->conectadosNaSolucao.size() == quantidadeNos;
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

void ACG::ordenaVetorNos()
{

}

void ACG::atualizaHeuristica(list <No *> listaNosAdjacentes, No* no)
{   
    int heuristica;
    for (list<No*>::iterator it = listaNosAdjacentes.begin(); it != listaNosAdjacentes.end(); it++)
    {   
        heuristica = (*it)->getHeuristica() - 1;
        (*it)->setHeuristica(heuristica);
    }
    heuristica = no->getHeuristica() - listaNosAdjacentes.size();
    no->setHeuristica(heuristica);
}

void ACG::encontraSubconjuntoDomPond()
{
    int quantidadeNos = this->grafoNaoDirecionado->getQuantidadeNos();

    // vetor de todos os nós do grafo
    vector<No *> nos(quantidadeNos);
    list <No *> listaNos;

    // Preenche o vetor dos nós e inicializa as heurísticas
    int i = 0;
    for (No *aux = this->grafoNaoDirecionado->getPrimeiro(); aux != nullptr; aux = aux->getProx())
    { 
        // if grau == 0, coloca ele na solução
        // else...
        nos.at(i) = aux;
        float grau = aux->getGrau();
        float peso = aux->getPeso();
        nos.at(i)->setHeuristica(grau / peso);
        i++;
    }

    ///////ORDENAR OS NÓS DE ACORDO COM A HEURÍSTICA
    this->ordenaVetorNos();


    while (!verificaFimDaSolucao()){

        No* melhorEscolha = listaNos.front();
        // pegar o primeiro nó da lista dos ordenados
        // colocar na solução
        this->subconjuntoDomPond.push_back(melhorEscolha);
        this->conectadosNaSolucao.push_back(melhorEscolha);

        // colocar ele e os adjacentes na lista de conectados na solução
        list <No*> nosAdjacentesAoVertice = this->grafoNaoDirecionado->encontraNosAdjacentes(melhorEscolha);
        for (list<No*>::iterator it = nosAdjacentesAoVertice.begin(); it != nosAdjacentesAoVertice.end(); it++)
        {
            this->conectadosNaSolucao.push_back(*it);
        }

        // atualizar a heuristica dos nós adjacentes a ele
        this->atualizaHeuristica(nosAdjacentesAoVertice, melhorEscolha);
        
        // remover ele da lista dos nós
        listaNos.pop_front();        
        quantidadeNos --;

        // reordenar os nós pelo valor da heuristica
        this->ordenaVetorNos();
    }
    
}

void ACG::encontraSubconjuntoDomPondRandomizado(float alfa)
{
    int cont = 0;
    {
        cont++;
    }

    
    //for (No *aux = this->grafoNaoDirecionado->getPrimeiro(); aux != nullptr; aux = aux->getProx()<int> ordematualizada(cont));

    vector<float> possibilidades(cont);

    int i = 0;
    for (No *aux = this->grafoNaoDirecionado->getPrimeiro(); aux != nullptr; aux = aux->getProx())
    {
        float grau = aux->getGrau();
        float peso = aux->getPeso();
        grau = grau - peso;
        if (grau < 0)
            grau = grau * (-1);
        possibilidades.at(i) = grau;
        i++;
    } // lista com os valores de k. Melhor solução = maior valor

    // Ordenar
    float atual = 0;
    int k;
    std::sort(possibilidades.begin(), possibilidades.end(), greater<float>());

    vector<No *> nos(cont);

    for (int k = 0; k < cont; k++)
    {
        for (No *aux = this->grafoNaoDirecionado->getPrimeiro(); aux != nullptr; aux = aux->getProx())
        {
            float grau = aux->getGrau();
            float peso = aux->getPeso();
            grau = grau - peso;
            //if (grau == possibilidades.at(k))
               // ordematualizada.at(k) = aux->getId();
        }
    }

    int p = 0;
    for (No *aux = this->grafoNaoDirecionado->getPrimeiro(); aux != nullptr; aux = aux->getProx())
    {
        nos.at(p) = aux;
        p++;
    }
    // pegar melhor alternativa
    int n = std::ceil(possibilidades.size() * alfa);
    int posicaoRandom = rand() % n;
    std::cout << "Posicao random: " << posicaoRandom << endl;

    //int index = this->encontraNoComId(nos, ordematualizada.at(posicaoRandom));
    int index = 0;
    No *e = nos.at(index);

    possibilidades.at(posicaoRandom) = -1;
    // for(int k =0; k< i; k++) {
    //     cout << possibilidades.at(k) << endl;
    // }
    std::sort(possibilidades.begin(), possibilidades.end(), greater<float>());

     for (int k = 0; k < cont; k++)
        {
        for (No *aux = this->grafoNaoDirecionado->getPrimeiro(); aux != nullptr; aux = aux->getProx())
        {
            float grau = aux->getGrau();
            float peso = aux->getPeso();
            grau = grau - peso;
           // if (grau == possibilidades.at(k))
            //    ordematualizada.at(k) = aux->getId();
        }
        }
    while (!verificaFimDaSolucao())
    {
        for (int k = 0; k < cont; k++)
        {
            for (No *aux = this->grafoNaoDirecionado->getPrimeiro(); aux != nullptr; aux = aux->getProx())
            {
                float grau = aux->getGrau();
                float peso = aux->getPeso();
                grau = grau - peso;
                //if (grau == possibilidades.at(k))
                  //  ordematualizada.at(k) = aux->getId();
            }
        }
        if (!verificaConexao(e))
        {
            this->subconjuntoDomPond.push_back(e);
            this->conectadosNaSolucao.push_back(e);
            list<No *> nosAdje = this->grafoNaoDirecionado->encontraNosAdjacentes(e);
            list<No *>::iterator it;
            for (it = nosAdje.begin(); it != nosAdje.end(); it++)
            {
                this->conectadosNaSolucao.push_back(*it);
            }
        }
        // int n = std::ceil(possibilidades.size() * alfa);
        posicaoRandom = rand() % n;
        std::cout << "Posicao random: " << posicaoRandom << endl;
        std::cout << "Possibilidades: " << possibilidades.at(posicaoRandom) << endl;
        for (int k = 0; k < i; k++)
        {
            std::cout << possibilidades.at(k) << endl;
        }
        //index = this->encontraNoComId(nos, ordematualizada.at(posicaoRandom));
        e = nos.at(index);
        possibilidades.at(posicaoRandom) = -1;
        std::sort(possibilidades.begin(), possibilidades.end(), greater<float>());

         
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
    std::cout << "Imprime a solucao" << endl;
    list<No *>::iterator it;

    for (it = this->subconjuntoDomPond.begin(); it != this->subconjuntoDomPond.end(); it++)
    {
        std::cout << (*it)->getId() << endl;
    }
}