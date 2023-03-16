#include "No.h"

No::No()
{
    this->id = 0;
    this->primeira = nullptr;
    this->proxNo = nullptr;
    this->grau = 0;
    this->visitado = false;
    this->jaEstaNaSolucao = false;
    this->peso = 0;
    this->coeficiente = 0;
}
No::~No()
{

}
void No::setPeso(int peso)
{
    this->peso = peso;
}
bool No::getVisitado()
{
    return this->visitado;
}
void No::setVisitado(bool visitado)
{
    this->visitado = visitado;
}
void No::setjaEstaNaSolucao(bool solucao)
{
    this->jaEstaNaSolucao = solucao;
}
void No::setCoeficiente(float c)
{
    this->coeficiente = c;
}
Aresta *No::getAresta(int id)
{
    for(Aresta *aux = this->getPrimeira(); aux!=nullptr; aux = aux->getProxima()){
        if(aux->getId() == id)
        return aux;
    }
    return nullptr;
}
float No::getCoeficiente()
{
    return this->coeficiente;
}
bool No::getjaEstaNaSolucao()
{
    return this->jaEstaNaSolucao;
}
void No::setId(int id)
{
    this->id = id;
}
void No::setProx(No *prox)
{
    this->proxNo = prox;
}
void No::setPrimeira(Aresta *primeira)
{
    this->primeira = primeira;
}
int No::getPeso()
{
    return this->peso;
}
void No::setGrauDaSolucao(int grauDaSolucao)
{
    this->grauDaSolucao = grauDaSolucao;
}
int No::getGrauDaSolucao()
{
    return this->grauDaSolucao;
}
int No::getId()
{
    return this->id;
}
int No::getGrau()
{
    return this->grau;
}
No* No::getProx()
{
    return this->proxNo;
}
Aresta* No::getPrimeira()
{
    return this->primeira;
}
void No::inserirAresta(int id,float peso)
{
    if(!procurarAresta(id)){
    Aresta *nova = new Aresta(id);
    nova->setPeso(peso);
    if (this->primeira == nullptr){
        this->setPrimeira(nova);
    }
    else{
        Aresta *aux = this->primeira;
        while(aux->getProxima()!=nullptr){
            aux = aux->getProxima();
        }
        aux->setProxima(nova);
    }
    this->grau++;
    }
}
bool No::procurarAresta(int i)
{
    for(Aresta *aux = this->getPrimeira(); aux!=nullptr; aux = aux->getProxima()){
        if(aux->getId() == i)
        return true;
    }
    return false;
}