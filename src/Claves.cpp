//
// Created by aabedraba on 17/12/17.
//

#include "Claves.h"

Claves::Claves( NumerosPrimos &primos ) {
    mpz_inits ( _d, _n ); // inicializando números de multi precisión
    mpz_init_set ( _p, primos.getPrimos().first );
    mpz_init_set ( _q, primos.getPrimos().second );
    mpz_init_set_ui ( _e, 65537 ); //primo de Fermat
    crearClavePublica();
    crearClavePrivada();
}

void Claves::crearClavePublica() {
    // n = p*q
    // e = 65537
    mpz_set ( _n, _p );
    mpz_mul ( _n, _n, _q );
    mpz_set ( _clavePublica.first, _n );
    mpz_set ( _clavePublica.second, _e );
}

void Claves::crearClavePrivada( ) {
    // d = e^-1 mod ((p-1)*(q-1))
    // e = 65537
    mpz_t carmichael; mpz_init(carmichael);
    mpz_sub_ui( _p, _p, 1 );
    mpz_sub_ui( _q, _q, 1 );
    mpz_mul( carmichael, _p, _q ); // carmichael = (p-1)*(q-1) (Robert Daniel Carmichael <3)
    mpz_invert( _d, _e, carmichael );
    mpz_set ( _clavePrivada.first, _d );
    mpz_set ( _clavePrivada.second, _e);
}

const std::pair<mpz_t, mpz_t> &Claves::get_clavePublica( ) const {
    return _clavePublica;
}

const std::pair<mpz_t, mpz_t> &Claves::get_clavePrivada( ) const {
    return _clavePrivada;
}

//FUTURE IMPLEMENTATION (maybe), GMP no soporta funciones recursivas :(
//mpz_t Claves::modInversa( mpz_t &a, mpz_t &b ) {
//    mpz_t x, y, resultado;
//    mpz_inits( x, y, resultado );
//    metodoEuclides( a, b, x, y ); //recursivo
//    mpz_t res = (x%b + b) % b; // ..+b para números negativos
//    return res;
//}
//
//mpz_t Claves::metodoEuclides( mpz_t a, mpz_t b, mpz_t &x, mpz_t &y ) {
//    mpz_t aux1, aux2; // para guardar resultados
//    mpz_t mcd; // máximo común divisor
//    mpz_inits( aux1, aux2, mcd );
//    mpz_mod( b, a, b );
//    mpz_set ( mcd, metodoEuclides( b, a, aux1, aux2 ) );
//
//    mpz_div( b, b, a );
//    mpz_mul( b, b, aux1 );
//    mpz_sub( x, aux2, b );
//    mpz_set( y, aux1 );
//}
