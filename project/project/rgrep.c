
#include <stdio.h>
#define MAXSIZE 4096

/**
 * You can use this recommended helper function
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char * partial_line, char * pattern) {
    // Implement if desire
    
    return 0;
}

/**
 * You may assume that all s are properly null terminated
 * and will not overrun the buffer set by MAXSIZE
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {
    
    char* iterator = line;
    char* Stringincrement = iterator;
    char* patternincrement = pattern;
    int escaped = 0;
    int wildcard = 0;
    int matchedOnce = 0;
    
    
    while(*iterator != '\0' && *iterator != '\n') {
        Stringincrement = iterator;
        patternincrement = pattern;
        
        while(1) {
            //printf(" Pattern: %c \n ", *patternincrement);
            
            if(*patternincrement == '\0') {
                return 1;
            }
          //  printf("Line: %c \n", *Stringincrement);
            if(*Stringincrement == '\0' || *Stringincrement == '\n') {
                return 0;
            }
            
            if(!escaped) {
                //  printf("Pattern: %c", *patternincrement);
                if(*patternincrement == '.') {
                    wildcard = 1;
                }
                else if(*patternincrement == '\\') {
                    patternincrement++;
                    escaped = 1;
                    continue;
                }
            }else {
                escaped = 0;
            }
            
            
            
            if(*(patternincrement + 1) == '+') {
                if(*Stringincrement == *patternincrement) {
                    matchedOnce = 1;
                    Stringincrement++;
                }
                if(wildcard) {
                    return 1;
                } else {
                    if(matchedOnce) {
                        matchedOnce = 0;
                        Stringincrement++;
                        patternincrement+=2;
                    } else {
                        break;
                    }
                }
            } else if(*(patternincrement + 1) == '?') {
                if(*Stringincrement == *patternincrement || wildcard) {
                    Stringincrement++;
                }
                if(*(patternincrement + 2) == *patternincrement || wildcard) {
                    if(*(Stringincrement - 1) != *Stringincrement) {
                        patternincrement++;
                    }
                }
                patternincrement+=2;
                wildcard = 0;
            } else if(wildcard || *Stringincrement == *patternincrement) {
                Stringincrement++;
                patternincrement++;
                wildcard = 0;
                escaped = 0;
            } else {
                break;
            }
            
            
        }
        
        iterator++;
    }
    
    return 0;
}

    
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }
    
    /* we're not going to worry about long lines */
    char buf[MAXSIZE];
    
    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }
    
    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }
    
    return 0;
}
