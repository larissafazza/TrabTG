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
    void ordenaVetorNos(std::vector<No*>& vectornos);
    void atualizaHeuristica(No *e);
    void encontraSubconjuntoDomPond();
    void encontraSubconjuntoDomPondRandomizado(float alfa);
    int encontraNoComId(vector<No*> vet,int id);
    void imprimeSolucao();

};