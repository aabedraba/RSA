//
// Created by aabedraba on 17/12/17.
//

#include "RSA.h"

void RSA::combinar( mpz_t a, mpz_t b, mpz_t &resultado ) {
        mpz_t contador;
        mpz_init_set_ui( contador, 1 );
        while ( mpz_cmp( contador, b) < 0 || mpz_cmp( contador, b ) == 0 ) //contador <= b
            mpz_mul_ui(contador, contador, 10);

        //a*contador + b
        mpz_mul( resultado, a, contador );
        mpz_add( resultado, resultado, b );
}