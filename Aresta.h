#ifndef ARESTA_H
#define ARESTA_H 1

class Aresta {

    private:
    int id; //indice do nó correspondente a essa aresta
    float peso;
    Aresta *proxima; //ponteiro para a próxima aresta;

    public:
    Aresta(int id);
    ~Aresta();
    void setId(int id);
    void setPeso(float peso);
    void setProxima(Aresta *proxima);
    int getId();
    int getPeso();
    Aresta* getProxima();
};

#endif // ARESTA_H