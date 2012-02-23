/* 
 * File:   utils.cpp
 * Author: antonio
 * 
 * Created on 8 de febrero de 2012, 13:55
 */

#include "include/utils.h"
#include "include/document.h"

/**
 * @brief Obtiene todos los nombres de archivo dado un directorio
 * @param path directorio del que tiene que extraer los nombres de archivo.
 * @return list<string> donde cada uno de los elementos es el nombre de un fichero
 */

list<string> utils::getFilesFromDirectory(const string path) {
    DIR *dir;
    list<string> *toRet;
    //char *toInsert; //char *toInsert;
    struct stat stata;
    char filename[512];

    toRet = new list<string > ();
    struct dirent *enl;
    if (!(dir = opendir(path.c_str()))) {
        cout << "Error utils::getFilesFromDirectory "<<path<<endl;
        exit(1);
    }

    while ((enl = readdir(dir))) { //Mientras haya archivos en el directorio, (end!=NULL), los metemos en el vector.
        if ((strcmp(".", enl->d_name)) && (strcmp("..", enl->d_name)) && (strcmp("", enl->d_name))) {
            strcpy(filename, path.c_str());
            strcat(filename, enl->d_name);
            if (lstat(filename, &stata) == -1) {
                cout << "Error" <<endl;
                //perror(enl->d_name);
            } else { //Metemos nombre en el vector
                //toInsert = (char *) malloc((strlen(filename) + 1) * sizeof (char));
                //toInsert = (char *) malloc((strlen(filename) + 1) * sizeof (char));
                //strcpy(toInsert, filename);
                toRet->push_back(string(filename)); //vdin_strings_aumd(toRet, toInsert);
            }
        }
    }
    closedir(dir);
    return *toRet;
}

/**
 * @brief Separa una cadena en partes, dado uno o varios tokens.
 * @param str Cadena que se quiere partir
 * @param tokens separadores
 * @return list<string> las distintas partes de la cadena
 */

list<string> *utils::splitString(const char *str, const char *tokens) {
    char *pch, *ptr_str, *str_ori, *saveptr;
    list<string> *toRet;
    str_ori=(char *)malloc(((strlen(str)+1))*sizeof(char));
    strcpy(str_ori,str);// = str;
    toRet = new list<string>(); //vdin_strings_crea();

    pch = strtok_r(str_ori, tokens, &saveptr);
    if (pch) {
        ptr_str = (char *) malloc((strlen(pch) + 1) * sizeof (char));
        strcpy(ptr_str, pch);
    }
    while (pch != NULL) {
        toRet->push_back(ptr_str); //vdin_strings_aumd(toRet, ptr_str);
        //printf("Metemos %s\n",ptr_str);
        //printf ("%s\n",pch);
        pch = strtok_r(NULL, tokens, &saveptr);
        if (pch) {
            ptr_str = (char *) malloc((strlen(pch) + 1) * sizeof (char));
            strcpy(ptr_str, pch);
        }
    }
    //str = str_ori;
    free(str_ori);
    return toRet;
}

/**
 * @brief Lee un archivo SGML.
 * @param file Nombre del archivo SGML
 * @param doc estructura document donde se guardará el documento. No debe estar inicializada (reserva de memoria).
 * @return 1 si durante la lectura ha habido un error, 0 en caso contrario.
 */
