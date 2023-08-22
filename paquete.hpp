#ifndef PAQUETE_HPP_INCLUDED
#define PAQUETE_HPP_INCLUDED


#include <fstream>
#include<string>

class Paquete{

private:

    int id;
    std::string origen;
    std::string destino;
    float peso;

public:

    Paquete();

    void setId(int);
    void setPeso(float);
    void setOrigen(std::string);
    void setDestino(std::string);

    int getId();
    std::string getOrigen();
    std::string getDestino();
    float getPeso();

    std::string toString();

    friend std::ostream& operator << (std::ostream&, Paquete&);
    friend std::istream& operator >> (std::istream&, Paquete&);

};


#endif // PAQUETE_HPP_INCLUDED
