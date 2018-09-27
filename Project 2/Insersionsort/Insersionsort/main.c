//
//  main.c
//  Insersionsort
//
//  Created by Mohammad Sharif on 7/27/18.
//  Copyright © 2018 Mohammad Sharif. All rights reserved.
//

#include <stdio.h>

int main()
{
    int size = 6;
    int array[6] = { 5, 3,2, 4, 2, 1 };
    int c = 0;
    int d = 0;
    int t = 0;
    
    for (c = 1 ; c <= size - 1; c++) {
        d = c;
        while (d > 0 && array[d] < array[d - 1]) {
            t = array[d];
            array[d] = array[d - 1];
            array[d - 1] = t;
            d--;
        }
    }
    
    for (c = 0; c <= size - 1; c++) {
        printf("%d\n", array[c]);
    }
    
    return 0;
}
