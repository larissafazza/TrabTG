#include "Aresta.h"
#include "No.h"
#include <fstream>
#include <vector>
#include <list>

using namespace std;

class Grafo {

    private:
    No *primeiro;
    No *ultimo;
    int ordem;
    int quantidadeNos;
    bool direcionado;
    bool pesoAresta;
    void auxSubConjDominante(No *no,vector<No*>&solucao,bool *entraNaSolucao);

    public:
    Grafo(bool direcionado,bool pesoAresta);
    ~Grafo();
    int getQuantidadeNos();
    void inserirNo(int id,float peso);
    void inserirAresta(int origem,int destino, float peso, int pesoOrigem, int pesoDestino);
    void removerNo(int id);
    void removerAresta(int origem,int destino);
    void setPrimeiro(No *primeiro);
    void setDirecionado(bool direcionado);
    No* getPrimeiro();
    No* getUltimo();
    No *getNo(int id);
    bool getDirecionado();
    void imprimir();
    void uniao(Grafo *grafo_uniao);
    void setOrdem(int ordem);
    int getOrdem();
    bool getPesoAresta();  
    void subConjDominante();
    list<No*> encontraNosAdjacentes(No *vertice);
    void diferenca(Grafo *diferenca);
    void intersecao(Grafo *intersecao);
    void resetarNos();
    No *getNoCoeficiente(float c);
    void imprimirDot(Grafo *grafo);
    void criarLista(vector<No*>&ordenados);
    void randomizado();
    void subConjDominante2();
    void leitura(string input_file);
    void leituraParte2(string input_file);
};