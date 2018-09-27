#include <stdio.h> //   stack/NO
#include <stdlib.h> //  stack/NO
#include <malloc.h> //  stack/NO

int main() {  //  stack/NO 
	int num; //stack/NO
	int *ptr;//stack/NO
	int **handle;//stack/NO

	num = 14; //stack/NO
	ptr = (int *)malloc(2 * sizeof(int));//stack and heap/YES
	handle = &ptr; //stack/NO
	*ptr = num; //storing 14 to the heap 
	ptr = &num; //stack/
	handle = (int **)malloc(1 * sizeof(int **));//stack and heap/YES
}
