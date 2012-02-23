/* 
 * File:   WordFile.cpp
 * Author: antonio
 * 
 * Created on 9 de febrero de 2012, 13:17
 */

#include "include/WordFile.h"

bool WordFile::comp(WordFile wf1, WordFile wf2) {
    return wf1.palabra<wf2.palabra;
}
//{ return ( int(first)<int(second) ); }

