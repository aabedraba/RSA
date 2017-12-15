#include <iostream>
#include <cstdlib>
#include <gmp.h>

using namespace std;

int main(){
    cout << RAND_MAX << endl;
    mpz_t largeNumber;
    mpz_init(largeNumber);
    mpf_t bigger;
    mpf_init(bigger);
    cout << bigger;
    return 0;

}