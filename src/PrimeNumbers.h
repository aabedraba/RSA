/*
 * File:   PrimeNumbers.h
 * Author: aabedraba
 *
 * Created on November 14, 2017, 10:34 PM
 */

#ifndef PRIMENUMBERS_H
#define PRIMENUMBERS_H

#include <vector>
#include <string>
#include <cmath>
#include <gmp.h>
#include <fstream>
#include <list>

class PrimeNumbers {
public:
    explicit PrimeNumbers( const long range );
    PrimeNumbers( const PrimeNumbers& orig ) = default;
    virtual ~PrimeNumbers( );

    const std::pair<mpz_t, mpz_t> *getPrimes( );

    void generatePrimes( const long range );
    void generateFirst168Primes( );
    bool isPrime( mpz_t *n );
    bool checksWithFirst168Primes( mpz_t *n );
    bool millerRabinsTest( mpz_t *d, mpz_t *n );

private:
    std::list<short> _first168Primes; ///First primes in the range of [2, 1000]
    std::pair<mpz_t, mpz_t> _primes;
};

#endif /* PRIMENUMBERS_H */

