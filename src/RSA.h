//
// Created by aabedraba on 17/12/17.
//

#ifndef RSA_RSA_H
#define RSA_RSA_H

#include <string>
#include "NumerosPrimos.h"
#include "Claves.h"


class RSA {
public:
    RSA( int tamClaves );
    void mostrarClaves();
    std::string cifrar( std::string nomFicheroEntrada );
    void descifrar();

private:
    void combinar ( mpz_t a, mpz_t b, mpz_t &resultado );
    char* enteroAString(mpz_t x);

private:
    NumerosPrimos _primos;
    Claves _claves;
};



#endif //RSA_RSA_H
