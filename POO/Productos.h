// Proyecto final de programacion
// Sistema de una caja registradora para una ferretería
// Este programa toma registros como nombre, dirección, número de teléfono móvil, monto pagado, 
// monto adeudado, fecha de pago. El sistema deberá agregar artículos, quitar artículos, 
// e imprimir ticket con el total a pagar.
#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include "Clientes.h"

class Productos{
    protected:
    double total = 0, totalFinal = 0, precio;
    int continuar, cantidadFinal = 0, indice;
    string productos[4] = {"Martillo", "Desarmador", "Tuerca", "Taladro"};
    double precios[4] = {50, 60, 1, 500};
    int cantidades[4] = {10, 10, 10, 10};
    int cantidad, idArticulo;
    int idProductos[4] = {1, 2, 3, 4};

    public:
    Productos();
    void MostrarProductos();
    void AgregarProducto();
    void QuitarProducto();
    void Ticket_Productos();
    ~Productos();
};


// Derivacion de Super clase Productos
Productos::Productos(){}

void Productos::MostrarProductos(){
            cout << "=========================================" << endl;
        for(int i = 0; i < 4; i++){
            cout << "ID: " << idProductos[i] << endl;
            cout << "Producto: " << productos[i] << endl;
            cout << "Precio: " << precios[i] << endl;
            cout << "Cantidades: " << cantidades[i] << endl;
            cout << "=========================================" << endl;
        }
}

void Productos::AgregarProducto(){
    
    do{
        MostrarProductos();
        cout << "Ingrese el ID del producto a Comprar: ";
        cin >> idArticulo;

        while(idArticulo > 5){
            cout << "ID INVALIDO\n\n";
            cout << "Ingrese el ID del producto a Comprar: ";
            cin >> idArticulo;
        }

            // necesitamos trabajar con los indices de nuestros arreglos
        indice = idArticulo - 1;

            //validar si el ID del articulo existe
        if(indice >= 0 && indice<= 3){
            //Usamos el array siguiente y pedimos la cantidad
            cout << "Ingrese la cantidad de productos a comprar: ";
            cin >> cantidad;

                //validar la cantidad y la cantidad del inventario
            if(cantidad > cantidades[indice]){
                cout << "No hay suficientes productos" << endl;
            }else{
                // en el caso de que si tengamos productos, entonces no pasamos al siguiente array
                precio = precios[indice];
                //sacar el total de lo comprado
                total = precio * cantidad; // debe de poder agregar productos al ticket


                system("clear");
                cout << "Producto Comprado!\n\n";
                //imprimir
                cout << "=============================================================================" << endl;
                cout << "\t\tUsted ha comprado: " << productos[indice] << " x " << cantidad << endl;
                cout << "TOTAL: " << total << endl;
                cout << "\t\tGRACIAS POR SU PREFERENCIA" << endl;
                cout << "=============================================================================" << endl;
                cantidades[indice] = cantidades[indice] - cantidad;
                cantidadFinal = cantidadFinal + cantidad;
                totalFinal = totalFinal + total;
            }
        }else{
             cout << "ID del articulo " << idArticulo << " invalido " << endl;
            }
        cout << "Agregar Otro Producto? (Si = 1 / No = 0)";
        cin >> continuar;
    }while(continuar != 0);

    totalFinal  = totalFinal + (totalFinal * 0.2);
}

Productos::~Productos(){}


void Productos::Ticket_Productos(){
    // ciclo para enseñar datos
    cout << "==========================================================" << endl;
    cout << "\t\tUsted ha comprado: " << cantidadFinal << " productos" << endl;
    cout << "\t\tGRACIAS POR SU PREFERENCIA" << endl;

        if(cantidadFinal > 5 ){
            cout << "\n\nDescuento por la compra +5 productos: -10 pesos";
            totalFinal = totalFinal - 10;
        }
    cout << "\n\n\t\tTOTAL: " << totalFinal << endl;
    cout << "==========================================================" << endl;
}


#endif