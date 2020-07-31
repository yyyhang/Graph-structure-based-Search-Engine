#include <string.h>
#include <stdio.h>
#include "LList.h"

// read a word
char *collect(FILE *f){
    int buf;
    int cnt = 0;
    static char thisWord[50];
    while ((buf = fgetc(f)) != EOF){
        if ((buf >= 48 && buf <= 57) || ((buf >= 97) && (buf <= 122)) || buf==45)	// numbers or small letters or -
            thisWord[cnt++] = buf;
        else if (buf >= 65 && buf <= 90){   // convert capital letters to numbers
            buf = buf + 32;
            thisWord[cnt++] = buf;
        }
        else if (cnt <= 0)
            continue;
        else if (cnt > 0){                  // insert it into the linked list
            thisWord[cnt] = '\0';
            return thisWord;
        }
    }
    return NULL;
}

// open collection.txt, and make a linked list for all links
LList getLinks(){
    FILE *f;
    int buf;
    int cnt = 0;
    LList In = NULL;
    char thisWord[50];
    // open file and check if it is available
    if ((f = fopen ("collection.txt", "r")) == NULL) {
        printf("Error!\n");
        return (0);
    }
    while ((buf = fgetc(f)) != EOF){
        if ((buf >= 48 && buf <= 57) || (buf >= 97 && buf <= 122))	// small letters and numbers
            thisWord[cnt++] = buf;
        else if (buf >= 65 && buf <= 90){   // convert capital letters to numbers
            buf = buf + 32;
            thisWord[cnt++] = buf;
        } else if (cnt <= 0)    // not a number or letter
            continue;
        else if (cnt > 0){      // end of a word
            thisWord[cnt] = '\0';
            cnt = 0;
            In = insertSorted(In, makeNode(thisWord));  // insert it into the linked list
        }
    }
    fclose(f);
    return In;
}