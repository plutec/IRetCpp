/* 
 * File:   Peso.h
 * Author: antonio
 *
 * Created on 9 de febrero de 2012, 13:09
 */

#ifndef PESO_H
#define	PESO_H
#include <string>
#include <list>
#include "DocPeso.h"

using namespace std;

class Peso {
private:
    string palabra;
    list<DocPeso> *pesos;
    list<DocPeso>::iterator itr;
public:
    Peso();
    //Peso(const Peso& orig);
    virtual ~Peso();
    void setPalabra(string p) { palabra=p; }
    void insertDocPeso(DocPeso dp) { pesos->push_back(dp); }
    string getPalabra() { return palabra; }
    void startIterator() { itr=pesos->begin(); }
    bool endIterator() { if (itr==pesos->end()) { return true; } return false; }
    DocPeso valueIterator() { return *itr; }
    void nextIterator() { itr++; }
};

#endif	/* PESO_H */

