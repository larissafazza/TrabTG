#include "Aresta.h"

Aresta::Aresta(int id)
{
    this->peso = 0;
    this->id = id;
    this->proxima = nullptr;
}
Aresta::~Aresta()
{

}
void Aresta::setId(int id)
{
    this->id = id;
}
void Aresta::setPeso(float peso)
{
    this->peso = peso;
}
void Aresta::setProxima(Aresta *proxima)
{
    this->proxima = proxima;
}
int Aresta::getId()
{
    return this->id;
}
int Aresta::getPeso()
{
    return this->peso;
}
Aresta* Aresta::getProxima()
{
    return this->proxima;
}