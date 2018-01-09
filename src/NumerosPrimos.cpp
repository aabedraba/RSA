/*
 * File:   NumerosPrimos.cpp
 * Author: aabedraba
 *
 * Created on November 14, 2017, 10:34 PM
 */

#include "NumerosPrimos.h"

NumerosPrimos::NumerosPrimos(const long rango)
    : _primerosMil()
{
    primosHastaElMil(); //genera los primeros primos hasta el  mil (168 primos)
    mpz_inits(_primos.first, _primos.second); //inicializa los primos
    generaPrimos( rango );
}

/**
 * @brief Genera dos números primos en el rango de 2^(rango-1) y 2^rango-1
 * @param rango const long, exponente a elevar el rango
 * @post dos números primos en el par de variables _primos
 */
void NumerosPrimos::generaPrimos( const long rango ) {
    gmp_randstate_t state1; gmp_randinit_mt(state1); // inicializador de Merssene-Twister, con buenas propiedas de pseudoaleatoriedad
    gmp_randstate_t state2; gmp_randinit_default( state2 ); // utilizando inicializadores distintos
    mpz_rrandomb( _primos.first, state1, rango);
    mpz_rrandomb( _primos.second, state2, rango+1);

    if ( mpz_fdiv_ui(_primos.first, 2) == 0 ) mpz_sub_ui(_primos.first, _primos.first, 1); // _primos.first--; convirtiendo a impar
    if ( mpz_fdiv_ui(_primos.second, 2) == 0 ) mpz_sub_ui(_primos.second, _primos.second, 1); // _primos.second--; convirtiendo a impar

    while ( !esPrimo( _primos.first ) ) mpz_add_ui( _primos.first, _primos.first, 2 ); // _primos.first+=2
    while ( !esPrimo( _primos.second ) ) mpz_add_ui( _primos.second, _primos.second, 2 ); // _primos.second+=2
}

/**
 * Comprueba si un número es primo o no. Primero prueba si está compuesto por lo mil primeros primos
 * en caso contrario, itera con el test de primalidad de Miller-Rabin durante 10 veces.
 * @param n mpz_t, número a comprobar
 * @return true, si es primo. false, si es compuesto.
 */
bool NumerosPrimos::esPrimo(mpz_t &n) {
    //Comprueba con los primeros mil
    if ( !compruebaLosPrimerosMil( n ) ) return false;

    //Comprueba con el test de primalidad Miller-Rabin
    //Preparatorios para la función
    //n = (2^d)*s + 1
    mpz_t d;
    mpz_init_set(d, n);
    mpz_sub_ui(d, d, 1);
    while ( mpz_fdiv_ui(d, 2) == 0 ) // d%2 == 0
        mpz_div_ui(d, d, 2);

    int numeroDeIteraciones = 10; //número de iteraciones para el test de Miller-Rabin
    for (int i = 0; i < numeroDeIteraciones; ++i)
        if ( !testMillerRabin(d, n) ) return false;
    return true;
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
 * @param n mpz_t, número que queremos comprobar
 * @return true, si no es compuesto por los primeros primos hasta el mil. false, si es compuesto.
 */
bool NumerosPrimos::compruebaLosPrimerosMil( mpz_t& n ) {
    auto iter = _primerosMil.begin();

    while ( iter != _primerosMil.end() )
        if ( mpz_fdiv_ui(n, (*iter++) ) == 0) return false;

    return true;
}

/**
 * Utiliza el algoritmo de Miller-Rabin para comprobar que un número es o no primo
 * @param d mpz_t, del algoritmo, n = (2^d)*s + 1
 * @param n mpz_t, número a comprobar
 * @return true, posiblemente primo. false, compuesto.
 */
bool NumerosPrimos::testMillerRabin(mpz_t d, mpz_t &n) {
    mpz_t a; mpz_init(a);
    mpz_t aux; mpz_init(aux);
    mpz_t aux2; mpz_init(aux2);

    // a = 2 + rand() % (n - 4);
    // Escoger a entre [2..n-2] para evitar casos límites
    gmp_randstate_t estado; gmp_randinit_default(estado);
    mpz_set (a, n);
    mpz_sub_ui(a, a, 4);
    mpz_urandomm( aux, estado, a); // aux = rand % (n-4)
    mpz_add_ui(a, aux, 2); // a = 2 + aux

    // aux = a^d % n
    mpz_powm(aux, a, d, n);

    // aux == 1 || aux == n-1
    mpz_sub_ui(aux2, n, 1); //aux2 = n-1
    int comparacion1 = mpz_cmp_ui(aux, 1); //cero si verdadero
    int comparacion2 = mpz_cmp(aux, aux2); //cero si verdadero
    if ( comparacion1==0 || comparacion2==0 )
        return true;

    // Repetir hasta
    // (i) d != n-1
    // (ii)  (x^2) % n != 1
    // (iii) (x^2) % n != n-1
    while ( mpz_cmp(aux2, d) != 0 ){ // d != aux2(n-1)
        mpz_powm_ui(aux, aux, 2, n); // aux = aux*aux % n
        mpz_mul_ui(d, d, 2); // d*=2

        if ( mpz_cmp_ui(aux, 1) == 0 ) { //x == 1
//            mpz_clears(a, aux, aux2, estado );
            return false; //compuesto
        }
        if ( mpz_cmp(aux, aux2) == 0 ) {//x == n-1
//            mpz_clears(a, aux, aux2, estado );
            return true; //posible primo
        }
    }
    // devuelve compuesto
//    mpz_clears(a, aux, aux2, estado );
    return false;
}

std::pair<mpz_t, mpz_t> NumerosPrimos::getPrimos() const {
    return _primos;
}
