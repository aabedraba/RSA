//
// Created by aabedraba on 17/12/17.
//

#include <cstring>
#include "RSA.h"

RSA::RSA( int tamClaves )
    : _primos ( tamClaves ),
      _claves ( _primos )
{}

void RSA::mostrarClaves( ) {
    mpz_t result;
    mpz_init( result );
    combinar( _claves.get_publicKey( ).first, _claves.get_publicKey( ).second, result );
}

void RSA::combinar( mpz_t a, mpz_t b, mpz_t &resultado ) {
    mpz_t contador;
    mpz_init_set_ui( contador, 1 );
    while ( mpz_cmp( contador, b) < 0 || mpz_cmp( contador, b ) == 0 ) //contador <= b
        mpz_mul_ui(contador, contador, 10);

    //a*contador + b
    mpz_mul( resultado, a, contador );
    mpz_add( resultado, resultado, b );
}

std::string RSA::cifrar( std::string nomFicheroEntrada ) {
    mpz_t x, c; mpz_inits( x, c );
    mpz_t &n = _claves.get_publicKey( ).first;
    mpz_t &e = _claves.get_publicKey( ).second;

    FILE *fichero;

    fichero = std::fopen( nomFicheroEntrada.c_str(), "r" );
    mpz_inp_str(x, fichero, 10);
    std::fclose( fichero );
    mpz_powm_ui(c, x, mpz_get_ui(e), n);

    std::string ficheroDeSalida = "archivoCifrado.txt";
    std::ofstream cifrado( ficheroDeSalida.c_str() );
    fichero = fopen( ficheroDeSalida.c_str(), "w");
    mpz_inp_str(c, fichero, 10);
    fclose( fichero );
}




char* RSA::enteroAString( __mpz_struct *x ) {
    std::string str = mpz_get_str(NULL,10,x);
    char* buf;
    strcpy(buf, str.c_str());
    return buf;
}

//using byte = unsigned char ;
//
//template< typename T > std::array< byte, sizeof(T) >  to_bytes( const T& object )
//{
//    std::array< byte, sizeof(T) > bytes ;
//
//    const byte* begin = reinterpret_cast< const byte* >( std::addressof(object) ) ;
//    const byte* end = begin + sizeof(T) ;
//    std::copy( begin, end, std::begin(bytes) ) ;
//
//    return bytes ;
//}
//
//template< typename T >
//T& from_bytes( const std::array< byte, sizeof(T) >& bytes, T& object )
//{
//    // http://en.cppreference.com/w/cpp/types/is_trivially_copyable
//    static_assert( std::is_trivially_copyable<T>::value, "not a TriviallyCopyable type" ) ;
//
//    byte* begin_object = reinterpret_cast< byte* >( std::addressof(object) ) ;
//    std::copy( std::begin(bytes), std::end(bytes), begin_object ) ;
//
//    return object ;
//}
