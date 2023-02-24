#ifndef NO_H
#define NO_H 1

#include "Aresta.h"

class No {

    private:
    int id; //indice do nó;
    int peso;
    No *proxNo; //ponteiro que aponta para o proximo nó;
    Aresta *primeira; //ponteiro para a primeira aresta;
    int grau;
    float heur;
    bool visitado;
    bool jaEstaNaSolucao;
    float coeficiente;

    public:
    No();
    ~No();

    void setHeuristica(float val){this->heur = val;};
    float getHeuristica() {return this->heur;};
    
    void setId(int id);
    void setProx(No *prox);
    void setjaEstaNaSolucao(bool solucao);
    void setPrimeira(Aresta *primeira);
    int getId();
    bool getjaEstaNaSolucao();
    bool getVisitado();
    void setVisitado(bool visitado);
    int getGrau();
    No* getProx();
    Aresta* getPrimeira();
    void inserirAresta(int id, float peso);
    bool procurarAresta(int i);
    int getPeso();
    void setPeso(int peso);
    void setCoeficiente(float c);
    float getCoeficiente();
    Aresta *getAresta(int id);

};

#endif // NO_H