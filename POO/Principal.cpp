// Proyecto final de programacion
// Sistema de una caja registradora para una ferretería
// Este programa toma registros como nombre, Codigo Postal, número de teléfono móvil, monto pagado, 
// monto adeudado, fecha de pago. El sistema deberá agregar artículos, quitar artículos, 
// e imprimir ticket con el total a pagar.
// programa principal

#include "iostream"
#include "cstring"
#include "ctime"
#include "cstdlib"
#include "fstream"
#include "cmath"
#include "Clientes.h"
#include "Productos.h"
#include "Cuenta.h"
using namespace std;

int main(){
    Productos productos;
    Clientes clientes;
    Cuenta cuenta;
    char opcion, continuar;
    bool validacion = false;
    ofstream Ticket;
    time_t now = time(0);
    string date_time = ctime(&now);
    string nombre_archivo = date_time + ".dat";
    intro();
        
    do{
    system("clear");
    cout << "===================================================" <<endl;
    cout << "\n\t\tCONTROL DE ACCESO\n" <<endl;
    cout << "===================================================" <<endl;
    cout << "[1] Iniciar sesion" << endl;
    cout << "[2] Cambiar usuario y contrasena" << endl;
    cout << "\nOPCION:";
    cin >> opcion;
        switch(opcion){   
            case '1':
            cuenta.ingresar();
            if(validacion = true){
                // MENU PRINCIPAL UNA VEZ INGRESADO
                do{
                    system("clear");
                    cout << "===================================================" <<endl;
                    cout << "\n\t\tFERRETERIA CARROD\n" <<endl;
                    cout << "===================================================" <<endl;
                    cout << "SELECCIONA OPCION A REALIZAR" << "\n" << endl;
                    cout << "[1] Comprar Productos" << endl;
                    cout << "[2] Cancelar compra" << endl;
                    cout << "[3] Lista de Productos" << endl;
                    cout << "[4] Imprimir Factura" << endl;
                    cout << "[5] Salir" << endl;
                    cout << "\nOPCION: ";
                    cin >> opcion;
                        switch(opcion){   
                            case '1':
                                productos.AgregarProducto();
                            break;

                            case '2':
                                cuenta.ingresar();
                                if(validacion = true){
                                    cout << "\nCompra cancelada correctamente " << endl;
                                }
                            break;
                            
                            case '3':
                                productos.MostrarProductos();
                            break;

                            case '4':
                                system("clear");
                                escribeCuenta();
                                productos.Ticket_Productos();
                            break;

                            case '5':
                                exit(0);
                            break;

                            default:
                                cout<< "Opcion invalida, elija una operacion a realizar";
                            break;
                        }
                        cout << endl;
                        cout << "==========================================================" <<endl;
                        cout << "Deseas realizar otra funcion? \n[1] Si \n[0] No" <<endl;
                        cin >> continuar;
                        
                    }while(continuar == '1');
            }
            break;

            case '2':
                cuenta.cambiar();
            break;

            default:
                cout<< "Opcion invalida, elija una operacion a realizar";
            break;
        }
        cout << "\n==========================================================" <<endl;
        cout << "Deseas realizar otra funcion? \n[1] Si \n[0] No" <<endl;
        cin >> continuar;
    }while(continuar == '1');
}