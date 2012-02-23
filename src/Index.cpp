/* 
 * File:   index.cpp
 * Author: Antonio Sánchez Perea
 * 
 * Created on 8 de febrero de 2012, 13:33
 */

#include "include/Index.h"


/**
 * Constructor de la clase generadora del índice
 * @param root Directorio del que realizar la extracción
 */
Index::Index(string root) {
    this->directory=root;
    documents=new list<document*>();
    lPesos=new list<Peso*>;
}

/**
 * @brief Extrae la ruta absoluta de todos los archivos que hay en el directorio indicado.
 * @post Almacena una lista con tantos elementos como ficheros haya en el directorio
 */
void Index::read() {
    //vdin_documentos toRet;
        list<string> files;//vdin_strings files;
        document *doc;
        unsigned int i,tam;
        files=utils::getFilesFromDirectory(this->directory);
        i=0;
        tam=files.size();
        //cout << "Ocupa "<<tam<<endl;
        //toRet=vdin_documentos_crea();
        //tam=files.size();//vdin_strings_tama(files);
        //for(i=0;i<tam;++i) {
        list<string>::iterator itr;//=files.begin();
        for(itr=files.begin();itr!=files.end();itr++) {
            ++i;
            doc=new document();//(document)malloc(sizeof(struct rep_document));
            if (utils::_readFile(*itr,doc, i)!=0) {
                cout << "Index::read: Error de sintaxis al leer "<<*itr<<endl;
            } /*else {
                cout << "Text: "<<doc->getCat()<<endl;
            }*/
            documents->push_back(doc);//vdin_documentos_aumd(toRet, doc);
        }
	//return toRet;
}

/**
 * @brief Dado un vector de documentos y un archivo de palabras vacías. Elimina de todos los documentos las palabras que se encuentren en dicho archivo.
 * @param v vector de documentos del que realizar la eliminación
 * @param stopperFile archivo de texto que contenga las palabras vacías.
 */
void Index::stopper(const string stopperFile) {
    Stopper *stp;//avl_string avl;
    document *doc;
    //int i;
    //char *cat_tmp, *tags_tmp;
    //Creamos el AVL con la lista de palabras vacías
    stp=new Stopper(stopperFile);//avl=create_stopper_list(stopperFile);
    //Ahora para cada uno de los documentos, comprobamos si existe alguna palabra vacía.
    list<document*>::iterator itr;
    for(itr=documents->begin();itr!=documents->end();itr++) {
        doc=*itr;//vdin_documentos_obtiene(v,i);
        //cout << "Original: "<<doc->getOriginal()<<endl;
        doc->setStopper(stp->eliminate_null_words(doc->getOriginal()));//->stopper=eliminate_null_words(avl, doc->original_text);
        //cout << "Stopper: "<<doc->getStopper()<<endl;
        //Categorías
        //cat_tmp=eliminate_null_words(avl,doc->cat);
        //free(doc->cat);
        //doc->cat=cat_tmp;
        doc->setCat(stp->eliminate_null_words(doc->getCat()));
        //Tags
        //tags_tmp=eliminate_null_words(avl,doc->tags);
        //free(doc->tags);
        //doc->tags=tags_tmp;
        doc->setTags(stp->eliminate_null_words(doc->getTags()));
    }
    //Destruimos el stopper.
    delete stp;//avl_string_dest(&avl);
}


/**
 * @brief Procedimiento que dado un vector de documentos, normaliza todos los elementos que contenga. Elimina caracteres que no sean [a-zA-Z0-9] y espacio.
 * @param originales vector a normalizar.
 */
void Index::normalize(){
    //Normalizamos textos de los documentos
    //int tam, i;
    document *doc;
    //char *cat_tmp, *tags_tmp;
    //tam=documents.size();//vdin_documentos_tama(originales);
    list<document*>::iterator itr;
    for(itr=documents->begin();itr!=documents->end();itr++) {
        //Texto
        doc=*itr;//vdin_documentos_obtiene(originales,i);
        //cout << "Stopper: "<<doc->getStopper()<<endl;
        doc->setNormalized(normalize::normalizeString(doc->getStopper()));//->normalized=normalizeString(doc->stopper);
        //cout << "Normalized: "<<doc->getNormalized()<<endl;
        //Categorías
        //cat_tmp=normalizeString(doc->cat);
        //free(doc->cat);
        //doc->cat=cat_tmp;
        doc->setCat(normalize::normalizeString(doc->getCat()));
        //Tags
        //tags_tmp=normalizeString(doc->tags);
        //free(doc->tags);
        //doc->tags=tags_tmp;
        doc->setTags(normalize::normalizeString(doc->getTags()));

    }
}

