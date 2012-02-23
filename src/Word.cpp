/* 
 * File:   Word.cpp
 * Author: antonio
 * 
 * Created on 9 de febrero de 2012, 13:20
 */

#include "include/Word.h"

Word::Word() {
    frecuencia=new list<DocFrec>();
}

Word::~Word() {
    delete frecuencia;
}

