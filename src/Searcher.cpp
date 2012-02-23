/* 
 * File:   searcher.cpp
 * Author: antonio
 * 
 * Created on 10 de febrero de 2012, 13:48
 */

#include <list>

#include "include/Searcher.h"

Searcher::Searcher() {
}

/**
 * @brief Elimina las palabras vacías de las cadenas dadas como parámetro.
 * @param v Vector de cadenas objetivo.
 * @param stopperFile Fichero que contiene las palabras vacías. Una por línea.
 */
void Searcher::stopper(const string stopperFile) {
    //vdin_documentos toRet;
    Stopper *stp;
    list<string> *splitted;
    //Creamos el Stopper con la lista de palabras vacías
    stp=new Stopper(stopperFile);
    //Ahora para cada una de las palabras, comprobamos si existe alguna palabra vacía.
    splitted=utils::splitString(consult.c_str(), " ");
    list<string>::iterator itr=splitted->begin();
    while(itr!=splitted->end()) {
        if (stp->nullWord(*itr)) { //Es palabra vacía, la eliminamos de la lista
            splitted->erase(itr);
        } else {
            itr++;
        }
    }
    //Destruimos el Stopper
    delete stp;
}

/**
 * @brief Normaliza cada una de las cadenas dadas como parámetro. Elimina todo caracter que no sea [a-zA-Z0-9] y espacio.
 * @param v vector de cadenas a normalizar.
 */
void Searcher::normalize() {
    //Normalizamos textos de las cadenas
    //int tam, i;
    //char *cons;
    //string ptr;
    //list<string>::iterator itr;
    //for(itr=consults.begin();itr!=consults.end();itr++) {
        //cons=*itr;//vdin_documentos_obtiene(v,i);
        consult=normalize::normalizeString(consult);
        //free(cons);
        //vdin_strings_asigna(v, ptr, i);
        //*itr=ptr;
    //}
}

/**
 * @brief Procedimiento que extrae las raíces de un conjunto de cadenas.
 * @param v vector de cadenas del que extraer las raíces.
 */
void Searcher::stemmer() {
    //int i;
    //char *ptr;
    //char *cons;

    //list<string>::iterator itr;
    //for(itr=consult.begin();itr!=consult.end();itr++) {
    //for(i=0;i<vdin_strings_tama(v);++i){
        //cons=*itr;//vdin_strings_obtiene(v, i);
        consult=stemstring(consult.c_str());
        //free(cons);
        //vdin_strings_asigna(v, ptr, i);
        //consult=ptr;
    //}
}

/**
 * @brief Función que extrae de un fichero cada una de las líneas y las devuelve en un vector de cadenas.
 * @param filename Fichero objeto del parseo.
 */

/*void Searcher::extractConsults(const string filename) {
    FILE *fd;
    char str[1024];
    //char *toInsert;
    string *toInsert;
    //vdin_strings toRet;
    //toRet=vdin_strings_crea();

    if (!(fd=fopen(filename,"rt"))) {
        cout << "Searcher::extractConsults: No se puede abrir el archivo de consultas."<<endl;
        exit(-1);
    }
    //Si no lo hago así, me coge una última línea vacía.
    fgets(str,1023,fd);
    do{
        //toInsert=(char*)malloc((strlen(str))*sizeof(char));
        //strncpy(toInsert, str, strlen(str)-1);
        str[strlen(str)-1]='\0';
        toInsert=new string(str);
        consults.push_back(toInsert);
        //vdin_strings_aumd(toRet, toInsert);
        fgets(str,1023,fd);
    }while(!feof(fd));
    fclose(fd);

    list<string *>::iterator itr;
    for(itr=consults.begin();itr!=consults.end;itr++) {
        originalConsults.push_back(&(*itr));
    }
}*/

/**
 * @brief Devuelve un vector de similitudes dada una consulta.
 * @param consulta Serie de palabras con la que se calculan las similitudes.
 * @post Genera el vector de documentos similares a la consulta
 */
