/* 
 * File:   main.cpp
 * Author: Antonio Sánchez Perea
 *
 * Created on 8 de febrero de 2012, 12:03
 */

#include <cstdlib>

#include "include/Index.h"
#include "include/Searcher.h"

using namespace std;

int indexer(int argc, char** argv) {
    //Definición de variables
    int num;
    // Lectura de parámetros
    if (argc<3) {
        cout << "Número de parámetros incorrecto." <<endl;
        cout << argv[0] << " directorio_coleccion fichero_indice fichero_stopper"<<endl;
        return 0;
    }
    //Creamos el índice
    Index *ind=new Index(argv[1]);
    //Lectura de documentos
    cout << "Cargando colección"<<endl;
    ind->read();
    cout << "Cargada colección"<<endl;
    //Stopper!
    cout << "Pasando Stopper"<<endl;
    ind->stopper(argv[3]);
    cout << "Stopper realizado. Normalizando"<<endl;
    //Normalización
    ind->normalize();
    cout << "Normalizado completado. Obteniendo raíces"<<endl;
    //Stemmer
    ind->stemmer();
    cout << "Obtención de raíces completada."<<endl;
    cout << "Calculando pesos de las palabras"<<endl;
    ind->pesos();
    printf("Generando archivo de índice\n");
    num=ind->write(argv[2]);//ai_indice_escribeIndice(listaPesos, numDocs, argv[2]);//"index.ind");
    //Finalizamos
    cout << "Se han escrito "<<num<<" palabras en el archivo de índice"<<endl;
    cout << "Pulse una tecla para terminar"<<endl;
    getchar();
    return 0;
}

int searcher(int argc, char** argv) {
    //Parámetros:
    //Primer parámetro, cadena que indica dónde está el índice. argv[1]
    //Segundo parámetro, cadena que indica dónde está el archivo consulta. argv[2]
    //Tercer parámetro, número de documentos relevantes que se devolverán. argv[3]
    //Declaraciones
    //avl_peso palabras;
    Searcher search;//=new Searcher();
    //Index ind=new Index();
    int numDocs, numDocsRelevantes;
   // int i, tam;
    //FILE *fdResul;
    //vdin_strings consultas, consultas_originales;
    //vdin_strings docFile;
    //vdin_similitud sim;
    //Comprobación de número de parámetros.
    if (argc<3) {
        printf("Número de parámetros incorrecto.\n");
        printf("%s tipo archivo_indice.ind \"consulta\" numDocsRelevantes\n",argv[0]);
        return 1;
    }
    numDocsRelevantes=atoi(argv[3]);

    //Cargamos el índice
    //palabras=ai_buscador_carga(&numDocs, argv[1]); //"index.ind");
    search.loadIndex(argv[1]);
    //Cargamos las consultas
    //consultas=ai_buscador_consultas(argv[2]); //"consultas.txt");
    //search->extractConsults(argv[2]);
    search.setConsult(argv[2]);
    //consultas_originales=vdin_strings_copia(consultas); //Para tenerlas a la hora de mostrarlas
    //ai_buscador_stopper(consultas, "englishST.txt");
    search.stopper("englishST.txt");
    //ai_buscador_normaliza(consultas);
    search.normalize();
    //ai_buscador_stemmer(consultas);
    search.stemmer();
    //Cargamos el archivo con los pares ID, doc.
    //docFile=ai_buscador_cargaColeccion("ids.txt");
    search.cargaColeccion("ids.txt");
    //Calculamos los documentos similares
    search.calculateSimilarity(argv[2]);
    search.writeResults("resultado.txt", numDocsRelevantes);

    printf("Se ha generado el archivo resultado.txt con la consulta seleccionada\n");

    return (EXIT_SUCCESS);
}
/*
 * 
 */
int main(int argc, char** argv) {
    // Lectura de parámetros
    if (argc<1) {
        cout << argv[0] << " (1,2)(Indexer, Searcher)"<<endl;
        return 1;
    }
    if (atoi(argv[1])==1) {
        return indexer(argc-1, argv+1);
    } else {
        return searcher(argc-1, argv+1);
    }
    return 1;
}

