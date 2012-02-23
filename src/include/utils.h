/* 
 * File:   utils.h
 * Author: antonio
 *
 * Created on 8 de febrero de 2012, 13:55
 */

#ifndef UTILS_H
#define	UTILS_H
//Para listar directorio
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//Fin listar direct.
#include <string>
#include <list>
#include <cstdio>

#include "document.h"

using namespace std;

class utils {
public:

    utils();
    utils(const utils& orig);
    virtual ~utils();
    static list<string> getFilesFromDirectory(const string path);
    static list<string> *splitString(const char *str, const char *tokens);
    static int _readFile(const string file, document *doc, int idNumber);
    static const char *strstrci (const char *haystack, const char *needle);
private:

};

#endif	/* UTILS_H */

