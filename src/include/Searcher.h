/* 
 * File:   searcher.h
 * Author: antonio
 *
 * Created on 10 de febrero de 2012, 13:48
 */

#ifndef SEARCHER_H
#define	SEARCHER_H
#include <string>
#include <list>
#include <vector>
#include "Result.h"
#include "Similarity.h"
#include "DocPeso.h"
#include "Stopper.h"
#include "normalize.h"
#include "PorterStemmer.h"
#include "Peso.h"

#include <map>

using namespace std;

class Searcher {
private:
    //string searchStr;
    string consult;
    string originalConsult;
    list<Result> results;
    int numDocs;

    //map<Peso> *index;
    map<string, list<DocPeso>*> *index;
    vector<string> ids;
    list<Similarity> similarities;

    list<DocPeso>* extractPeso(const string word);
    int obtiene_titulo_frase(const char *filename, char **title, char **frase, const char *consulta);
public:
    Searcher();
    //3º
    void stopper(const string stopperFile);
    //4º
    void normalize();
    //5º
    void stemmer();
    //2º
    void extractConsults(const string filename) { }
    void setConsult(const string cons) { consult=cons; originalConsult=cons; }
    //Searcher(const Searcher& orig);
    //8º
    void writeResults(const string resultsFileName, int numDocsRel);
    //6º
    void cargaColeccion(const string filename);
    //1º
    void loadIndex(const string filename);
    virtual ~Searcher();
    //7º
    void calculateSimilarity(const string consulta);
};

#endif	/* SEARCHER_H */

