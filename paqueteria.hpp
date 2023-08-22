#ifndef PAQUETERIA_HPP_INCLUDED
#define PAQUETERIA_HPP_INCLUDED

#include <fstream>
#include <istream>
#include <exception>
#include <string>

template <class T>
class Paqueteria {

        class Node; // Forward Declaration

    public:

        class Exception : public std::exception { // Clase anidada
            private:
                std::string msg;
            public:
                explicit Exception(const char* message) : msg(message) { }
                explicit Exception(const std::string& message): msg(message) { }
                virtual ~Exception() throw() { }
                virtual const char* what() const throw ( ) {
                    return msg.c_str();
                    }
            };

        typedef Node* position; //Elgancia en programacion en ves de recibir un Node* recibimos una posicion

    private:
        class Node { // Clase anidada
            private:
                T data;
                position next;
            public:
                Node();
                Node(const T&);

                T getData();
                position getNext() const;

                void setData(const T&);
                void setNext(position);

            };
        position anchor;

        void copyAll(const Paqueteria<T>&);

        bool isValidPos(const position&) const;

    public:

        Paqueteria();
        Paqueteria(const Paqueteria&);
        ~Paqueteria();

        bool isEmpty() const;
        void insertData(const position&,const T&);
        void deleteData(const position&);

        position findData(const T&) const;
        T retrieve(position) const;

        position getFirstPos() const;
        position getLastPos() const;
        position getPrevPost(position) const;
        position getNextPos(position) const;


        void deleteAll();

        std::string toString() const;

        void ReadFromDisk(const std::string&);
        void WriteFromDisk(const std::string& );

        Paqueteria& operator = (const Paqueteria&);


    };

// inicio de node

template <class T>
Paqueteria<T>::Node::Node() : next(nullptr) {}

template <class T>
Paqueteria<T>::Node::Node (const T& e) : data(e), next(nullptr) {}

template <class T>
T Paqueteria<T>::Node::getData()  {
    return data;
    }

template <class T>
typename Paqueteria<T>::position Paqueteria<T>::Node::getNext() const {
    return next;
    }

template <class T>
void Paqueteria<T>::Node::setData(const T& e) {
    data = e;
    }

template <class T>
void Paqueteria<T>::Node::setNext(position p) {
    next = p;
    }

// final de node

using namespace std;

template <class T>

Paqueteria<T>::Paqueteria() : anchor(nullptr) {}

template <class T>
Paqueteria<T>::Paqueteria(const Paqueteria& l) {
    copyAll(l);
    }

template <class T>
Paqueteria<T>::~Paqueteria() {
    deleteAll();
    }

template <class T>
bool Paqueteria<T>::isValidPos(const position& p) const {
    position aux(anchor);

    while(aux != nullptr) { //mientras no llegue al final

        if(aux == p) { //revisa si es esa posicion
            return true;
            }
        aux = aux->getNext(); // se va recorriendo
        }
    return false; // si no la encuentra
    }


template <class T>
bool Paqueteria<T>::isEmpty() const {
    return anchor == nullptr;
    }


template <class T>
void Paqueteria<T>::insertData(const position& p, const T& e) {

    if(p != nullptr and !isValidPos(p)) {
        throw Exception("Posicion invalida, insertada");
        }

    position aux (new Node(e));

    if(aux == nullptr) {
        throw Exception("Memoria no disponible, insertData");
        }
    if(p == nullptr) { //insertar al principio
        aux->setNext(anchor);
        anchor = aux;
        }
    else { // insertamos en otro lugar
        aux->setNext(p->getNext());
        p->setNext(aux); // insercion despues del punto de interes
        }
    }


template <class T>
void Paqueteria<T>::deleteData(const position& p) {
    if(!isValidPos(p)) {
        throw Exception("Posicion invalida, deleteData");
        }

    if(p == anchor) { // primer elemento
        anchor = p->getNext();
        }
    else {
        getPrevPost(p)->setNext(p->getNext());
        }

    delete p;
    }

template <class T>
typename Paqueteria<T>::position Paqueteria<T>::findData(const T& e) const {
        position aux(anchor);

        while( aux != nullptr and aux->getData() != e){
            aux = aux->getNext();
        }
        return aux;
    }

template <class T>
T Paqueteria<T>::retrieve(position p) const {
    if(!isValidPos(p)){
        throw Exception("Posicion invalida, retrieve");
    }

    return p->getData();
    }

template <class T>
typename Paqueteria<T>::position Paqueteria<T>::getLastPos() const {
    if(isEmpty()) {
        return nullptr;
        }
    position aux(anchor);

    while(aux->getNext() != nullptr) {
        aux = aux->getNext();
        }

    return aux;
    }

template <class T>
typename Paqueteria<T>::position Paqueteria<T>::getFirstPos() const {
    return anchor;
    }

template <class T>
typename Paqueteria<T>::position Paqueteria<T>::getNextPos( position p) const {
    if(!isValidPos()) {
        return nullptr;
        }
    return p->getNext();
    }

template <class T>
typename Paqueteria<T>::position Paqueteria<T>::getPrevPost( position p) const {
    if(p == anchor) {
        return nullptr;
        }
    position aux(anchor);

    while(aux != nullptr and aux->getNext() != p) {
        aux = aux->getNext();
        }

    return aux;
    }

template <class T>
void Paqueteria<T>::copyAll(const Paqueteria<T>& l) {
    position aux(l.anchor);
    position lastInserted(nullptr);
    position newNode;

    while(aux != nullptr) {
        if((newNode = new Node(aux->getData()) ) == nullptr) {
            throw Exception("Memoria no disponible, copyAll");
            }

        if(lastInserted == nullptr) {
            anchor = newNode;
            }
        else {
            lastInserted->setNext(newNode);
            }
        lastInserted = newNode;
        aux = aux->getNext();
        }
    }

template <class T>
void Paqueteria<T>::deleteAll() {
    position aux;

    while(anchor != nullptr) {

        aux = anchor;
        anchor = anchor->getNext();
        delete aux;

        }
    }

template <class T>
string Paqueteria<T>::toString() const {
    string result;
    position aux(anchor);

    while(aux != nullptr) {
        result += aux->getData().toString() ;

        aux = aux->getNext();
        }
    return result;
    }

template <class T>
Paqueteria<T>& Paqueteria<T>::operator=(const Paqueteria& l) {
    copyAll(l);
    return *this;
    }


template <class T>
void Paqueteria<T>::ReadFromDisk(const string& fileName) {
    ifstream myFile;

    myFile.open(fileName);

    if(!myFile.is_open()) {

        throw Exception("No se pudo abrir, ReadFromDisk");
        }

    deleteAll();

    T data;

    try {
        while(myFile >> data) {

            insertData(anchor,data);

            }
        }
    catch(const Exception& ex) {

        myFile.close();

        throw Exception("Falló la inserción");
        }

    myFile.close();

    }


template <class T>
void Paqueteria<T>::WriteFromDisk(const string& fileName) {
    ofstream myFile;

    myFile.open(fileName, myFile.trunc);

    if(!myFile.is_open()) {
        throw Exception("No se abrió el archivo, writeFromDisk");
        }

    position aux(anchor);

    while(aux != nullptr){
        myFile<< aux->getData() << endl;
        aux = aux->getNext();
    }

    myFile.close();

    }



#endif // PAQUETERIA_HPP_INCLUDED
