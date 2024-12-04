#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE 14 //Length of each line, includes two 5 digit numbers and 4 blank spaces
#define NUM_DIGITS 5 //length of each digit

typedef struct {
    int number; //what is the repeated number?
    int count; //how many times was it repeated?
} Pairs;

//returns number of characters from file
int countCharactersFromFile();
//returns text based on passed size
char * getTextFromFile(int chars);
//put each number in the associated array
int getArrayPairs(int a[], int b[], char *c);
//sort the arrays
void bubbleSort(int arr[], int n);
//calculate total distance
void solvePartOne(int a[], int b[], int c);
void solvePartTwo(int a[], int b[], int c, Pairs d[]);

int main() {
    int numOfChars = countCharactersFromFile();
    char *locationString = getTextFromFile(numOfChars);
    int length = strlen(locationString);
    int numChunks = length / CHUNK_SIZE;

    int *leftNumbers = malloc(numChunks * sizeof(int));
    int *rightNumbers = malloc(numChunks * sizeof(int));

    //places numbers into their appropriate array and sorts them by size ascending, returns the array length
    int numbers = getArrayPairs(leftNumbers, rightNumbers, locationString);

    Pairs result[numbers];

    solvePartOne(leftNumbers, rightNumbers, numbers);
    solvePartTwo(leftNumbers, rightNumbers, numbers, result);

    free(locationString);
    free(leftNumbers);
    free(rightNumbers);

    return 0;
}

void solvePartOne(int left[], int right[], int length){
    int total = 0;
    for(int i = 0; i < length; i++){
        int distance = abs(left[i] - right[i]);
        total += distance;
    }
    printf("The total distance between the two lists is: %d\n", total);
}

void solvePartTwo(int left[], int right[], int length, Pairs arr[]){
    int arrSize = 0;
    for(int i = 0; i < length; i++){
        int found = 0;
        for(int j = 0; j < length; j++){
            if (left[i] == arr[j].number){
                found = 1;
                break;
            }
        }

        if (!found) {
            arr[arrSize].number = left[i];
            arr[arrSize].count = 0;

            for (int j = 0; j < length; j++){
                if(left[i] == right[j]){
                    arr[arrSize].count++;
                }
            }
            arrSize++;
        }

    }
    int totalSimilarity = 0;
    for(int i = 0; i < arrSize; i++){
        if(arr[i].count != 0){
            totalSimilarity += arr[i].number * arr[i].count;
        }
    }
    printf("Total similarity score is: %d\n", totalSimilarity);
}

int countCharactersFromFile(){
    FILE *fp;
    int count = 0;
    char c;

    fp = fopen("puzzle.txt", "r");
    
    if (fp == NULL){
        printf("File loading error");
        return 0;
    }

    for (c = getc(fp); c != EOF; c = getc(fp)){
        count += 1;
    }

    fclose(fp);
    return count;
}

char * getTextFromFile(int chars){
    FILE *fptr = fopen("puzzle.txt", "r");
    char *locationString = malloc(chars + 1);
    size_t bytesRead = fread(locationString, sizeof(char), chars, fptr);
    locationString[bytesRead] = '\0';
    fclose(fptr);
    return locationString;
}

int getArrayPairs(int leftNumbers[], int rightNumbers[], char *locationString){
    int index = 0;
    int length = strlen(locationString);
    for (int i = 0; i < length; i += CHUNK_SIZE){

    //first 5 is the first number
    //space of 3
    //another 5 is the second number
    //space of 1
    //repeat - Total is 14

        char temp[NUM_DIGITS + 1];

        strncpy(temp, &locationString[i], NUM_DIGITS);
        temp[NUM_DIGITS] = '\0';
        leftNumbers[index] = atoi(temp);

        strncpy(temp, &locationString[i + NUM_DIGITS + 3], NUM_DIGITS);
        temp[NUM_DIGITS] = '\0';
        rightNumbers[index++] = atoi(temp);
    }
    bubbleSort(leftNumbers, index);
    bubbleSort(rightNumbers, index);
    return index;
}

void bubbleSort(int arr[], int n){
    int temp;
    for (int i = 0; i < n -1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (arr[j] > arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}