//TODO cambiar a void y jugar con excepciones
int utils::_readFile(const string file, document *doc, int idNumber) {
    char *ptr_strRead;
    char *ptr_str;
    char *pos_init;
    char *pos_end;
    char *tmp_cad;
    int toRet = 0;
    int length, read_len = 0;
    FILE *fd;

    //Guardamos nombre del archivo
    //doc->filename = (char *) malloc((strlen(file) + 1) * sizeof (char));
    doc->setFilename(file);//strcpy(doc->filename, file);
    //Abrimos archivo
    if (!(fd = fopen(file.c_str(), "rt"))) {
        //depuracion("_readFile: No se puede abrir el archivo", ERR_ABRIR_ARCHIVO);
        //TODO depuración
    }
    //guardamos tamaño del archivo
    fseek(fd, 0L, SEEK_END); // Ir al final del Fichero
    length = ftell(fd); // Almacenar el tamaño del Fichero
    fseek(fd, 0, SEEK_SET); // Restablecer puntero
    //Reservamos memoria
    ptr_strRead = (char *) malloc((length + 1) * sizeof (char));
    //leemos todo el archivo línea a línea
    ptr_str = ptr_strRead;
    while (!feof(fd)) {
        read_len += fread(ptr_strRead, sizeof (char), length - read_len, fd) - 1;
        ptr_strRead = ptr_str + read_len;
    }
    ptr_strRead = ptr_str;
    //Introducimos el id (en número).
    doc->setIdNumber(idNumber);//->idNumber = idNumber;
    //Buscamos etiquetas
    //Buscamos <ID>
    pos_init = strstr(ptr_strRead, "<ID>");
    if (pos_init)
        pos_end = strstr(pos_init, "</ID>");
    if ((pos_init) && (pos_end)) {
        pos_init += strlen("<ID>");
        //doc->id = (char *) malloc((pos_end - pos_init + 1) * sizeof (char));
        tmp_cad = (char *) malloc((pos_end - pos_init + 1) * sizeof (char));
        strncpy(tmp_cad, pos_init, pos_end - pos_init);
        tmp_cad[pos_end - pos_init] = '\0';
        doc->setId(string(tmp_cad));
        free(tmp_cad);
    } else {
        toRet = 1;
        doc->setId("");//doc->id = NULL;
    }
    //Buscamos <TITLE>
    pos_init = strstr(ptr_strRead, "<TITLE>");
    pos_end = strstr(ptr_strRead, "</TITLE>");
    if ((pos_init) && (pos_end)) {
        pos_init += strlen("<TITLE>");
        tmp_cad = (char *) malloc((pos_end - pos_init + 1) * sizeof (char));
        strncpy(tmp_cad, pos_init, pos_end - pos_init);
        tmp_cad[pos_end - pos_init] = '\0';
        doc->setTitle(string(tmp_cad));
        free(tmp_cad);
    } else {
        toRet = 1;
        doc->setTitle("");//doc->title = NULL;
    }
    //Buscamos <CATEGORIES>
    pos_init = strstr(ptr_strRead, "<CATEGORIES>");
    pos_end = strstr(ptr_strRead, "</CATEGORIES>");
    if ((pos_init) && (pos_end)) {
        pos_init += strlen("<CATEGORIES>");
        tmp_cad = (char *) malloc((pos_end - pos_init + 1) * sizeof (char));
        strncpy(tmp_cad, pos_init, pos_end - pos_init);
        tmp_cad[pos_end - pos_init] = '\0';
        doc->setCat(string(tmp_cad));
        free(tmp_cad);
        /* ANTIGUO
        categories=(char *)malloc((pos_end-pos_init+1)*sizeof(char));
        strncpy(categories, pos_init, pos_end-pos_init);
        categories[pos_end-pos_init]='\0';
        doc->cat=splitString(categories, ",");
        free(categories);
         */

    } else {
        toRet = 1;
        doc->setCat("");//doc->cat = NULL;
    }
    //Buscamos <TAGS>
    pos_init = strstr(ptr_strRead, "<TAGS>");
    pos_end = strstr(ptr_strRead, "</TAGS>");
    if ((pos_init) && (pos_end)) {
        pos_init += strlen("<TAGS>");
        tmp_cad = (char *) malloc((pos_end - pos_init + 1) * sizeof (char));
        strncpy(tmp_cad, pos_init, pos_end - pos_init);
        tmp_cad[pos_end - pos_init] = '\0';
        doc->setTags(string(tmp_cad));
        free(tmp_cad);
        /* ANTIGUO
        tags=(char *)malloc((pos_end-pos_init+1)*sizeof(char));
        strncpy(tags, pos_init, pos_end-pos_init);
        tags[pos_end-pos_init]='\0';
        doc->tags=splitString(categories, ",");
        free(tags);*/
    } else {
        toRet = 1;
        doc->setTags("");//doc->tags = NULL;
    }
    //Buscamos <TEXT>
    pos_init = strstr(ptr_strRead, "<TEXT>");
    pos_end = strstr(ptr_strRead, "</TEXT>");
    if ((pos_init) && (pos_end)) {
        pos_init += strlen("<TEXT>");
        tmp_cad = (char *) malloc((pos_end - pos_init + 1) * sizeof (char));
        strncpy(tmp_cad, pos_init, pos_end - pos_init);
        tmp_cad[pos_end - pos_init] = '\0';
        doc->setOriginal(string(tmp_cad));
        free(tmp_cad);
    } else {
        toRet = 1;
        doc->setOriginal("");//doc->original_text = NULL;
    }
    //Liberamos
    free(ptr_str);
    //cout<< "Termina de leer archivo"<<endl;
    return toRet;
}

utils::utils() {
}

utils::utils(const utils& orig) {
}

utils::~utils() {
}


/**
 * @brief str case insensitive
 * @param haystack text
 * @param needle found word
 * @return pointer to first occurrence
 */
const char *utils::strstrci (const char *haystack, const char *needle) {
    if ( !*needle ) {
        return haystack;
    }
    for (;*haystack;++haystack ) {
        if ( toupper(*haystack) == toupper(*needle) ) {
        /*
         * Matched starting char -- loop through remaining chars.
         */
        const char *h, *n;
        for ( h = haystack, n = needle; *h && *n; ++h, ++n ) {
            if ( toupper(*h) != toupper(*n) ) {
                break;
            }
        }
        if ( !*n ) {/* matched all of 'needle' to null termination */
            return haystack; /* return the start of the match */
        }
        }

    }
    return 0;
}
