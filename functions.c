#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UNAVAILABLE_NUMBER INT_MAX
#define INPUT_SIZE 10000


void number_generator (int people, int sticks) {
    FILE *input_file;
    input_file= fopen("input.txt", "w");

    srand(time(NULL));

    int i, number;

    fprintf(input_file, "%d %d \n", people, sticks);


    for (i = 1; i < sticks; i++) {
        number = rand() % 10000 + 1;
        fprintf(input_file, "%d ", number);
    }

    fclose(input_file);
}


void quicksort(int vector_sticks[INPUT_SIZE],int first,int last) {
    int i, j, pivot, temp;

    if(first < last) {
        pivot = first;
        i = first;
        j = last;
        while(i < j) {
            while(vector_sticks[i] <= vector_sticks[pivot] && i < last)
                i++;
            while(vector_sticks[j] > vector_sticks[pivot])
                j--;
            if(i < j) {
                temp = vector_sticks[i];
                vector_sticks[i] = vector_sticks[j];
                vector_sticks[j] = temp;
            }
        }
        temp = vector_sticks[pivot];
        vector_sticks[pivot] = vector_sticks[j];
        vector_sticks[j] = temp;
        quicksort(vector_sticks,first,j-1);
        quicksort(vector_sticks,j+1,last);
    }
}


int minimum_diff(int vector_diff[], int vector_size) {
    int min_diff, i;
    min_diff = vector_diff[0];

    for(i = 0; i < vector_size - 1; i++) {
        if(vector_diff[i] != UNAVAILABLE_NUMBER && vector_diff[i] <= min_diff) {
            min_diff = vector_diff[i];
        }
    }
    return min_diff;
}
