/* 
 * File:   NumerosPrimos.cpp
 * Author: aabedraba
 * 
 * Created on November 14, 2017, 10:34 PM
 */

#include <fstream>

#include "NumerosPrimos.h"

NumerosPrimos::NumerosPrimos(const long rango)
    : _primerosMil()
{
    primosHastaElMil(); //genera los primeros primos hasta el  mil (168 primos)
}

void NumerosPrimos::generaPrimos() {

}

/**
 * @brief Usando el método de la Criba de Eratóstenes, crea una lista con los primeros primos comprendidos entre
 * 0 y mil. Esta lista es necesaria ya que 90% de los números compuestos mayores que mil son compuestos por primos
 * que perteneces a esta lista. Por lo tanto, comprobando que el número que yo tenga no sea compuesto por cualquiera
 * de los que perteneces a esta lista, tengo una probabilidad del 90% de que no sea primo.
 * @post La lista _primerosMil contiene los primeros mil hasta el 100.
 */
void NumerosPrimos::primosHastaElMil() {
    //Implementación de la Criba de Eratóstenes
    std::vector<bool> v(1000, true); //vector de los mil primeros números sin tachar (true)
    for (short i = 2; i < v.size(); i++) {
        if (v[i] == true) {
            if (i * 2 > v.size()) break; //ya no hay más múltiplos en el vector que tachar
            for (short j = 2, aux = i * j; aux < v.size(); ++j, aux = i * j) //tachamos los mútliplos
                v[aux] = false;
        }
    }
    for (short i = 2; i < v.size(); i++)
        if (v[i] == true) //si no esta tachado
            _primerosMil.push_back(i);
}

/**
 * @brief Comprueba que el número que se pasa como argumento no sea un compuesto por la lista de los primeros primos
 * hasta el mil.
 * @param posiblePrimo int, número que queremos comprobar
 * @return true, si no es compuesto por los primeros primos hasta el mil. false, si es compuesto.
 */
bool NumerosPrimos::compruebaLosPrimerosMil( int& posiblePrimo ) {
    auto iter = _primerosMil.begin();
    for (;  iter != _primerosMil.end(); iter++)
        if ( posiblePrimo % *iter ==0 ) return false;
    return true;
}


bool testMillerRabin( mpz_t &posiblePrimo ){
//    int numDeIteraciones = 10; //Número de veces que aplicamos el algoritmo de Miller-Rabin
//    //Algoritmo de Miller-Rabin
//    //n = (2^d)*s + 1
//    //0 < a < n-1
//    int num = 1;
//    mpz_t d;
//    mpz_set(d, mpz_sub_ui(posiblePrimo,posiblePrimo,num));
//    while (d % 2 == 0) d /= 2;
//    int a = 2 + rand() % (posiblePrimo - 4);

}