/**
 * @brief Procedimiento encargado de la extracción de raíces de palabras. Dado un vector de documentos hace la extracción sobre ellos.
 */
void Index::stemmer() {
    //int i;
    document *doc;
    //char *cat_tmp, *tags_tmp;
    list<document*>::iterator itr;
    for(itr=documents->begin();itr!=documents->end();itr++){
        doc=*itr;//vdin_documentos_obtiene(v, i);
        //cout << "Normalized: "<<doc->getNormalized()<<endl;
        doc->setStemmer(stemstring(doc->getNormalized().c_str()));//->stemmer=stemstring(doc->normalized);
        //cout << "Stemmer: "<<doc->getStemmer()<<endl;
        //Categorías
        //cat_tmp=stemstring(doc->cat);
        //free(doc->cat);
        //doc->cat=cat_tmp;
        doc->setCat(stemstring(doc->getCat().c_str()));
        //Tags
        //tags_tmp=stemstring(doc->tags);
        //free(doc->tags);
        //doc->tags=tags_tmp;
        doc->setTags(stemstring(doc->getTags().c_str()));
    }
}

/**
 * @brief Genera el archivo ids.txt con los pares "nombre_documento | ID_documento"
 * @param v Vector de documentos a volcar en disco.
 */
void Index::genera_archivo_ficheros() {
    //int i;
    FILE *fd;
    //ocument doc;
    if (!(fd=fopen("ids.txt","wt"))) {
        cout << "genera_archivo_ficheros: No se puede abrir el archivo ids.txt"<<endl;
    }
    list<document*>::iterator itr;
    for(itr=documents->begin();itr!=documents->end();itr++){
        //doc=vdin_documentos_obtiene(v,i);
        fprintf(fd, "%s | %d\n",(*itr)->getFilename().c_str(), (*itr)->getIdNumber());
    }
    fclose(fd);
}

/**
 * @brief Dado un vector de documentos, calcula el peso de todas las palabras.
 * @pre Deben estar normalizada, sin palabras vacías y con extracción de raíces realizada.
 * @param v vector de documentos, sobre cada uno de los documentos se realizada el pesado de palabras.
 * @return lista dinámica de pesos.
 */