void Searcher::calculateSimilarity(const string consulta) {
    //vdin_similitud similitudes;
    vector<Similarity*> *vSimilarities;
    Similarity *simi;
    list<string> *splitted;
    list<DocPeso> *ldp;
    string palabra;
    DocPeso dp;

    splitted=utils::splitString(consulta.c_str(), " ");
    //Ahora el vector de similitudes
    vSimilarities=new vector<Similarity*>(numDocs, NULL); //Vector de similitudes a NULL.
    
    list<string>::iterator itr;
    for(itr=splitted->begin();itr!=splitted->end();itr++) { //Para cada palabra de la consulta
        palabra=*itr;
        //p.palabra=palabra;
        //Buscamos la palabra
        ldp=extractPeso(palabra);
        if (ldp!=NULL) {//Si la encuentra en el AVL.
            //Calculamos W=Tfc * Idfc, tomamos Tfc = 1, así que queda como sigue:
            //double lnumX=listadin_docpeso_numElem(p.pesos);
            //w=log10((double)numDocs/(double)listadin_docpeso_numElem(p.pesos))/log10(2);

            //Ahora calculamos S +=W*V (donde V es el vector de la palabra en cada documento)
            //listadin_docpeso_iter_ini (p.pesos);
            list<DocPeso>::iterator itrdp;
            itrdp=ldp->begin();
            while(itrdp!=ldp->end()) { //Para cada uno de los pesos en cada documento
                dp=*itrdp;
                simi=vSimilarities->at(dp.getDoc());
                if (simi==NULL) {
                    simi=new Similarity();
                }
                
                //*w; //Consideramos que el peso de la palabra es 1 independientemente del número de veces que se repita en la consulta.
                simi->incrSimilarity(dp.getPeso());
                //vdin_similitud_asigna(similitudes, simi, dp->doc);
                vSimilarities->assign(dp.getDoc(),simi);//[dp.getDoc()]=simi;
            }
        }
    }
    //Una vez generado, lo pasamos a lista.
    vector<Similarity*>::iterator itrv;
    for(itrv=vSimilarities->begin();itrv!=vSimilarities->end();itrv++) {
        simi=*itrv;
        if (simi!=NULL) {
            similarities.push_back(*simi);
        }
    }
    //Destruye lo que no sirve
    delete[] vSimilarities;
    //Y lo ordenamos de mayor a menor
    similarities.sort(Similarity::comp);

}

/**
 * Extrae la lista de Documentos-Peso de una palabra.
 * @param word palabra a buscar.
 * @return la lista de DocPeso correspondiente a la palabra o NULL en caso de no encontrarla.
 */
list<DocPeso>* Searcher::extractPeso(const string word) {
    map<string, list<DocPeso>*>::iterator itr=index->find(word);
    if(itr!=index->end()) {
        return (*itr).second;
    }
    return NULL;
}
/**
 * @brief Carga el archivo de referencias donde teníamos guardado el identificador y fichero asociado a este.
 * @param filename Fichero a parsear.
 */
void Searcher::cargaColeccion(const string filename) {
    FILE *fd;
    int t, tam;
    char fil[1024];
    char *ptr;
    //vdin_strings toRet;

    if (!(fd=fopen(filename.c_str(),"rt"))) {
        cout << "Index::cargaColeccion: No se puede abrir el archivo."<<endl;
    }
    //toRet=vdin_strings_crea();
    while(!feof(fd)) {
        fscanf(fd,"%s | %d", fil, &t);
        tam=strlen(fil)+1;
        //ptr=(char *)malloc(tam*sizeof(char));
        //memcpy(ptr, fil, tam);
        //vdin_strings_aumd(toRet, ptr);
        ids.push_back(fil);
    }
    //return toRet;
}

/**
 * @brief Procedimiento que escribe los resultados obtenidos tras generar la consulta.
 * @param resultsFileName nombre del fichero donde se volcarán los resultados
 * @param numDocsRel Número de documentos relevantes que se desean grabar.
 */
