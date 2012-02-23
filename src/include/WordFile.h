/* 
 * File:   WordFile.h
 * Author: antonio
 *
 * Created on 9 de febrero de 2012, 13:17
 */

#ifndef WORDFILE_H
#define	WORDFILE_H
#include <string>
using namespace std;

class WordFile {
private:
    string palabra;
    int file;
public:
    void setPalabra(string p) { palabra=p; }
    void setFile(int f) { file=f; }
    string getPalabra() { return palabra; }
    int getFile() { return file; }
    static bool comp (WordFile wf1, WordFile wf2);

};

#endif	/* WORDFILE_H */

