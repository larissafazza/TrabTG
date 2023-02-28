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
    void ordenaVetorNos();
    void atualizaHeuristica(list <No *> listaNos, No* no);
    void encontraSubconjuntoDomPond();
    void encontraSubconjuntoDomPondRandomizado(float alfa);
    int encontraNoComId(vector<No*> vet,int id);
    void imprimeSolucao();
    
};