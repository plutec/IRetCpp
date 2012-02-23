/* 
 * File:   normalize.h
 * Author: antonio
 *
 * Created on 9 de febrero de 2012, 0:44
 */

#ifndef NORMALIZE_H
#define	NORMALIZE_H
#include <string>
#include <cstring>

using namespace std;

class normalize {
private:
    static int isAcceptedChar(char c);
public:
    static string normalizeString(const string str);

};

#endif	/* NORMALIZE_H */

