#include "No.h"
#include "Grafo.h"
#include <fstream>
#include <list>

using namespace std;

class ACG {

    private:
    Grafo * grafoNaoDirecionado;
    list<No*> subconjuntoDomPond;
    list<No*> conectadosNaSolucao;

    public:
    ACG(Grafo *graph);
    ~ACG();
    void limparGrafo();
    bool verificaFimDaSolucao();
    bool verificaConexao(No *e);
    bool compararPorHeur(const No* a, const No* b);
    void calculaHeuristica();
    void atualizaHeuristica(list <No *> listaNosAdjacentes);
    void encontraSubconjuntoDomPond();
    void encontraSubconjuntoDomPondRandomizado(float alfa);
    void encontraSubconjuntoDomPondRandomizadoAdaptativo(float *alfa);
    double encontraSolucao(float alfa);
    int sorteiaAlfa(float *probabilidades);
    void atualizaProbabilidades(double *mediaDeCadaAlfa, int *execucoes, float *probabilidades);
    int encontraNoComId(vector<No*> vet,int id);
    void imprimeSolucao();
    
};