void Index::pesos(/*vdin_documentos v*/) {
    int i,j, numDocsX, tam, docActual=-1; //Valor basura, empiezan en 0.
    //vdin_strings words, tmp;
    list<string> *words, *tmp;
    list<WordFile> vdinwf;
    list<Word> vdinw;
    document *doc;
    WordFile wf;
    Word *w;
    DocFrec df, *ptr_df;
    string palabraActual;
    Peso *pToInsert;
    DocPeso dp;
    double acum, norma, num, idf;
    //list<Peso> *lPesos;

    //Se genera el archivo ids.txt con los pares: archivo.sgml | valor numérico
    genera_archivo_ficheros();
    //Generamos el array con los pares (palabra-fichero).
    //vdinwf=vdin_wordfile_crea();
    numDocs=documents->size();//vdin_documentos_tama(v);
    list<document*>::iterator itr;
    //for (i=0;i<numDocs;++i) { //Para cada documento
    for(itr=documents->begin();itr!=documents->end();itr++) { //Para cada documento
        doc=*itr;//vdin_documentos_obtiene(v, i);
        //Generamos un vector con cada una de las palabras (ya normalizadas y con raíces extraídas)
        //cout << "Stemmer: "<<doc->getStemmer()<<endl;
        words=utils::splitString(doc->getStemmer().c_str(), " ");
        //Incluimos los de tags y categories
        tmp=utils::splitString(doc->getCat().c_str(), " ");
        //vdin_strings_join(words, tmp);
        words->merge(*tmp);
        delete tmp;
        //vdin_strings_destruye(&tmp);
        tmp=utils::splitString(doc->getTags().c_str(), " ");
        //vdin_strings_join(words, tmp);
        words->merge(*tmp);
        delete tmp;
        //vdin_strings_destruye(&tmp);
        list<string>::iterator itrw;
        //for (j=0;j<vdin_strings_tama(words);++j) { //Insertamos los pares (palabra-fichero)
        for(itrw=words->begin();itrw!=words->end();itrw++) { //Insertamos los pares (palabra-fichero)
            //wf.palabra=(char *)malloc((strlen(vdin_strings_obtiene(words, j))+1)*sizeof(char));
            //strcpy(wf.palabra,vdin_strings_obtiene(words,j));
            wf.setPalabra(*itrw);
            //wf.file=doc->idNumber;
            wf.setFile(doc->getIdNumber());
            //vdin_wordfile_aumd(vdinwf, wf);
            vdinwf.push_back(wf);
        }
        //Liberamos memoria del vector de palabras.
        //vdin_strings_destruye(&words);
    }

    //Ordenamos el vector por palabras
    //vdin_wordfile_sort(vdinwf);
    vdinwf.sort(WordFile::comp);

    //Creamos el vector de frecuencias.
    //Se hará mediante un vector de "word", y cada elemento contiene una lista de docfrec.
    //vdinw=vdin_word_crea();
    //tam=vdin_wordfile_tama(vdinwf);
    //i=0;
    //wf=vdin_wordfile_obtiene(vdinwf,i++);
    //do { //WHILE haya
    list<WordFile>::iterator itrwf;
    itrwf=vdinwf.begin();
    //for(itrwf=vdinwf.begin();itrwf!=vdinwf.end();itrwf++) {
    while(itrwf!=vdinwf.end()) {
        wf=*itrwf;
        //w.palabra=(char *)malloc((strlen(wf.palabra)+1)*sizeof(char));
        //strcpy(w.palabra, wf.palabra);
        w=new Word();
        w->setPalabra(wf.getPalabra());

        //w.frecuencia=listadin_docfrec_nueva();
        palabraActual=w->getPalabra();//.palabra; //No hace falta reservar memoria, quiero referenciar.
        //while((!strcmp(palabraActual,w.palabra)) && (i<=tam)) { //While sean la misma palabra.
        while((palabraActual==w->getPalabra()) && (itrwf!=vdinwf.end())) {
            //df.idDoc=wf.file;
            df.setIdDoc(wf.getFile());
            //docActual=df.idDoc;
            docActual=df.getIdDoc();
            df.setFrec(0);//.frec=0;
            palabraActual=wf.getPalabra();//wf.palabra; //No reservo memoria, lo único que me hace falta es referenciar.
            //while ((wf.file==docActual) && (!strcmp(palabraActual, wf.palabra)) && (i<=tam)) { //While sea el mismo doc y la misma palabra.
            while ((wf.getFile()==docActual) && (palabraActual==wf.getPalabra()) && (itrwf!=vdinwf.end())) { //While sea el mismo doc y la misma palabra.
                df.aumFrec();//.frec++;
                if (itrwf!=vdinwf.end()) { wf=*itrwf; itrwf++; /*vdin_wordfile_obtiene(vdinwf,i++);*/ }
                else { wf.setFile(-1); itrwf++; }
            }

            //Insertamos en la lista de doc-frec
            //listadin_docfrec_insertaFinal(w.frecuencia, df);
            w->addDocFrec(df);
        }
        //Si ya no es la misma palabra, meto en el vector.
        //vdin_word_aumd(vdinw, w);
        vdinw.push_back(*w);
    } //}while(i<tam);

    //Destruimos el vector vdinwf, pero primero los elementos de dentro.
    /*for(i=0;i<vdin_wordfile_tama(vdinwf);++i) {
        wf=vdin_wordfile_obtiene(vdinwf, i);
        free(wf.palabra);
    }
    vdin_wordfile_destruye(&vdinwf);*/
    //Vamos a calcular los vectores de pesos normalizados
    //Para cada palabra X del vector de frecuencias vdinwf, calculamos el IDF de la palabra.
    //Ya tenemos numDocs (número total de documentos)
    //tam=vdin_word_tama(vdinw);
    acum=0;
    //lPesos=listadin_peso_nueva();
    list<Word>::iterator itrw;
    //for(i=0;i<tam;++i) { //Para cada palabra
    for(itrw=vdinw.begin();itrw!=vdinw.end();itrw++) { //Para cada palabra
        //w=vdin_word_obtiene(vdinw,i);
        *w=*itrw;
        //numDocsX=listadin_docfrec_numElem(w.frecuencia);
        numDocsX=w->frecSize();
        idf=log10(numDocs/numDocsX)/log10(2);
        //Tenemos el idf, paso 2
        //Multiplicamos por la frecuencia de aparición en cada documento.
        //listadin_docfrec_iter_ini(w.frecuencia);
        w->startIterator();
        acum=0;
        //while(!listadin_docfrec_iter_fin(w.frecuencia)) {
        while(!w->endIterator()) {
            //ptr_df=listadin_docfrec_iter_siguiente (w.frecuencia);
            *ptr_df=w->valueIterator();
            w->nextIterator();
            //num=(ptr_df->frec)*idf;
            num=(ptr_df->getFrec())*idf;
            num*=num; //num^2
            acum+=num;
        }
        norma=sqrt(acum); //Denominador

        //Calculamos el peso, teniendo ya la norma de la palabra y el idf
        pToInsert=new Peso();
        //pToInsert.palabra=(char*)malloc((strlen(w.palabra)+1)*sizeof(char));
        //strcpy(pToInsert.palabra, w.palabra);
        pToInsert->setPalabra(w->getPalabra());
        //pToInsert.pesos=listadin_docpeso_nueva();
        //listadin_docfrec_iter_ini(w.frecuencia);
        w->startIterator();
        int i=0;
        //while(!listadin_docfrec_iter_fin(w.frecuencia)) {
        while(!w->endIterator()) {
            ++i;
            //ptr_df=listadin_docfrec_iter_siguiente (w.frecuencia);
            *ptr_df=w->valueIterator();
            w->nextIterator();
            //dp.peso=((ptr_df->frec)*idf) / norma;
            dp.setPeso(ptr_df->getFrec()*idf / norma);
            //dp.doc=ptr_df->idDoc;
            dp.setDoc(ptr_df->getIdDoc());
            //listadin_docpeso_insertaFinal(pToInsert.pesos, dp);
            pToInsert->insertDocPeso(dp);
        }
        //if (i>1) { cout<<"Ha entrado más de una vez para la palabra "<<w->getPalabra()<<endl; }
        //listadin_peso_insertaFinal(lPesos, pToInsert);
        lPesos->push_back(pToInsert);
    }
    //Liberamos vdinw
    /*for(i=0;i<vdin_word_tama(vdinw);++i) {
        w=vdin_word_obtiene(vdinw, i);
        free(w.palabra);
        listadin_docfrec_destruye(&(w.frecuencia));
    }
    vdin_word_destruye(&vdinw);*/
    //Ya tengo el vector(lista) de pesos, devolvemos
    //return lPesos;
}

