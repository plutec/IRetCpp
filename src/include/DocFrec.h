/* 
 * File:   DocFrec.h
 * Author: antonio
 *
 * Created on 9 de febrero de 2012, 13:21
 */

#ifndef DOCFREC_H
#define	DOCFREC_H

class DocFrec {
private:
    int idDoc;
    int frec;
public:
    DocFrec();
    DocFrec(const DocFrec& orig);
    virtual ~DocFrec();
    void setIdDoc(int d) { idDoc=d; }
    void setFrec(int f) { frec=f; }
    int getIdDoc() { return idDoc; }
    int getFrec() { return frec; }
    void aumFrec() { ++frec; }
};

#endif	/* DOCFREC_H */

