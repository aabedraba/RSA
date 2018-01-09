#include <iostream>
#include <gmp.h>
#include "Claves.h"
#include "NumerosPrimos.h"
using namespace std;

int main() {
    //Aunque la generación de los números primos es correcta,
    //esto es una comprobación, usando una función de la librería
    //de GMP que calcula, de nuevo utilizando el test de Miller
    //Rabin si los números son o no primos
    int esPrimo;
    NumerosPrimos primos( 1024 );
    mpz_probab_prime_p(primos.getPrimos().first, esPrimo);
    cout << "Primer primo: " << primos.getPrimos().first << endl;
    cout << "P " << (esPrimo ? "es primo": "no es primo") << endl;
    mpz_probab_prime_p(primos.getPrimos().second, esPrimo);
    cout << "Segundo primo: " << primos.getPrimos().second << endl;
    cout << "Q " << (esPrimo ? "es primo": "no es primo") << endl;
    cout << "\n" << endl;

    Claves claves( primos );
    pair<mpz_t, mpz_t> publica = claves.get_clavePublica();
    pair<mpz_t, mpz_t> privado = claves.get_clavePrivada();

    cout << "Clave Pública: (" << std::hex << publica.first << ", " << std::hex << publica.second << ")" << endl;
    cout << "Clave Privada: (" << std::hex << privado.first << ", " << std::hex << privado.second << ")" << endl;
    cout << "\n" << endl;

    int numero;
    cout << "Introduzca un número: ";
    cin >> numero;

    mpz_t cifrado; mpz_init_set_ui(cifrado, numero);
    mpz_t descifrado; mpz_init;

    mpz_powm( cifrado, cifrado, publica.first, publica.second);
    cout << "Número cifrado: " << endl;
    cout << std::hex << cifrado << endl;

    mpz_powm ( descifrado, cifrado, privado.first, publica.second);
    cout << "Número descifrado: " << endl;
    cout << std::dec << descifrado << endl;

    mpz_clear ( cifrado );// Limpiando memoria
    mpz_clear ( descifrado );
    return 0;
}