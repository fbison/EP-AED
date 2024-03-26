#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "global_functions.h"

char* copyToLower(char *string) {
    char * copia= strdup(string);
    for(int i = 0; copia[i]; i++){
      copia[i] = tolower(copia[i]);
    }
    return copia;
}

char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}