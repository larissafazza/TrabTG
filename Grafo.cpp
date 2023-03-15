#include "Grafo.h"
#include "No.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <list>
#include <string>
#include <time.h> /* time_t, struct tm, difftime, time, mktime */

using namespace std;

Grafo::Grafo(bool direcionado, bool pesoAresta)
{
    this->ordem = 0;
    this->primeiro = nullptr;
    this->direcionado = direcionado;
    this->ultimo = nullptr;
    this->pesoAresta = pesoAresta;
}
Grafo::~Grafo()
{
    No *no = this->getPrimeiro();
    No *aux;
    this->quantidadeNos = 0;
    while (no != nullptr)
    {
        aux = no;
        no = no->getProx();
        delete aux;
    }
}
void Grafo::setOrdem(int ordem)
{
    this->ordem = ordem;
}
int Grafo::getOrdem()
{
    return this->ordem;
}
No *Grafo::getNo(int id)
{
    No *aux = this->primeiro;
    while (aux != nullptr)
    {
        if (aux->getId() == id)
            return aux;
        aux = aux->getProx();
    }
    return nullptr;
}
bool Grafo::getPesoAresta()
{
    return this->pesoAresta;
}
void Grafo::inserirNo(int id, float peso)
{
    if (this->getNo(id) == nullptr)
    {
        No *novo = new No();
        novo->setId(id);
        novo->setPeso(peso);
        if (this->primeiro == nullptr)
        {
            this->primeiro = this->ultimo = novo;
        }
        else
        {
            ultimo->setProx(novo);
            this->ultimo = novo;
        }
        this->quantidadeNos ++;
    }
}
void Grafo::inserirAresta(int origem, int destino, float peso, int pesoOrigem, int pesoDestino)
{
    if (this->getNo(origem) == nullptr)
    {
        this->inserirNo(origem, pesoOrigem);
    }
    if (this->getNo(destino) == nullptr)
    {
        this->inserirNo(destino, pesoDestino);
    }
    No *no_origem = this->getNo(origem);
    No *no_destino = this->getNo(destino);
    no_origem->inserirAresta(destino, peso);
    if (!this->direcionado)
    {
        no_destino->inserirAresta(origem, peso);
    }
}
void Grafo::removerNo(int id)
{
    this->quantidadeNos --;
}
int Grafo::getQuantidadeNos(){
    return this->quantidadeNos;
}

