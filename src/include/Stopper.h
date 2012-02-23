/* 
 * File:   stopper.h
 * Author: Antonio Sánchez Perea
 *
 * Created on 9 de febrero de 2012, 0:12
 */

#ifndef STOPPER_H
#define	STOPPER_H
#include <string>
#include <map>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "utils.h"

using namespace std;

class Stopper {
private:
    map<string, string> stopperList;
public:
    Stopper() { }
    Stopper(const string stopperFile);
    string eliminate_null_words(const string str);
    bool nullWord(string word);
    virtual ~Stopper();
private:

};

#endif	/* STOPPER_H */

