/* 
 * File:   Similarity.cpp
 * Author: antonio
 * 
 * Created on 12 de febrero de 2012, 19:41
 */

#include "include/Similarity.h"

bool Similarity::comp(Similarity s1, Similarity s2) {
    if (s1.similitud>=s2.similitud)
        return true;
    return false;
}
/*Similarity::Similarity() {
}

Similarity::Similarity(const Similarity& orig) {
}

Similarity::~Similarity() {
}*/

