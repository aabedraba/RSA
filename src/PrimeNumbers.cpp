/*
 * File:   NumerosPrimos.cpp
 * Author: aabedraba
 *
 * Created on November 14, 2017, 10:34 PM
 */

#include "PrimeNumbers.h"

PrimeNumbers::PrimeNumbers(const long range)
    : _first168Primes()
{
    generateFirst168Primes( ); //generates prime numbers within the range [0, 1000] (168 primes)
    mpz_inits(_primes.first, _primes.second, NULL); //initialization
    generatePrimes( range );
}

PrimeNumbers::~PrimeNumbers( ) {
    mpz_clears( _primes.first, _primes.second, NULL );
}

/**
 * @brief Genera dos números primos en el rango de 2^(rango-1) y 2^rango-1
 * @param rango const long, exponente a elevar el rango
 * @post dos números primos en el par de variables _primos
 */
void PrimeNumbers::generatePrimes( const long rango ) {
    gmp_randstate_t state1; gmp_randinit_mt(state1); // Merssene-Twister initializer; good pseudo-randomness properties
    gmp_randstate_t state2; gmp_randinit_default( state2 ); // using different initializer
    mpz_rrandomb( _primes.first, state1, rango);
    mpz_rrandomb( _primes.second, state2, rango+1);

    if ( mpz_fdiv_ui(_primes.first, 2) == 0 ) // if num % 2 == 0
        mpz_sub_ui(_primes.first, _primes.first, 1); // converting to odd
    if ( mpz_fdiv_ui(_primes.second, 2) == 0 )
        mpz_sub_ui(_primes.second, _primes.second, 1);

    while ( !isPrime( _primes.first ) )
        mpz_add_ui( _primes.first, _primes.first, 2 ); // _primes.first+=2

    while ( !isPrime( _primes.second ) )
        mpz_add_ui( _primes.second, _primes.second, 2 ); // _primes.second+=2
}

/**
 * Comprueba si un número es primo o no. Primero prueba si está compuesto por lo mil primeros primos
 * en caso contrario, itera con el test de primalidad de Miller-Rabin durante 10 veces.
 * @param n mpz_t, número a comprobar
 * @return true, si es primo. false, si es compuesto.
 */
bool PrimeNumbers::isPrime( mpz_t &n ) {
    //Checks primality with the first 168 primes
    if ( !checksWithFirst168Primes( n ) ) return false;

    //Checks with Miller-Rabin's primality test
    //n = (2^d)*s + 1
    mpz_t d;
    mpz_init_set(d, n);
    mpz_sub_ui(d, d, 1); // d = n - 1
    while ( mpz_fdiv_ui(d, 2) == 0 ) // d%2 == 0
        mpz_div_ui(d, d, 2); // d/=2

    int millersTestIterations = 10;
    bool isPrime = true;
    for (int i = 0; i < millersTestIterations; ++i)
        if ( !millerRabinsTest( d, n ) ) isPrime = false;
    mpz_clear( d );
    return isPrime;
}


/**
 * @brief Usando el método de la Criba de Eratóstenes, crea una lista con los primeros primos comprendidos entre
 * 0 y mil. Esta lista es necesaria ya que 90% de los números compuestos mayores que mil son compuestos por primos
 * que perteneces a esta lista. Por lo tanto, comprobando que el número que yo tenga no sea compuesto por cualquiera
 * de los que perteneces a esta lista, tengo una probabilidad del 90% de que no sea primo.
 * @post La lista _primerosMil contiene los primeros mil hasta el 100.
 */
void PrimeNumbers::generateFirst168Primes( ) {
    std::vector<bool> v(1000, true);
    for (short i = 2; i < v.size(); i++)
        if (v[i] == true) {
            if (i * 2 > v.size()) break;
            for (short j = 2, aux = i * j; aux < v.size(); ++j, aux = i * j)
                v[aux] = false;
        }

    for (short i = 2; i < v.size(); i++)
        if (v[i] == true)
            _first168Primes.push_back(i);
}


/**
 * @brief Comprueba que el número que se pasa como argumento no sea un compuesto por la lista de los primeros primos
 * hasta el mil.
 * @param n mpz_t, número que queremos comprobar
 * @return true, si no es compuesto por los primeros primos hasta el mil. false, si es compuesto.
 */
bool PrimeNumbers::checksWithFirst168Primes( mpz_t &n ) {
    auto it = _first168Primes.begin();

    while ( it != _first168Primes.end() )
        if ( mpz_fdiv_ui(n, (*it++) ) == 0 ) return false;

    return true;
}

/**
 * Utiliza el algoritmo de Miller-Rabin para comprobar que un número es o no primo
 * @param d mpz_t, del algoritmo, n = (2^d)*s + 1
 * @param n mpz_t, número a comprobar
 * @return true, posiblemente primo. false, compuesto.
 */
bool PrimeNumbers::millerRabinsTest( mpz_t d, mpz_t &n ) {
    mpz_t a, aux, aux2;
    mpz_inits( a, aux, aux2, NULL );

    // Choose 'a' between [2..n-2] to avoid limit cases
    gmp_randstate_t state; gmp_randinit_default(state);
    mpz_set (a, n);
    mpz_sub_ui(a, a, 4);
    mpz_urandomm( aux, state, a);
    mpz_add_ui(a, aux, 2); // a = 2 + rand() % (n - 4);

    // aux = (a^d) % n
    mpz_powm(aux, a, d, n);

    mpz_sub_ui(aux2, n, 1); //aux2 = n-1
    int comparison1 = mpz_cmp_ui(aux, 1);
    int comparison2 = mpz_cmp(aux, aux2);
    if ( comparison1 == 0 || comparison2 == 0 ) {// if aux == 1 || aux == n-1
        mpz_clears( a, aux, aux2, state, NULL );
        return true;
    }

    // Repetir hasta
    // (i) d != n-1
    // (ii)  (x^2) % n != 1
    // (iii) (x^2) % n != n-1
    bool isPrime = false;
    while ( mpz_cmp(aux2, d) != 0 ){ // d != (n-1)
        mpz_powm_ui(aux, aux, 2, n); // aux = (aux*aux) % n
        mpz_mul_ui(d, d, 2); // d*=2

        if ( mpz_cmp_ui(aux, 1) == 0 ) //if x == 1
            break; //compound

        if ( mpz_cmp(aux, aux2) == 0 ) {//if x == n-1
            isPrime = true; //possible prime
            break;
        }
    }

    mpz_clears(a, aux, aux2, state, NULL );
    return isPrime;
}

const std::pair<mpz_t, mpz_t>* PrimeNumbers::getPrimes( ) {
    const std::pair<mpz_t, mpz_t> *primes = &_primes;
    return primes;
}

