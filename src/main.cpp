#include <iostream>
#include "NumerosPrimos.h"

using namespace std;

int main(){
    NumerosPrimos primos(100);
    cout << primos.getPrimos().first << endl;
    cout << primos.getPrimos().second << endl;
    if ( mpz_probab_prime_p(primos.getPrimos().first, 40) > 0 ) cout << "el primero es primo" << endl;
    if ( mpz_probab_prime_p(primos.getPrimos().second, 10) > 0 ) cout << "el segundo también es primo" << endl;
    return 0;
}