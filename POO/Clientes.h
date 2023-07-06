// Proyecto final de programacion
// Sistema de una caja registradora para una ferretería
// Este programa toma registros como nombre, Codigo Postal, número de teléfono móvil, monto pagado, 
// monto adeudado, fecha de pago. El sistema deberá agregar artículos, quitar artículos, 
// e imprimir ticket con el total a pagar.
#ifndef CLIENTES_H
#define CLIENTES_H

#include "iostream"
#include "iomanip"
#include "fstream"
#include "cstring"

using namespace std;
#include "Productos.h"

class Clientes{
    protected:
    char nombre[50];
    string telefono, CP;
    string user, contra;
    string usuarioIngresado, contraIngresada;
    char* date_time;
    int c;

    public:
    Clientes();
    void getDatos();
    void imprimirDatos();
    void imprimirFecha();
    void controlDeAcceso();
    void reportar();
    ~Clientes();
};

// Herencia de superclase 
class TicketDatos : public Clientes{
    private:
    int i;

    public:
    TicketDatos();
    void Ticket_Datos();
    ~TicketDatos();

};

//Se declara la funcion a desplegar al principio del programa
void intro();

void intro(){
    cout << "\n\n\n\tFERRETERIA CARROD";
    cout << "\n\n\n\tPresione ENTER";
    cin.get();
}

Clientes::Clientes(){}

void Clientes::getDatos(){
    cout << "Introduzca su Nombre Completo: ";
    cin.ignore();
    cin.getline(nombre,50);

    cout << "\nIntroduzca su Telefono(10 digitos): ";
    cin >> telefono;

    if(telefono.length() != 10){
        do{
            cout << "\nIntroduzca su Telefono(10 digitos): ";
            cin >> telefono;

        }while(telefono.length() != 10);
    }


    cout << "\nIntroduzca su Codigo Postal(5 digitos): ";
    cin >> CP;

        if(CP.length() != 5){
        do{
            cout << "\nIntroduzca su Codigo Postal(5 digitos): ";
            cin >> CP;
        }while(CP.length() != 5);
    }

    cout << endl;
    //conseguir la fecha
    time_t now = time(0);
    date_time = ctime(&now);
}

void Clientes::imprimirFecha(){
    cout << "FECHA: " << date_time << endl;
}

void Clientes::imprimirDatos(){
    cout << "NOMBRE DEL CLIENTE: " << nombre << endl;
    cout << "TELEFONO: " << telefono << endl;
    cout << "CODIGO POSTAL: " << CP << endl;
}

Clientes::~Clientes(){}

TicketDatos::TicketDatos(){}

void TicketDatos::Ticket_Datos(){
    Clientes clientes[100];
    clientes[i].getDatos();
    // ciclo para enseñar datos
    cout << "==========================================================" << endl;
    cout << "TICKET DE COMPRA:";
    cout << "\t\t";
    clientes[i].imprimirFecha();
    cout << endl;
    cout << "Datos del Cliente" << endl;
    clientes[i].imprimirDatos();
    //dividir el nombre con el ticket
    cout << "==========================================================" << endl;
}

TicketDatos::~TicketDatos(){}

time_t now = time(0);
string date_time = ctime(&now);
string nombre_archivo = date_time + ".dat";

void escribeCuenta();
void imprimirCuentas();

void escribeCuenta(){
    TicketDatos ticketD;
    ofstream archivoSalida;

    archivoSalida.open(nombre_archivo, ios::binary|ios::app);
    ticketD.Ticket_Datos();
    archivoSalida.write(reinterpret_cast<char *>(&ticketD), sizeof(TicketDatos));
    archivoSalida.close();
}

#endif