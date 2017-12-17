//
// Created by aabedraba on 17/12/17.
//

#ifndef RSA_RSA_H
#define RSA_RSA_H

#include <gmp.h>

class RSA {
public:
    void combinar ( mpz_t a, mpz_t b, mpz_t &resultado );
};



#endif //RSA_RSA_H
