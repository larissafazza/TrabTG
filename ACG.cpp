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
    return this->conectadosNaSolucao.size() == quantidadeNos;
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

void ACG::calculaHeuristica()
{
}

void ACG::ordenaVetorNos(std::vector<No*>& vectornos) {
    std::sort(vectornos.begin(), vectornos.end(), compararPorHeur);
}

// Função de comparação para ordenar os objetos No pelo atributo 'heur'
bool compararPorHeur(const No* a, const No* b) {
    return a->heur > b->heur;
}

void ACG::atualizaHeuristica(No *no)
{
}

void ACG::encontraSubconjuntoDomPond()
{
    int quantidadeNos = this->grafoNaoDirecionado->getQuantidadeNos();

    // vetor de todos os nós do grafo
    vector<No *> nos(quantidadeNos);

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
    this->ordenaVetorNos(nos);

    // enquanto não for o fim da solução,
    // pegar o primeiro nó da lista dos ordenados
    // colocar na solução
    // colocar ele e os adjacentes na lista de conectados na solução
    // remover ele da lista dos nós
    // atualizar a heuristica dos nós adjacentes a ele
    // reordenar os nós pelo valor da heuristica

    /*while (!verificaFimDaSolucao())
    {
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
        melhor = -1;
        for (k = 0; k < i; k++)
        {
            if (possibilidades.at(k) > melhor)
            {
                melhor = possibilidades.at(k);
                posicaoDoMelhor = k;
            }
        }
        e = nos.at(posicaoDoMelhor);
        possibilidades.at(posicaoDoMelhor) = -1;
        ind = posicaoDoMelhor-1;
        nos.erase(nos.begin()+ (ind));
    } */
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