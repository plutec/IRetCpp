/* 
 * File:   normalize.cpp
 * Author: antonio
 * 
 * Created on 9 de febrero de 2012, 0:44
 */

#include "include/normalize.h"
//Private
/**
 * @brief Comprueba si es un caracter válido para realizar la normalización
 * @param c caracter a comprobar
 * @return 1 si es válido, 0 en caso contrario
 */
int normalize::isAcceptedChar(char c) {
    //(a-z)
    if ((c>96) && (c<123))
        return 1;
    //(espacio)
    if (c==32)
        return 1;
    //[A-Z]
    if ((c>64) && (c<91))
        return 1;
    //[0-9]
    if ((c>47) && (c<58))
        return 1;
    return 0;
}
//Public
/**
 * @brief Normaliza una cadena, eliminando los caracteres no permitidos de la misma.
 * @param str cadena a normalizar, no se modifica.
 * @return La cadena ya normalizada.
 */
string normalize::normalizeString(const string str) {
    string toRet;
    int i, j;
    //toRet=(char *)malloc((strlen(str)+1)*sizeof(char));
    i=0;
    j=0;
    while(str[i]!='\0') {
        if (isAcceptedChar(str[i])) {
            //toRet[j++]=str[i];
            toRet+=str[i];
        }
        ++i;
    }
    //toRet[j]='\0';
    //toRet=(char *)realloc(toRet,strlen(toRet)+1);
    return toRet;
}


