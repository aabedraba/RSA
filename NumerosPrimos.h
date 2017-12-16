/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   NumerosPrimos.h
 * Author: aabedraba
 *
 * Created on November 14, 2017, 10:34 PM
 */

#ifndef NUMEROSPRIMOS_H
#define NUMEROSPRIMOS_H

#include <vector>
#include <cmath>
#include <string>
#include <list>
#include <gmp.h>

class NumerosPrimos {
public:
    explicit NumerosPrimos( const long rango );
    NumerosPrimos( const NumerosPrimos& orig ) = default;
    virtual ~NumerosPrimos( ) = default;

    void primosHastaElMil();

    void generaPrimos( const long rango );
    std::pair<mpz_t, mpz_t> getPrimos() const;
    bool esPrimo( mpz_t &n );
    bool compruebaLosPrimerosMil( mpz_t& n );
    bool testMillerRabin( mpz_t d, mpz_t &n );
private:
    std::list<short> _primerosMil; ///Los primeros números primos en el rango de [2,1000)
    std::pair<mpz_t, mpz_t> _primos; ///Par de primos generados
};

#endif /* NUMEROSPRIMOS_H */

