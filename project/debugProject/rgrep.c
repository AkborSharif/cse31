#include <stdio.h>
#define MAXSIZE 4096

/**
 * You can use this recommended helper function
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *subStrinigIterator, char *patternSubStringIterator) {
    return 0;
}

/**
 * You may assume that all strings are properly null terminated
 * and will not overrun the buffer set by MAXSIZE
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {
    
    char* iterator = line;
    char* subStringIterator = iterator;
    char* patternSubStringIterator = pattern;
    int escaped = 0;
    int wildcard = 0;
    int matchedOnce = 0;
    
    
    while(*iterator != '\0') {
        subStringIterator = iterator;
        patternSubStringIterator = pattern;
        
        while(1) {
             printf(" Pattern: %c \n ", *patternSubStringIterator);
             printf("Line: %c ", *subStringIterator);
            
            if(*patternSubStringIterator == '\0') {
                return 1;
            }
            if(*subStringIterator == '\0') {
                return 0;
            }
            
            if(!escaped) {
              //  printf("Pattern: %c", *patternSubStringIterator);
                if(*patternSubStringIterator == '.') {
                    wildcard = 1;
                }
               else if(*patternSubStringIterator == '\\') {
                    patternSubStringIterator++;
                    escaped = 1;
               }
         }else {
             escaped = 0;
            }
            
            
            
            if(*(patternSubStringIterator + 1) == '+') {
                if(*subStringIterator == *patternSubStringIterator) {
                    matchedOnce = 1;
                    subStringIterator++;
                } if(wildcard) {
                    return 1;
                } else {
                    if(matchedOnce) {
                        matchedOnce = 0;
                        subStringIterator++;
                        patternSubStringIterator+=2;
                    } else {
                        break;
                    }
                }
            } else if(*(patternSubStringIterator + 1) == '?') {
                if(*subStringIterator == *patternSubStringIterator || wildcard) {
                    subStringIterator++;
                }
                if(*(patternSubStringIterator + 2) == *patternSubStringIterator) {
                    if(*(subStringIterator - 1) != *subStringIterator) {
                        patternSubStringIterator++;
                    }
                }
                patternSubStringIterator+=2;
                wildcard = 0;
            } else if(wildcard || *subStringIterator == *patternSubStringIterator) {
                subStringIterator++;
                patternSubStringIterator++;
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
    rgrep_matches("hidin", "h.d..?n");
    return 0;
}
