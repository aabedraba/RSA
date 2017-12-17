#include <iostream>
#include "Claves.h"
#include <sstream>

using namespace std;

void combinar( const mpz_t a, const mpz_t b, mpz_t &resultado ) {
    mpz_t contador;
    mpz_init_set_ui( contador, 1 );
    while ( mpz_cmp( contador, b) < 0 || mpz_cmp( contador, b ) == 0 ) //contador <= b
    mpz_mul_ui(contador, contador, 10);

    //a*contador + b
    mpz_mul( resultado, a, contador );
    mpz_add( resultado, resultado, b );
}

int main(){
    NumerosPrimos primos( 1024 );
    Claves claves( primos );
    mpz_t result;
    mpz_init( result );
    combinar( claves.get_clavePublica().first, claves.get_clavePublica().second, result );
    stringstream flujo;
    flujo << result;
    string resultado = flujo.str();
    string otroResultado = "6463401214262201460142975337733990392088820533943096806426069085504931027773578178639440282304582691998984982914355393933369254147028506958630973748010751037283531241064516569548181944580367653976934823988581246561795006960081213304539463352962359913417312689973569004313033660229709065297493713233451754017931596335666590206922370373736909512740326004252930488688185617582670343689958264278737708452178667450878344135498352091657842961432716167802431948070992878418193917499024564074928445026117523851987599030416183958280058439211404064796806714070740820956618443675502647925250442704926039957867791853740779164417165537";

    if ( resultado == otroResultado )
        cout << "Pushea y a dormir" << endl;

}