#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UNAVAILABLE_NUMBER INT_MAX
#define INPUT_SIZE 10000


int main()
{
    int people, sticks;

    scanf("%d", &people);   //reading from keyboard the number of people attending the dinner
    scanf("%d", &sticks);   //reading from keyboard the number of available sticks

    number_generator(people, sticks);     //generating numbers based on the input data

    FILE *input_file;
    input_file= fopen("input.txt", "r");    //opening the file for reading data from it
    int vector_sticks[INPUT_SIZE];

    if(input_file == NULL) {    //testing if there is data in the file
        printf("Error Reading File\n");     //printing an error text if the file is empty
        exit (0);
    }

    int people_number, sticks_number;
    fscanf(input_file, "%d %d ", &people_number, &sticks_number );  //reading from the input file the number of people and sticks

    for(int i = 0; i < INPUT_SIZE; i++) {
        fscanf(input_file, "%d ", &vector_sticks[i] );     //reading the generated random numbers from the input file
    }

    fclose(input_file);     //closing the input file


    int vector_diff[1001];

    quicksort(vector_sticks, 0, sticks_number-1);   //sorting the vector which contains the random numbers

    printf( "\nSorted vector: ");
    for(int i = 0; i < sticks_number; i++){
        printf("%d ", vector_sticks[i]);    //printing the sorted vector
    }

    int vector_diff_size = 0;   //initializing the size of the difference (cost) vector to 0

    for(int i = 0; i < sticks_number - people_number - 1; i++) {
        vector_diff[i] = vector_sticks[i+1] - vector_sticks[i];     //creating the difference (cost) vector
        vector_diff_size++;     //incrementing the size for every element in the vector
    }

    printf("\n\nCosts vector: ");
    for(int i = 0; i < vector_diff_size; i++)
        printf("%d ", vector_diff[i]);      //printing the difference (cost) vector

    int k=0;    //initializing k to 0 as an iterator
    int vector_big_sticks[1001];

    for(int i = sticks_number - 1; i >= sticks_number - people_number; i--) {
        vector_big_sticks[k] = vector_sticks[i];    //creating the vector which cointains the sizes of the bigger sticks
        k++;    //incrementing the iterator for every element in the vector
    }

    int pairs_number = 0;   //initializing the number of the pairs of sticks to 0
    int cost = 0;   //initializing the cost to 0

    while(pairs_number < people_number) {
        int min_diff = minimum_diff(vector_diff, vector_diff_size) ;    //calling the function to find the minimum in the difference vector
        for(int i=0; i < vector_diff_size; i++) {
            if (pairs_number == people_number) {
                break;}                        //if the number of pairs is equal to the number of people attending, there is no need to continue
            if(vector_diff[0] == min_diff) {
                cost += vector_diff[0];                 //if the first element of the vector is the minimum, we increment the total cost with
                vector_diff[0] = UNAVAILABLE_NUMBER;    //its value and turn it and its right neighbour into an unavailable number so we won`t
                vector_diff[i+1] = UNAVAILABLE_NUMBER;  // use a value twice
                pairs_number++;     //incrementing the number of pairs for each pair found
            }

            if(vector_diff[vector_diff_size] == min_diff) {
                cost += vector_diff[vector_diff_size];                  //if the last element of the vector is the minimum, we increment the total cost with
                vector_diff[vector_diff_size] = UNAVAILABLE_NUMBER;     //its value and turn it and its left neighbour into an unavailable number so we won`t
                vector_diff[vector_diff_size - 1] = UNAVAILABLE_NUMBER; //use a value twice
                pairs_number++;     //incrementing the number of pairs for each pair found
            }

            if(vector_diff[i] == min_diff) {
                cost += vector_diff[i];                 //for every minimum we find in the vector, we add its value to the total cost and turn
                vector_diff[i-1] = UNAVAILABLE_NUMBER;  //it and both its left and right neighbours into unavailable numbers so we won`t use
                vector_diff[i] = UNAVAILABLE_NUMBER;    //a value twice
                vector_diff[i+1] = UNAVAILABLE_NUMBER;
                pairs_number++;     //incrementing the number of pairs for each pair found
            }
        }
    }

    printf("\n\nThe minimum total cost is: %d", cost);      //printing the total minimum cost



}
