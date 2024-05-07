#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"
#include <ctype.h>

/**************** normalizeWord() ****************/

void normalizeWord (char *word) {
    if ( word != NULL) {
        //convert to lowercase 

        for (char *p = word; *p; p++) {
            *p = tolower((unsigned char)*p);
        }
    }
}
