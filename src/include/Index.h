/* 
 * File:   index.h
 * Author: antonio
 *
 * Created on 8 de febrero de 2012, 13:33
 */

#ifndef INDEX_H
#define	INDEX_H
#include <string>
#include <list>
#include "document.h"
#include "PorterStemmer.h"
#include "Stopper.h"
#include "Peso.h"
#include <iterator>
#include <vector>
#include <cstdio>
#include <cmath>
#include <vector>
#include "DocFrec.h"
#include "DocPeso.h"
#include "Word.h"
#include "document.h"
#include "normalize.h"
#include "WordFile.h"
#include <map>

using namespace std;

class Index {
private:
    string directory;
    list<document *> *documents;
    list<Peso*> *lPesos;
    unsigned int numDocs;
    
public:
    Index() {}
    Index(string root);
    void read();
    void stopper(const string stopperFile);
    void normalize();
    void stemmer();
    void genera_archivo_ficheros();
    void pesos(/*vdin_documentos v*/);
    int write(/*tlistadin_peso lp, int numDocs,*/ const string filename);
    virtual ~Index(); //Eliminar documentos, lista de documentos, pesos y lista de pesos.
};

#endif	/* INDEX_H */

