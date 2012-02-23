/* 
 * File:   DocPeso.h
 * Author: antonio
 *
 * Created on 9 de febrero de 2012, 13:11
 */

#ifndef DOCPESO_H
#define	DOCPESO_H

class DocPeso {
private:
    int doc;
    double peso;
public:
    DocPeso();
    DocPeso(const DocPeso& orig);
    virtual ~DocPeso();
    void setDoc(int d) { doc=d; }
    void setPeso(double p) { peso=p; }
    int getDoc() { return doc; }
    double getPeso() { return peso; }
};

#endif	/* DOCPESO_H */

