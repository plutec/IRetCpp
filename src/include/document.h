/* 
 * File:   Document.h
 * Author: Antonio Sánchez Perea
 * Email: asanchez@plutec.net
 *
 * Created on 8 de febrero de 2012, 13:18
 */

#ifndef DOCUMENT_H
#define	DOCUMENT_H
#include <iostream>
#include <string>

using namespace std;
class document {
private:
    string filename;
    string id;
    int idNumber;
    //vdin_strings tags;
    string tags;
    //vdin_strings cat;
    string cat;
    string title;
    string original_text;
    string normalized;
    string stopper;
    string stemmer;
    string processed;
public:
    document();
    document(const document& orig);
    void setId(string str) { id=str; }
    string getId() { return id; }
    void setTitle(string str) { title=str; }
    void setOriginal(string str) { original_text=str; }
    void setFilename(const string str) { filename=str; }
    string getFilename() { return filename; }
    int getIdNumber() { return idNumber; }
    void setIdNumber(int num) { idNumber=num; }
    string getCat() { return cat; }
    void setCat(string str) { cat=str; }
    string getTags() { return tags; }
    void setTags(string str) { tags=str; }
    void setNormalized(string str) { normalized=str; }
    string getNormalized() { return normalized; }
    string getStopper() { return stopper; }
    string getOriginal() { return original_text; }
    void setStopper(string str) { stopper=str; }
    void setStemmer(string str) { stemmer=str; }
    string getStemmer() { return stemmer; }
    string getProcessed() { return processed; }
    void setProcessed(string str) { processed=str; }
    virtual ~document();
private:

};

#endif	/* DOCUMENT_H */

