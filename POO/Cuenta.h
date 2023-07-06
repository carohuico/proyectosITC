#ifndef CUENTA_H
#define CUENTA_H

#include "iostream"
#include "iomanip"
#include "fstream"
#include "cstring"
using namespace std;

class Cuenta{
    private:
    int c = 1;
    char opcion, continuar;
    bool validacion; 
    string usuario, contra, usuarioIngresado, contraIngresada;

    public:
    Cuenta();
    void cambiar();
    bool ingresar();
    ~Cuenta();
};


Cuenta::Cuenta(){}
void Cuenta::cambiar(){
    ingresar();
    if(validacion = true){
        ofstream archivo("controlDeAcceso.txt"); 
        cin.ignore();

        if(archivo.is_open()){
            cout << "\nIngrese su nuevo usuario: ";
            getline(cin, usuario);

            archivo << usuario << endl; 

            cout << "Ingrese su nueva contrasena: ";
            cin >> contra;

            archivo << contra << endl;

            archivo.close();
        } 
    }
}

bool Cuenta::ingresar(){
    
    ifstream leerArchivo;
    leerArchivo.open("controlDeAcceso.txt");
    leerArchivo >> usuario;
    leerArchivo >> contra;

    cout << "Ingrese su usuario: ";
    cin >> usuarioIngresado;

    cout << "Ingrese su contrasena: ";
    cin >> contraIngresada;
    
    while((usuario != usuarioIngresado)or(contra != contraIngresada)){
        cout << "\n\nEl usuario o contrasena es incorrecto" << endl;        
        cout << "Ingrese nuevamente su usuario: ";
        cin >> usuarioIngresado;
        cout << "Ingrese nuevamente su contrasena: ";
        cin >> contraIngresada;
        c++;
        if(c > 3){
        cout << "---------Usuario Bloqueado---------";
        validacion = false; 
        exit(0);
        }
    }
    validacion = true;
}
Cuenta::~Cuenta(){}

#endif