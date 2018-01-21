#include <iostream>
#include <gmp.h>
#include "PrimeNumbers.h"
#include "Keys.h"
using namespace std;

int main() {
    PrimeNumbers primos( 512 );
    cout << "Primer primo: " << primos.getPrimes( )->first << endl;
    cout << "Segundo primo: " << primos.getPrimes( )->second << endl;
    cout << "\n" << endl;

    Keys claves( primos );
    pair<mpz_t, mpz_t> publica = claves.get_publicKey( );
    pair<mpz_t, mpz_t> privado = claves.get_privateKey( );

    cout << "Clave Pública: (" << std::hex << publica.first << ", " << std::hex << publica.second << ")" << endl;
    cout << "Clave Privada: (" << std::hex << privado.first << ", " << std::hex << privado.second << ")" << endl;
    cout << "\n" << endl;

    int numero;
    cout << "Introduzca un número: ";
    cin >> numero;

    mpz_t cifrado; mpz_init_set_ui(cifrado, numero);
    mpz_t descifrado; mpz_init( descifrado );

    mpz_powm( cifrado, cifrado, publica.first, publica.second);
    cout << "Número cifrado: " << endl;
    cout << std::hex << cifrado << endl;

    mpz_powm ( descifrado, cifrado, privado.first, publica.second);
    cout << "Número descifrado: " << endl;
    cout << std::dec << descifrado << endl;

    mpz_clears( cifrado, descifrado, NULL);

    return 0;
}
