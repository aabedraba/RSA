/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NumerosPrimos.h
 * Author: aabedraba
 *
 * Created on November 14, 2017, 10:34 PM
 */

#ifndef NUMEROSPRIMOS_H
#define NUMEROSPRIMOS_H

#include <vector>
#include <cmath>
#include <string>
#include <list>

class NumerosPrimos {
public:
    NumerosPrimos( const long rango );
    NumerosPrimos( const NumerosPrimos& orig ) = default;
    virtual ~NumerosPrimos( ) = default;
    
    void primosHastaElMil();

    NumerosPrimos(const std::list<int> &_primerosMil);

    void generaPrimos();
    bool compruebaLosPrimerosMil( int& posiblePrimo );
    bool testMillerRabin( int& posiblePrimo );
    std::pair<long, long> getPrimos() const;
private:
    std::list<int> _primerosMil; ///Los primeros números primos en el rango de [2,1000)
};

#endif /* NUMEROSPRIMOS_H */

