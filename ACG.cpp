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
        float grau = (*it)->getGrauDaSolucao() - 1;
        (*it)->setGrauDaSolucao(grau);
        float peso = (*it)->getPeso();
        (*it)->setHeuristica(grau/peso);
        // heuristica = (*it)->getHeuristica() - 1;
        // (*it)->setHeuristica(heuristica);
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
        aux->setGrauDaSolucao(aux->getGrau());
        if(aux->getGrau()== 0){
            this->subconjuntoDomPond.push_back(aux);
            if(!verificaConexao(aux))
                this->conectadosNaSolucao.push_back(aux);    
        }

        else{

            listaNos.push_back(aux);
            float grau = aux->getGrauDaSolucao();
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
        aux->setGrauDaSolucao(aux->getGrau());
        if(aux->getGrau()== 0){
            aux->setHeuristica(0);
            this->subconjuntoDomPond.push_back(aux);
            if(!verificaConexao(aux))
                this->conectadosNaSolucao.push_back(aux);    
        }

        else{

            listaNos.push_back(aux);
            float grau = aux->getGrauDaSolucao();
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

double ACG::encontraSolucao(float alfa){
    //encontrar o subconjunto dopminante poderado e calcular a heuristica da solucao = soma dos pesos dos nós da solução * numero de nós na soluçao.
    double heuristica = 0;
    this->limparGrafo();
    this->encontraSubconjuntoDomPondRandomizado(alfa);
    for (list<No*>::iterator it = this->subconjuntoDomPond.begin(); it != this->subconjuntoDomPond.end(); it++)
    {   
        cout << "Peso da heuristica: " << (*it)->getHeuristica() << " - " ;
        heuristica += (*it)->getHeuristica();
    }
    // cout << "\n HEURISTICA = " << heuristica*subconjuntoDomPond.size() << endl;
    return heuristica / subconjuntoDomPond.size();
}

void ACG::atualizaProbabilidades(double *mediaDeCadaAlfa, int *execucoes, float *probabilidades){
    cout << "Fucao atualizaProbabilidades" << endl;
    double somaDasMediasHeuristicas = 0;
    for(int i = 0; i<5 ; i++) {
        if(execucoes[i] == 0){
            mediaDeCadaAlfa[i] = 0;
        } else {
            mediaDeCadaAlfa[i] = mediaDeCadaAlfa[i] / execucoes[i];
            somaDasMediasHeuristicas += mediaDeCadaAlfa[i];
        }
    }
    for(int i = 0; i<5 ; i++) {
        probabilidades[i] = mediaDeCadaAlfa[i] / somaDasMediasHeuristicas;
        mediaDeCadaAlfa[i] = 0;
        execucoes[i] = 0;
    }
}

int ACG::sorteiaAlfa(float *probabilidades) {
    
    std::random_device rd;
    std::mt19937 gen(rd());

    float somaProbabilidades = 0;

    //PEGAR UM NÚMERO ALEATÓRIO ENTRE 0 e 1
    std::uniform_real_distribution<> distrib(0, 1);
    // Gera um número inteiro aleatório
    float valorRand = (double) distrib(gen);
    cout << "Valor sorteado: " << valorRand << endl;

    int i = 0;
    for (i=0; i < 5; i++) {
        somaProbabilidades  += probabilidades[i];
        if(somaProbabilidades >= valorRand){
            break;
        }
    }
    return i;
}

void ACG::encontraSubconjuntoDomPondRandomizadoAdaptativo(float *alfas){

    float probabilidadeDeCadaAlfa[5] = {0.2, 0.2, 0.2, 0.2, 0.2};
    double mediaHeuristicaCadaAlfa[5] = {0, 0, 0, 0, 0};
    int numeroExecucoesDeCadaAlfa[5] = {0, 0, 0, 0, 0};
    int iteracoes = 30;
    int contadorExecucoes = 0;
    double melhorHeur = 0;
    list <No*> solucaoProblema;

    while (contadorExecucoes < iteracoes) {

        contadorExecucoes++;
        int idAlfa = sorteiaAlfa(probabilidadeDeCadaAlfa); // Valor entre 0 e 4

        cout << "Alfa selecionado: " << alfas[idAlfa] << endl;
        cout << "Alfa selecionado: " << idAlfa << endl;

        double valorHeuristica = encontraSolucao(alfas[idAlfa]);
        cout << "heuristica: " << valorHeuristica << endl;
        cout << "tamanho da solucao: " << this->subconjuntoDomPond.size() << endl;

        mediaHeuristicaCadaAlfa[idAlfa] += valorHeuristica;
        numeroExecucoesDeCadaAlfa[idAlfa]++;

        if(contadorExecucoes % 250 == 0) {
            atualizaProbabilidades(mediaHeuristicaCadaAlfa, numeroExecucoesDeCadaAlfa, probabilidadeDeCadaAlfa);
        }

        if (valorHeuristica > melhorHeur) {
            cout << "Encontrou soluco melhor" << endl;
            solucaoProblema.clear();
            melhorHeur = valorHeuristica;

            
            //this->imprimeSolucao();
            for (list<No*>::iterator it = this->subconjuntoDomPond.begin(); it != this->subconjuntoDomPond.end(); it++)
            {   
                solucaoProblema.push_back(*it);
            }
       }

        cout << contadorExecucoes << "a solucao: " << endl;
        for (list<No*>::iterator it = solucaoProblema.begin(); it != solucaoProblema.end(); it++)
        {   
            cout << (*it)->getId() << " ";
        }
        cout << "\n" << endl;
        //PRINTAS INFPORMAÇÕES

        this->limparGrafo();
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