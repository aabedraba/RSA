//
// Created by aabedraba on 17/12/17.
//

#ifndef RSA_ENCRIPTADO_H
#define RSA_ENCRIPTADO_H

#include <gmp.h>
#include "NumerosPrimos.h"

class Claves {
public:
    Claves( NumerosPrimos &primos );
    Claves( const Claves &orig ) = default;
    virtual ~Claves();

    const std::pair<mpz_t, mpz_t> &get_clavePublica( ) const;
    const std::pair<mpz_t, mpz_t> &get_clavePrivada( ) const;

private:
    void crearClavePublica();
    void crearClavePrivada();
//    mpz_t modInversa( mpz_t &a, mpz_t &b );
//    mpz_t metodoEuclides ( mpz_t a, mpz_t b, mpz_t &x, mpz_t &y);

private:
    // clave pública (n, e)
    // clabe privada (d, e)
    mpz_t _p, _q; //par de primos
    mpz_t _n, _d, _e;
    std::pair<mpz_t, mpz_t> _clavePublica;
    std::pair<mpz_t, mpz_t> _clavePrivada;

};


#endif //RSA_ENCRIPTADO_H