void Searcher::writeResults(const string resultsFileName, int numDocsRel) {
    int i,err;
    bool noMore=false;
    Similarity sim;
    char *title, *frase;
    FILE *fd;
    if (!(fd=fopen(resultsFileName.c_str(),"wt"))) {
        cout << "No se puede abrir el archivo para volcar resultados. ("<<resultsFileName<<")"<<endl;;
    }
    //Escribimos la consulta que nos han realizado.
    fprintf(fd, "%s\"\n",originalConsult.c_str());
    //Ahora escribimos los N documentos más relevantes
    i=0;
    list<Similarity>::iterator itr=similarities.begin();
    while ((i<numDocsRel) && (itr!=similarities.end())) {
        sim=*itr;//vdin_similitud_obtiene(s, i);
        if (sim.getSimilarity()>0) {
            //err=obtiene_titulo_frase(vdin_strings_obtiene(docs, sim.idDoc), &title, &frase, consulta);
            err=obtiene_titulo_frase(ids[sim.getIdDoc()].c_str(), &title, &frase, consult.c_str());
            //N - Nombre_fichero_relevante:Similitud:Titulo_documento:primera_frase
            if (err) {
                printf("Ha ocurrido un error al consultar el fichero %s\n",ids[sim.getIdDoc()].c_str());
                if ((!title) && (!frase)) {
                    fprintf(fd, "\n%d- %s:%.4lf:%s:%s\n", i+1, ids[sim.getIdDoc()].c_str(), sim.getSimilarity(), "null", "null");
                }else if(!title) {
                     fprintf(fd, "\n%d- %s:%.4lf:%s:%s\n", i+1, ids[sim.getIdDoc()].c_str(), sim.getSimilarity(), "null", frase);
                     free(frase);
                } else { //!frase
                    fprintf(fd, "\n%d- %s:%.4lf:%s:%s\n", i+1, ids[sim.getIdDoc()].c_str(), sim.getSimilarity(), title, "null");
                    free(title);
                }
            } else {
                fprintf(fd, "\n%d- %s:%.4lf:%s:%s\n", i+1, ids[sim.getIdDoc()].c_str(), sim.getSimilarity(), title, frase);
                free(title);
                free(frase);
            }
        }else {
            noMore=1;
        }
        ++i;
    }
}

/**
 * @brief Carga el índice del fichero pasado como parámetro.
 * @param filename, fichero índice.
 */
void Searcher::loadIndex(const string filename) {
    FILE *fd;
    Peso *p;
    char c;
    int doc;
    double peso;
    list<DocPeso> *ldp;
    char *pal;
    string sPal;
    int i=0, j, numElem; //numElem es el número de palabras que vamos a cargar desde el archivo.
    DocPeso dp;
    //avl_peso toRet;

    //Inicializamos
    if (!(fd=fopen(filename.c_str(), "rb"))) {
        cout << "Index::load: Error al abrir archivo para cargar el índice."<<endl;
    }
    //toRet=avl_peso_crea();
    index=new map<string, list<DocPeso>*>();
    pal=(char *)malloc(128*sizeof(char));
    fread(&numDocs, sizeof(int), 1, fd); //Leemos numDocs
    fread(&numElem, sizeof(int), 1, fd); //Leemos numElem

    //Cargamos el archivo.
    while(i<numElem){
        c='a';
        j=0;
        while (c!='\0') {
            fread(&c, sizeof(char), 1, fd);
            pal[j++]=c;
        }
        //p=new Peso();
        //p.palabra=(char *)malloc((strlen(pal)+1)*sizeof(char));
        //memcpy (p.palabra, pal, (strlen(pal)+1)*sizeof(char));
        //p->setPalabra(pal);
        //Palabra leída.
        //p.pesos=(tlistadin_docpeso)listadin_docpeso_nueva();
        //dp=new DocPeso();
        //Leemos doc y peso.
        //fread(&(dp.doc), sizeof(int), 1, fd);
        ldp=new list<DocPeso>();
        fread(&doc, sizeof(int), 1, fd);
        dp.setDoc(doc);
        do {
            //fread(&(dp.peso), sizeof(double), 1, fd);
            fread(&peso, sizeof(double), 1, fd);
            dp.setPeso(peso);
            //listadin_docpeso_insertaFinal(p.pesos, dp);
            ldp->push_back(dp);//insertDocPeso(dp);
            //dp=new DocPeso();
            fread(&doc, sizeof(int), 1, fd);
            dp.setDoc(doc);
        }while(doc!=-1); //Es la marca de final de "línea" que hemos puesto.
        //avl_peso_mete(&toRet, p, avl_peso_comp);
        sPal=pal;
        index->insert(index->begin(), pair<string, list<DocPeso>*>(sPal, ldp));//[pal] = ldp;
        ++i;
    }
    free(pal);
    //return toRet;
}

