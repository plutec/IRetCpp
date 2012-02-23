/* 
 * File:   Peso.cpp
 * Author: antonio
 * 
 * Created on 9 de febrero de 2012, 13:09
 */

#include "include/Peso.h"

Peso::Peso() {
    pesos=new list<DocPeso>();
}

Peso::~Peso() {
    delete pesos;
}

