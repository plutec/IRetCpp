/* 
 * File:   Word.h
 * Author: antonio
 *
 * Created on 9 de febrero de 2012, 13:20
 */

#ifndef WORD_H
#define	WORD_H

#include <string>
#include <list>
#include <iterator>
#include "DocFrec.h"

using namespace std;

class Word {
private:
    string palabra;
    list<DocFrec> *frecuencia; //Lugar + veces que aparece.
    list<DocFrec>::iterator itr;
public:
    Word();
    //Word(const Word& orig);
    virtual ~Word();
    void setPalabra(string p) { palabra=p; }
    string getPalabra() { return palabra; }
    void addDocFrec(DocFrec df) { frecuencia->push_back(df); }
    long unsigned int frecSize() { return frecuencia->size(); }
    void startIterator() { itr=frecuencia->begin(); }
    void nextIterator() { itr++; }
    DocFrec valueIterator() { return *itr; }
    bool endIterator() { if (itr==frecuencia->end()) { return true; } return false; }
    


};

#endif	/* WORD_H */

