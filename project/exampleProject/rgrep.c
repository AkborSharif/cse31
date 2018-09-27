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
	char* subStrinigIterator = iterator;
	char* patternSubStringIterator = pattern;
	int escaped = 0;
	int wildcard = 0;
    int matchingOneOrMore = 0;


	while(*iterator != '\0') {
		subStrinigIterator = iterator;
		patternSubStringIterator = pattern;
		
		while(1) {
			if(*patternSubStringIterator == '\0') {
                if(matchingOneOrMore) {
                    return 0;
                }
				return 1;
			}
			if(*subStrinigIterator == '\0') {
				return 0;
			}

            matchingOneOrMore = 0;
            
			if(!escaped) {
				if(*patternSubStringIterator == '\\') {
					escaped = 1;
					patternSubStringIterator++;
				} else if(*patternSubStringIterator == '.') {
					wildcard = 1;
				}

			} else {
				escaped = 0;
			}


			if(*(patternSubStringIterator + 1) == '+') {
				matchingOneOrMore = 1;
				if(*subStrinigIterator == *patternSubStringIterator) {
					subStrinigIterator++;
				} else if(wildcard) {
					return 1;
				} else {
                    subStrinigIterator++;
					patternSubStringIterator+=2;
				}
			}else if(*(patternSubStringIterator + 1) == '?') {
				if(*subStrinigIterator == *patternSubStringIterator || wildcard) {
					subStrinigIterator++;
				}
				if(*(patternSubStringIterator + 2) == *patternSubStringIterator) {
					if(*(subStrinigIterator - 1) != *subStrinigIterator) {
						patternSubStringIterator++;
					}
				}
				patternSubStringIterator+=2;
				wildcard = 0;
			}else if(wildcard || *subStrinigIterator == *patternSubStringIterator) {
				subStrinigIterator++;
				patternSubStringIterator++;
				wildcard = 0;
				escaped = 0;
			}else {
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
