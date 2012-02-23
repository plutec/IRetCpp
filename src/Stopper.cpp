/* 
 * File:   stopper.cpp
 * Author: Antonio Sánchez Perea
 * 
 * Created on 9 de febrero de 2012, 0:12
 */

#include <list>

#include "include/Stopper.h"

Stopper::Stopper(const string stopperFile) {
    char str[128];
    char *toInsert;
    FILE *fd;
    //Creamos el AVL con la lista de palabras vacías
    //stopperList=new map<string, string>();//toRet=avl_string_crea();
    if (!(fd=fopen(stopperFile.c_str(),"rt"))) {
        cout << "create_stopper_list: No se puede abrir el archivo de palabras vacías."<<endl;
        //TODO depuración
    }
    while(!feof(fd)) {
        //TODO hacer la lectura de palabras más eficiente
        fgets(str,127,fd);
        toInsert=(char*)malloc((strlen(str)-1)*sizeof(char));
        strncpy(toInsert, str, strlen(str)-2);
        toInsert[strlen(str)-2]='\0';
        stopperList[toInsert]=toInsert;//avl_string_mete(&toRet, toInsert, comp_string);
    }
    //return toRet;
    
}

string Stopper::eliminate_null_words(const string str) {
    list<string> *separate;
    char *strMod;//, *toRet, *word, *aux;
    string toRet;
    //int i,tam;
    //Como a splitString hay que pasarle un char *, hacemos una copia de la cadena para poder modificarla
    //strMod=(char*)malloc((strlen(str)+2)*sizeof(char));
    strMod=(char*)malloc((str.size()+2)*sizeof(char));
    strcpy(strMod, str.c_str());

    separate=utils::splitString(strMod, " ");

    //tam=vdin_strings_tama(separate);
    list<string>::iterator itr;
    for(itr=separate->begin();itr!=separate->end();itr++) {
        //word=vdin_strings_obtiene(separate, i);
        if (stopperList.find(*itr)==stopperList.end()) { //No ha encontrado la cadena en el AVL, quiere decir que no es palabra vacía
        //if (avl_string_busca(a, word, comp_string)!=1) { //No ha encontrado la cadena en el AVL, quiere decir que no es palabra vacía
            //strcat(toRet, (*itr).c_str());
            //strcat(toRet, " ");
            toRet+=*itr+" ";
        }
    }
    //Redimensionamos para no ocupar memoria innecesaria.
    //No utilizamos realloc porque da fallo de memoria.
    //tam=strlen(toRet)+1;
    //aux=(char*)malloc(tam*sizeof(char));
    //memcpy(aux, toRet, tam);

    free(strMod);
    //toRet=aux;
    //delete separate;
    return toRet;
}

/**
 * Nos indica si una palabra pertenece a las vacías o no.
 * @param word palabra a comprobar
 * @return true si es palabra vacía, false en caso contrario.
 */
bool Stopper::nullWord(string word) {
    if (stopperList.find(word)==stopperList.end()) { //No ha encontrado la cadena en el AVL, quiere decir que no es palabra vacía
        return false;
    }
    return true;
}

Stopper::~Stopper() {
    //delete stopperList;
}

