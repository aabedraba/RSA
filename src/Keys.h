//
// Created by aabedraba on 17/12/17.
//

#ifndef RSA_ENCRIPTADO_H
#define RSA_ENCRIPTADO_H

#include <gmp.h>
#include "PrimeNumbers.h"

class Keys {
public:
    Keys( PrimeNumbers &primes );
    Keys( const Keys &orig ) = default;
    virtual ~Keys();

    const std::pair<mpz_t, mpz_t> &get_publicKey( ) const;
    const std::pair<mpz_t, mpz_t> &get_privateKey( ) const;

private:
    void createPublicKey( );
    void createPrivateKey( );

private:
    const std::pair<mpz_t, mpz_t>* _primes; //primes
    mpz_t _n, _d, _e;
    std::pair<mpz_t, mpz_t> _publicKey; // public key (n, e)
    std::pair<mpz_t, mpz_t> _privateKey; // private key (d, e)

};


#endif //RSA_ENCRIPTADO_H