void Grafo::removerAresta(int origem, int destino)
{
}
void Grafo::setPrimeiro(No *primeiro)
{
    this->primeiro = primeiro;
}
void Grafo::setDirecionado(bool direcionado)
{
    this->direcionado = direcionado;
}
No *Grafo::getPrimeiro()
{
    return this->primeiro;
}
No *Grafo::getUltimo()
{
    return this->ultimo;
}
bool Grafo::getDirecionado()
{
    return this->direcionado;
}
void Grafo::resetarNos()
{
    for (No *aux = this->getPrimeiro(); aux != nullptr; aux = aux->getProx())
    {
        aux->setVisitado(false);
        aux->setjaEstaNaSolucao(false);
    }
}
void Grafo::imprimir()
{
    No *aux = this->getPrimeiro();
    while (aux != nullptr)
    {
        cout << aux->getId() << "(Peso No:" << aux->getGrau() << ")";
        for (Aresta *aresta = aux->getPrimeira(); aresta != nullptr; aresta = aresta->getProxima())
        {
            cout << " ---> ";
            cout << aresta->getId() << " (Peso Aresta:" << aresta->getPeso() << ")";
        }
        cout << endl;
        aux = aux->getProx();
    }
}
void Grafo::uniao(Grafo *grafo_uniao)
{
    cout << "Uniao: " << endl
         << "===========================================" << endl;
    Grafo *novo = new Grafo(this->direcionado, this->pesoAresta);
    for (No *aux = this->getPrimeiro(); aux != nullptr; aux = aux->getProx())
    {
        novo->inserirNo(aux->getId(), aux->getPeso());
        for (Aresta *aresta = aux->getPrimeira(); aresta != nullptr; aresta = aresta->getProxima())
        {
            novo->inserirAresta(aux->getId(), aresta->getId(), aresta->getPeso(), 0, 0);
        }
    }
    for (No *aux = grafo_uniao->getPrimeiro(); aux != nullptr; aux = aux->getProx())
    {
        novo->inserirNo(aux->getId(), aux->getPeso());
        for (Aresta *aresta = aux->getPrimeira(); aresta != nullptr; aresta = aresta->getProxima())
        {
            novo->inserirAresta(aux->getId(), aresta->getId(), aresta->getPeso(), 0, 0);
        }
    }
    novo->imprimir();
    cout << "===========================================" << endl;
    imprimirDot(novo);
}
No *Grafo::getNoCoeficiente(float c)
{
    for (No *aux = this->primeiro; aux != nullptr; aux = aux->getProx())
        if (aux->getCoeficiente() == c)
            return aux;
    return nullptr;
}
void Grafo::criarLista(vector<No *> &ordenados)
{
    resetarNos();
    vector<float> lista_coeficientes;
    float coeficiente;
    for (No *aux = this->getPrimeiro(); aux != nullptr; aux = aux->getProx())
    {
        coeficiente = float(aux->getGrau()) / aux->getPeso();
        lista_coeficientes.push_back(coeficiente);
        aux->setCoeficiente(coeficiente);
    }
    // imprimir coeficientes
    sort(lista_coeficientes.begin(), lista_coeficientes.end());
    for (int i = 0; i < lista_coeficientes.size(); i++)
    {
        // cout << lista_coeficientes.at(i) << " ";
        ordenados.push_back(getNoCoeficiente(lista_coeficientes.at(i)));
    }
    cout << endl;
    cout << "Imprimindo lista de vertices ordenadas de acordo com coeficiente grau/peso: " << endl;
    cout << "====================================================================================" << endl;
    for (int i = 0; i < ordenados.size(); i++)
        cout << ordenados.at(i)->getId() << " ";
    cout << endl
         << "====================================================================================" << endl
         << endl;
}
void Grafo::subConjDominante()
{
    vector<No *> ordenados;
    criarLista(ordenados);
    int pesoTotal = 0;
    vector<No *> solucao;
    bool entraNaSolucao = false;
    for (int i = ordem - 1; i >= 0; i--)
    {

        auxSubConjDominante(ordenados.at(i), solucao, &entraNaSolucao);
    }
    cout << "Tamanho do subconjunto dominante minimo pelo Algoritmo Construtivo Guloso: " << solucao.size() << endl;
    for (int i = 0; i < solucao.size(); i++)
    {
        cout << solucao.at(i)->getId() << " ";
        pesoTotal += solucao.at(i)->getPeso();
    }
    cout << endl
         << "====================================================================================" << endl;
    cout << "Peso Total:" << pesoTotal << endl;
    cout << "====================================================================================" << endl;

    ordenados.clear();
    solucao.clear();
    resetarNos();
}
void Grafo::auxSubConjDominante(No *no, vector<No *> &solucao, bool *entraNaSolucao)
{
    no->setVisitado(true);
    Aresta *aresta = no->getPrimeira();
    while (aresta != nullptr)
    {
        if (!getNo(aresta->getId())->getVisitado())
        {
            *entraNaSolucao = true;
            getNo(aresta->getId())->setVisitado(true);
        }
        aresta = aresta->getProxima();
    }
    if (*entraNaSolucao && !no->getjaEstaNaSolucao())
    {
        solucao.push_back(no);
        no->setjaEstaNaSolucao(true);
        *entraNaSolucao = false;
    }
}
void Grafo::diferenca(Grafo *diferenca)
{
    cout << "Diferenca: " << endl
         << "===========================================" << endl;
    Grafo *novo = new Grafo(this->direcionado, this->pesoAresta);
    bool permite = true;
    for (No *aux = this->getPrimeiro(); aux != nullptr; aux = aux->getProx())
    {
        if (diferenca->getNo(aux->getId()) != nullptr)
        {
            novo->inserirNo(aux->getId(), 0);
        }
        else
        {
            permite = false;
        }
    }
    if (permite)
    {
        for (No *aux = this->getPrimeiro(); aux != nullptr; aux = aux->getProx())
        {
            for (Aresta *aresta = aux->getPrimeira(); aresta != nullptr; aresta = aresta->getProxima())
            {
                if (!(diferenca->getNo(aux->getId())->procurarAresta(aresta->getId())))
                {
                    novo->inserirAresta(aux->getId(), aresta->getId(), aresta->getPeso(), 0, 0);
                }
            }
        }
    }
    novo->imprimir();
    cout << "===========================================" << endl;
    imprimirDot(novo);
}
/*
int ACG::pesoMaisLongo(list <Aresta *> listaArestas, int id) {
    int peso = 0;
    for (int i = 0; i < lilatividades[id].antecessoras.size(); i++) {
    for(int i=0; i<(*it).)
        int antecessora = atividades[id].antecessoras[i];
        int t = pesoMaisLongo(atividades, antecessora);
        if (t > peso) {
            peso = t;
        }
    }
    return peso + atividades[id].peso;
}

Aresta * maiorPeso(List<Aresta*> listaArestas, int id)
{
    int peso = 0;
    //percorre uma lista dos nós adjacentes ao nó de id do parâmetro
    /*  
        
    }
        int idAresta =  (*it)->getId();
        Aresta *aux = maiorPeso (listaArestasNo, idAresta);
        if(aux->getPeso() > peso)
              peso = aux->getPeso();
return peso + ~Pegar o peso da Aresta da id ~;


}
*/
void Grafo::redePert(Grafo *redepert){
/*

// Encontra o peso mais longo de cada atividade
    for (int i = 0; i < atividades.size(); i++) {
        atividades[i].peso_inicio = pesoMaisLongo(atividades, i);
        atividades[i].peso_fim = atividades[i].peso_inicio + atividades[i].peso;
    }

    // Imprime os pesos mais longos de cada atividade
    for (int i = 0; i < atividades.size(); i++) {
        cout << "Atividade " << atividades[i].id << ": " << atividades[i].peso_inicio << " - " << atividades[i].peso_fim << endl;
    }*/
}
void Grafo::intersecao(Grafo *intersecao)
{
    cout << "Intersecao: " << endl
         << "===========================================" << endl;
    Grafo *novo = new Grafo(this->direcionado, this->pesoAresta);
    for (No *aux = this->getPrimeiro(); aux != nullptr; aux = aux->getProx())
    {
        if (intersecao->getNo(aux->getId()) != nullptr)
        {
            novo->inserirNo(aux->getId(), 0);
            for (Aresta *aresta = aux->getPrimeira(); aresta != nullptr; aresta = aresta->getProxima())
            {
                if ((intersecao->getNo(aux->getId())->procurarAresta(aresta->getId())))
                    novo->inserirAresta(aux->getId(), aresta->getId(), aresta->getPeso(), 0, 0);
            }
        }
    }
    novo->imprimir();
    cout << "===========================================" << endl;
    imprimirDot(novo);
}
void Grafo::imprimirDot(Grafo *grafo)
{
    ofstream output;
    output.open("output.dot", ios::out | ios::trunc);
    if (!this->direcionado)
    {
        output << "strict graph{\n";
        for (No *aux = grafo->getPrimeiro(); aux != nullptr; aux = aux->getProx())
        {
            for (Aresta *aresta = aux->getPrimeira(); aresta != nullptr; aresta = aresta->getProxima())
            {
                output << aux->getId() << " -- " << aresta->getId() << ";\n";
            }
        }
    }
    else
    {
        output << "digraph{\n";
        for (No *aux = grafo->getPrimeiro(); aux != nullptr; aux = aux->getProx())
        {
            for (Aresta *aresta = aux->getPrimeira(); aresta != nullptr; aresta = aresta->getProxima())
            {
                output << aux->getId() << " -> " << aresta->getId() << ";\n";
            }
        }
    }
    output << "}";
    output.close();
    system("dot -Tpng output.dot -o output.png");
}
void Grafo::randomizado()
{
    float alfa;
    cout << "Digite o alfa que voce escolheu:";
    cin >> alfa;
    vector<No *> ordenados;
    criarLista(ordenados);
    int pesoTotal = 0;
    vector<No *> solucao;
    bool entraNaSolucao = false;
    // if(!(alfa == 0.15 || alfa == 0.30 || alfa == 0.50)){
    // cout << "Digite um valor valido para alfa" << endl;
    //}
    // else{
    // for(int i = 0; i < 10; i++){
    srand(time(nullptr));
    int k = (ordem - 1) - (rand() % int(alfa * ordenados.size() - 1));
    auxSubConjDominante(ordenados.at(k), solucao, &entraNaSolucao);
    // ordenados.erase(ordenados.begin()+k-1);
    for (int i = ordenados.size() - 1; i >= 0; i--)
    {
        auxSubConjDominante(ordenados.at(i), solucao, &entraNaSolucao);
        // if(getNo(i)->getjaEstaNaSolucao())
        // ordenados.erase(ordenados.begin()+i-1);
    }
    cout << "Tamanho do subconjunto dominante minimo pelo Algoritmo Construtivo Guloso: " << solucao.size() << endl;
    for (int i = 0; i < solucao.size(); i++)
    {
        cout << solucao.at(i)->getId() << " ";
        pesoTotal += solucao.at(i)->getPeso();
    }
    cout << endl
         << "====================================================================================" << endl;
    cout << "Peso Total:" << pesoTotal << endl;
    cout << "====================================================================================" << endl;

    ordenados.clear();
    solucao.clear();
    resetarNos();
    //}
    //}
}
void Grafo::subConjDominante2() // versao errada
{
    vector<No *> ordenados;
    int pesoTotal = 0;
    for (No *aux = this->getPrimeiro(); aux != nullptr; aux = aux->getProx())
    {
        ordenados.push_back(aux);
    }
    No *x;
    for (int i = 1; i < ordem; i++)
    {
        for (int j = 0; j < ordem - 1; j++)
        {
            if (ordenados.at(j)->getGrau() > ordenados.at(j + 1)->getGrau())
            {
                // cout << getNo(j)->getGrau() << " " << getNo(j+1)->getGrau() << endl;
                x = ordenados.at(j);
                ordenados.at(j) = ordenados.at(j + 1);
                ordenados.at(j + 1) = x;
            }
            else if (ordenados.at(j)->getGrau() == ordenados.at(j + 1)->getGrau())
            {
                if (ordenados.at(j)->getPeso() > ordenados.at(j + 1)->getPeso())
                {
                    x = ordenados.at(j);
                    ordenados.at(j) = ordenados.at(j + 1);
                    ordenados.at(j + 1) = x;
                }
            }
        }
    }
    cout << "Imprimindo lista de arestas ordenadas por maior grau e menor vertice: " << endl;
    for (int i = 0; i < ordenados.size(); i++)
        cout << ordenados.at(i)->getId() << " ";
    cout << "====================================================================================" << endl
         << endl;
    vector<No *> solucao;
    bool entraNaSolucao = false;
    for (int i = ordem - 1; i >= 0; i--)
    {

        auxSubConjDominante(ordenados.at(i), solucao, &entraNaSolucao);
    }
    cout << "Tamanho do subconjunto dominante minimo pelo algoritmo guloso: " << solucao.size() << endl;
    for (int i = 0; i < solucao.size(); i++)
    {
        cout << solucao.at(i)->getId() << " ";
        pesoTotal += solucao.at(i)->getPeso();
    }
    cout << "====================================================================================" << endl;
    cout << pesoTotal << endl
         << endl;
}
list<No *> Grafo::encontraNosAdjacentes(No *vertice)
{
    // retorna os nós adjacentes ao nó
    list<No *> nosAdj;
    Aresta *aux = vertice->getPrimeira();
    while (aux != nullptr)
    {
        int id = aux->getId();
        nosAdj.push_back(this->getNo(id));
        aux = aux->getProxima();
    }
    return nosAdj;
}
void Grafo::leitura(string input_file)
{
    fstream input;
    int ordem_grafo, origem, destino;
    float peso = 0;
    input.open(input_file, ios::in);
    if (input.is_open())
    {
        input >> ordem_grafo;
        this->setOrdem(ordem_grafo);
        if (!this->getPesoAresta())
        {
            while (input >> origem >> destino)
            {
                this->inserirAresta(origem, destino, 0, 0, 0);
            }
        }
        else
        {
            while (input >> origem >> destino >> peso)
            {
                this->inserirAresta(origem, destino, peso, 0, 0);
            }
        }
    }
    else
        cout << "Não foi possível abrir o arquivo! ";
}

void Grafo::leituraParte2(string input_file)
{
    fstream input;
    string linha;
    vector<string> lines;
    vector<float> pesos;
    int ordem_grafo, origem, destino;
    float peso = 0;
    input.open(input_file, ios::in);
    if (input.is_open())
    {
        input >> linha;
        input >> ordem_grafo;
        this->setOrdem(ordem_grafo);
        for (int i = 0; i < ordem_grafo + 3; i++)
            getline(input, linha);
        // cout << ordem;
        for (int i = 0; i < ordem_grafo; i++)
        {
            input >> peso;
            this->inserirNo(i, peso);
        }
        input >> linha;
        while (getline(input, linha))
            lines.push_back(linha);
        for (int i = 1; i < lines.size(); i++)
        {
            for (int j = 0; j < ordem_grafo; j++)
            {
                if (i - 1 != j)
                {
                    if (lines.at(i)[j * 2] == '1')
                    {
                        this->inserirAresta(i - 1, j, 0, 0, 0);
                    }
                }
            }
        }
        // grafo->imprimir();
    }
    else
        cout << "Não foi possível abrir o arquivo! ";
}