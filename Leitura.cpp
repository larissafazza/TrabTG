/*#include "Leitura.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

Leitura::Leitura()
{

}
Leitura::~Leitura()
{

}
void Leitura::leitura(string input_file, Grafo *grafo)
{
    fstream input;
    int ordem,origem,destino;
    float peso = 0;
    input.open(input_file, ios::in);
    if (input.is_open()) {
    input >> ordem;
    grafo->setOrdem(ordem);
    if(!grafo->getPesoAresta()){
      while(input >> origem >> destino){
        grafo->inserirAresta(origem,destino,0,0,0);
    }
    }
    else{
      while(input >> origem >> destino >> peso){
        grafo->inserirAresta(origem,destino,peso,0,0);
    } 
    }      
  } else
    cout << "Não foi possível abrir o arquivo! ";
}

void Leitura::leituraParte2(string input_file, Grafo *grafo)
{
    fstream input;
    string linha;
    vector<string> lines;
    vector<float> pesos;
    int ordem,origem,destino;
    float peso = 0;
    input.open(input_file, ios::in);
    if (input.is_open()) {
    input >> linha;
    input >> ordem;
    grafo->setOrdem(ordem);
    for(int i = 0; i < ordem+3; i++)
        getline(input, linha);
    //cout << ordem;
    for(int i = 0; i < ordem; i ++){
      input >> peso;
      grafo->inserirNo(i,peso);
    }
    input >> linha;
    while(getline(input,linha))
    lines.push_back(linha);
    for (int i = 1; i < lines.size(); i++){
        for(int j = 0; j < ordem; j++){
          if(i-1 != j){
            if(lines.at(i)[j*2] == '1'){
              grafo->inserirAresta(i-1, j,0,0,0);
            }
          }
        }
      }
    //grafo->imprimir();
         
  } else
    cout << "Não foi possível abrir o arquivo! ";
}*/