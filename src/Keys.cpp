//
// Created by aabedraba on 17/12/17.
//

#include "Keys.h"

Keys::Keys( PrimeNumbers &primes ) {
    mpz_inits( _d, _n, NULL ); //initializing GMP variables
    mpz_init_set_ui( _e, 65537 ); //Fermat's prime, binary is 10001; very efficient for arithmetic operations
    _primes = primes.getPrimes( );

    createPublicKey( );
    createPrivateKey( );
}

Keys::~Keys( ) {
    _primes = 0;
    mpz_clears( _n, _d, _e, NULL );
}

void Keys::createPublicKey( ) {
    mpz_mul( _n, _primes->first, _primes->second );
    mpz_set( _publicKey.first, _e ); // e = 65537
    mpz_set( _publicKey.second, _n ); // n = p*q
}

void Keys::createPrivateKey( ) {
    mpz_t carmichael, p1, q1;
    mpz_inits( carmichael, p1, q1, NULL );
    mpz_sub_ui( p1, _primes->first, 1 ); // p1 = p - 1
    mpz_sub_ui( q1, _primes->second, 1 ); // q1 = q - 1
    mpz_mul( carmichael, p1, q1 ); // carmichael = (p1*q1) (Robert Daniel Carmichael <3)
    mpz_invert( _d, _e, carmichael ); // d = (e^-1 mod carmichael)
    mpz_set( _privateKey.first, _d );
    mpz_set( _privateKey.second, _n );

    mpz_clears( carmichael, p1, q1, NULL ); //freeing memory
}

const std::pair<mpz_t, mpz_t> &Keys::get_publicKey( ) const {
    return _publicKey;
}

const std::pair<mpz_t, mpz_t> &Keys::get_privateKey( ) const {
    return _privateKey;
}
