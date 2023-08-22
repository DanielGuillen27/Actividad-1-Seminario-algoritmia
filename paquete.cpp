#include "paquete.hpp"
#include <fstream>

using namespace std;

Paquete::Paquete() {
    id = 0;
    origen = "";
    destino = "";
    peso = 0;

    }

void Paquete::setId(int id_nuevo) {
    id = id_nuevo;
    }

void Paquete::setPeso(float peso_nuevo) {
    peso = peso_nuevo;
    }

void Paquete::setOrigen(string origen_nuevo) {
    origen = origen_nuevo;
    }

void Paquete::setDestino(string destino_nuevo) {
    destino = destino_nuevo;
    }

int Paquete::getId() {
    return id;
    }

string Paquete::getOrigen() {
    return origen;
    }

string Paquete::getDestino() {
    return destino;
    }

float Paquete::getPeso() {
    return peso;
    }


string Paquete::toString() {
    string result;

    result += " ";
    result += to_string(id);
    result += " | ";
    result+= origen;
    result+= " | ";
     result+= destino;
     result+= " | ";
     result+= to_string(peso);
     result +" \n ";

    return result;
    }

//*****************OPERADORES DE FLUJO **********
ostream& operator << (std::ostream& os, Paquete& p) { //Interactua con la pantalla

    os << p.id << endl;
    os << p.origen << endl;
    os << p.destino << endl;
    os << p.peso << endl;

    return os;
    }
istream& operator >> (istream& is, Paquete& p) { //Interactua con el teclado
    string aux,aux2;

    getline(is, aux);
    p.id =  atoi(aux.c_str());

    getline(is, p.origen);
    getline(is, p.destino);
    getline(is, aux2);
    p.peso = std::stof(aux2);

    return is;
    }