//Searcher::Searcher(const Searcher& orig) {
//}

Searcher::~Searcher() {
    //TODO hay que destruir muchas cosas de memoria!
}

/**
 * @brief Obtiene el título y una frase relevante de documento SGML dado.
 * @param filename Fichero de donde se desea realizar la obtención
 * @param title guardará el título del documento.
 * @param frase guardará una frase "representativa" del documento.
 * @param consulta Consulta realizada sobre este documento.
 * @return 0 si todo ha ido bien, 1 si encuentra algún error.
 * @post Si no encuentra un título, apunta **title a NULL
 * @post Si no encuentra una frase representativa, apunta **frase a NULL
 */
int Searcher::obtiene_titulo_frase(const char *filename, char **title, char **frase, const char *consulta) {
    FILE *fd;
    unsigned length;
    char *ptr_str, *ptr_strRead;
    char *pos_init, *pos_end;
    string str;
    char *tit=NULL;
    char *fra=NULL;
    int read_len;
    int toRet=0;
    int encontrado=0;
    int i,t , tam;
    //vdin_strings consultaDiv;
    list<string> *consultaDiv;
    
    if (!(fd=fopen(filename, "rt"))) {
        cout << "obtiene_titulo_frase: No se puede abrir el archivo"<<endl;
        exit(-1);
    }
    //guardamos tamaño del archivo
    fseek(fd, 0L, SEEK_END); // Ir al final del Fichero
    length=ftell(fd); // Almacenar el tamaño del Fichero
    fseek(fd,0, SEEK_SET); // Restablecer puntero
    //Reservamos memoria
    ptr_strRead=(char *)malloc((length+1)*sizeof(char));
    //leemos todo el archivo línea a línea
    ptr_str=ptr_strRead;
    read_len=0;
    while (!feof(fd)) {
    	read_len+=fread(ptr_strRead,sizeof(char),length-read_len,fd)-1;
	ptr_strRead=ptr_str+read_len;
    }
    ptr_strRead=ptr_str;
    //Buscamos título
    pos_init=strstr(ptr_strRead, "<TITLE>");
    pos_end=strstr(ptr_strRead,"</TITLE>");
    if ((pos_init) && (pos_end)) {
        pos_init+=strlen("<TITLE>");
        tit=(char *)malloc((pos_end-pos_init+1)*sizeof(char));
	strncpy(tit, pos_init, pos_end-pos_init);
        tit[pos_end-pos_init]='\0';
    } else {
        toRet=1;
        tit=NULL;
    }
    //Buscamos la primera frase que contenga alguna palabra de la consulta.
    //Separamos la consulta
    consultaDiv=utils::splitString(consulta, " ");
    //Ahora buscamos
    //tam=vdin_strings_tama(consultaDiv);
    list<string>::iterator itr=consultaDiv->begin();
    i=0;
    while((itr!=consultaDiv->end())&&(!encontrado)) {
        str=*itr;//vdin_strings_obtiene(consultaDiv, i);
        if ((pos_init=(char *)utils::strstrci(ptr_strRead, str.c_str()))) { //La ha encontrado. (subcadena)
            pos_end=pos_init+1;
            //Buscamos el punto final, para marcar la frase.
            while((pos_end[0]!='.') && (pos_end[0]!='\0') && ((pos_end[0]!='<')&&(pos_end[1]!='/'))) { ++pos_end; }
            //Una vez encontrada, la guardamos en "frase".
            fra=(char *)malloc((pos_end-pos_init+1)*sizeof(char));
            strncpy(fra, pos_init, pos_end-pos_init);
            fra[pos_end-pos_init]='\0';
            encontrado=1;
        }
        ++i;
    }
    free(ptr_strRead);
    //vdin_strings_destruye(&consultaDiv); //Esto también elimina las cadenas.
    delete consultaDiv;
    //He tenido que hacer esta chapuza, porque sino se quedaba colgado, lo más grave es que sigo sin entender porqué :)
    *title=tit;
    *frase=fra;
    //Fin chapuza.
    return toRet;
}

