/* 
 * File:   Similarity.h
 * Author: antonio
 *
 * Created on 12 de febrero de 2012, 19:41
 */

#ifndef SIMILARITY_H
#define	SIMILARITY_H

class Similarity {
private:
    int idDoc;
    double similitud;
public:
    Similarity() {}
    //Similarity(const Similarity& orig);
    void setIdDoc(int id) { idDoc=id; }
    void setSimilarity(double s) { similitud=s; }
    int getIdDoc() { return idDoc; }
    double getSimilarity() { return similitud; }
    void incrSimilarity(double val) { similitud+=val; }
    bool static comp(Similarity s1, Similarity s2);
    //virtual ~Similarity();
private:

};

#endif	/* SIMILARITY_H */

