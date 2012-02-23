/* 
 * File:   Results.h
 * Author: antonio
 *
 * Created on 12 de febrero de 2012, 18:59
 */

#ifndef RESULTS_H
#define	RESULTS_H
#include <string>

using namespace std;

class Result {
private:
    int documentID;
    string document;
    double relevancia;
    string resumen;
public:
    Result() {}
    //Result(const Result& orig);
    void setDocumentID(int i) { documentID=i; }
    void setDocument(string d) { document=d; }
    void setRelevancia(double r) { relevancia=r; }
    void setResumen(string r) { resumen=r; }
    int getDocumentID() { return documentID; }
    string getDocument() { return document; }
    double getRelevancia() { return relevancia; }
    string getResumen() { return resumen; }
    //virtual ~Result();
};

#endif	/* RESULTS_H */

