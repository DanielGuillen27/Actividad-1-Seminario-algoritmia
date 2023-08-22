#include <iostream>
#include <string>
#include "paquete.hpp"
#include "paqueteria.hpp"
using namespace std;

int main() {
    system("color 0A");
    int respuesta;
    int flag = 1;
    Paqueteria<Paquete> miTienda;

    do {
        system("cls");

        cout <<"--------------------------------"<< endl;
        cout <<"|            MENU               |"<< endl;
        cout <<"|                               |"<< endl;
        cout <<"|    1) Agregar paquete:        |"<< endl;
        cout <<"|    2) Eliminar paquete:       |"<< endl;
        cout <<"|    3) Mostrar:                |"<< endl;
        cout <<"|    4) Guardar:                |"<< endl;
        cout <<"|    5) Recuperar:              |"<< endl;
        cout <<"|                               |"<< endl;
        cout <<"--------------------------------"<< endl;
        cout << "-> ";
        cin >> respuesta;


        switch(respuesta) {

            case 1: {
                Paquete mipaquete; //creamos el objeto
                int id;
                float peso;

                string origen, destino;

                cout  << "introduzca un id:" <<  endl;
                cin>>id;

                cout  << "introduzca un origen:" <<  endl;
                cin.ignore();
                getline(cin,origen);


                cout  << "introduzca un destino:" <<  endl;
                getline(cin,destino);

                cout  << "introduzca un peso:" <<  endl;
                cin>>peso;

                mipaquete.setId(id);
                mipaquete.setOrigen(origen);
                mipaquete.setDestino(destino);
                mipaquete.setPeso(peso);

                miTienda.insertData(nullptr, mipaquete); //lo agregamos en la primera posicion a la lista o paqueteria
                break;

                }

            case 2: {

                miTienda.deleteData(miTienda.getFirstPos()); // elimina en la primera posicion

                break;
                }

            case 3: {

                cout << miTienda.toString() << endl;

                break;
                }

            case 4: {

               miTienda.WriteFromDisk("inventario.txt");
                cout << "Guardando en el archivo" << endl;

                break;
                }

            case 5: {

                miTienda.ReadFromDisk("inventario.txt");
                cout << "Se leyó el archivo correctamente" << endl;

                break;
                }

            default: {
                cout << "¡¡ OPCION NO ENCONTRADA !!" << endl;
                }

            }

        cout << "SELECCIONAR OTRA OPCION SI[1] / NO[2]" << endl;
        cin>>flag;

        }
    while(flag == 1);
    }
