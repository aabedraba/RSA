#include <iostream>
#include <gmp.h>

using namespace std;

bool testMillerRabin(mpz_t d, mpz_t &n) {

}




int main(){
    mpz_t posiblePrimo;
    for (int i = 5; i < 1000; ++i) {
        mpz_init_set_ui(posiblePrimo, i);
        bool ehPrimo = esPrimo(posiblePrimo);
        if ( ehPrimo )
            cout << i << endl;
    }


    return 0;
}