/**
 * @brief Función que genera un fichero índice.
 * @param lp Lista de pesos de palabras
 * @param numDocs Número de documentos totales.
 * @param filename Archivo en el que se escribirá el índice
 * @return El número de palabras escritas en el índice. (Sirve para estadísticas, si se quiere usar).
 */
int Index::write(/*tlistadin_peso lp, int numDocs,*/ const string filename) {
    FILE *fd;
    Peso *p;
    int doc;
    double peso;
    int marca=-1;
    int numElem;
    DocPeso *dp;
    //Inicializamos
    if (!(fd=fopen(filename.c_str(), "wb"))) {
        cout << "Index::write: Error al abrir archivo para escribir índice."<<endl;
    }
    numElem=lPesos->size();//listadin_peso_numElem(lp);
    list<Peso*>::iterator itr;
    //listadin_peso_iter_ini(lp);
    //Escribimos el número de documentos
    fwrite(&numDocs, sizeof(int), 1, fd);
    //Escribimos el número de palabras.
    fwrite(&numElem, sizeof(int), 1, fd);
    //Empezamos a volcar la estructura en el archivo.
    //while(!listadin_peso_iter_fin(lp)) {
    for(itr=lPesos->begin();itr!=lPesos->end();itr++) {
        p=*itr;//listadin_peso_iter_siguiente (lp);
        //fwrite(p->palabra, sizeof(char), strlen(p->palabra)+1, fd);
        fwrite(p->getPalabra().c_str(), sizeof(char), p->getPalabra().length()+1, fd);
        //cout << "Guarda palabra "<<p->getPalabra()<<endl;
        //listadin_docpeso_iter_ini(p->pesos);
        p->startIterator();
        //if (p->endIterator()) { cout<<"No entra al iterador"<<endl; }
        //while(!listadin_docpeso_iter_fin(p->pesos)) {
        int i=0;
        while(!p->endIterator()) {
            //cout << "Entra iterador"<<endl;
            //dp=listadin_docpeso_iter_siguiente(p->pesos);
            ++i;
            *dp=p->valueIterator();
            p->nextIterator();
            doc=dp->getDoc();
            peso=dp->getPeso();
            fwrite(&doc, sizeof(int), 1, fd);
            fwrite(&peso, sizeof(double), 1, fd);
            //cout << "Escribe marca"<<endl;
        }

        if (i>1) { cout<<"Entrado más de una vez para la palabra "<<p->getPalabra()<<endl; }
        fwrite(&marca, sizeof(int), 1, fd); //Para marcar el fin de línea.
    }
    fclose(fd);
    return numElem;
}

Index::~Index() {
    delete documents;
    delete lPesos;
}


