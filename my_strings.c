/*
 * YOUR WORK GOES HERE!
 *
 * STUDENT_ID: 2415020
 *
 * ADDITIONAL COMMENTS (if any):
 * I decided to include the string.h standard library to manipulate the given arrays of characters . Since the header file shouldn't be modified,
 * I included the library within the main_strings.c file. The functions that I'm using are:
 *  - strlen(const char *str) - which computes the length of the string str up to but not including the terminating null character.
 *  - strncat(char *dest, const char *src, size_t n) - Appends the string pointed to, by src to the end of the string pointed to,
 *                                                     by dest up to n characters long.
 *  - memmove(void *dest, const void *src, size_t n) - Function to copy n characters from src to dest.
 *  - strstr(const char *haystack, const char *needle) - Finds the first occurrence of the entire string needle (not including
 *                                                       the terminating null character) which appears in the string haystack.
 */


#include "my_strings.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_STR 20

/**
 * Returns the length s, which is the number of characters in s.
 * The null string would have a length of 0
 * @param s
 * @return
 */
int length(const char s[])
{
    if(s == NULL) return 0; //if string is a null string the returns 0
    else return strlen(s); //otherwise returns the length of the string
}

void reverse(char s[])
{
    const int FIRST_POSITION = 0, LAST_POSITION = strlen(s) - 1; //constants to avoid magic numbers
    int first = FIRST_POSITION, last = LAST_POSITION; //initialisation of the character's array first and last element
    char temp; //temporary char which is needed to reverse the order of the characters
    while (first < last) {
        temp = s[first]; //assign first element to temp
        s[first] = s[last]; //assign last element of char array to current first cell
        s[last] = temp; //assign temp to the current last cell
        first++; //increments the first element to iterate through the char array
        last--; //decrements the last element to iterate though the array
    }
}

void insert(char s1[], const char s2[], int n) {
    if (!isalnum(n)) { //parameter validation; if n is not an alphanumeric, therefore it's an integer
        if(n<0 || n>=MAX_STR){ //if n is less than the zero or larger than the array length
            fprintf(stderr, "The position needs to be greater than zero and less than MAX_STR\n");
            exit(EXIT_FAILURE);
        }
        else if (n >= strlen(s1)) strncat(s1, s2, n); //if n is greater than the length of s1, appends s2 to s1
        else { //otherwise insert s2 to the nth position of s1; if n is equal to zero prepend s2 to s1
            memmove(s1 + n + strlen(s2), s1 + n, MAX_STR + 1); //moves content of s1 after the nth position, to the position of s1 + the given number (n) + the length of the s2
            memmove(s1 + n, s2, strlen(s2)); //since now there's space for s2, inserts s2 to the nth position of s1 by s2 length, hence s1 and s2 are now combined
        }
    } else { //otherwise outputs an appropriate error and terminates the program.
        fprintf(stderr,"Position cannot be an alphanumeric/character.\n");
        exit(EXIT_FAILURE);
    }
}

bool search(const char s1[], const char s2[])
{
    if(s1 && (strstr(s1,s2) || s2 == NULL)) return true; //if s2 is substring of s1, or s2 is a null string it returns true
    else return false; //otherwise it returns false
}

int main_strings() {

    printf ("Length of \"Hello!\" is %d.\n" , length("Hello!"));

    char str[MAX_STR + 1] = "Hello!";
    printf("The reverse of %s", str);
    reverse(str);
    printf(" is %s.\n", str);

    char ab[MAX_STR + 1] = "Alice and Bob";
    char  b[MAX_STR + 1] = "Alice";

    if(search(ab, b) == true) {
        printf("String '%s' is in '%s'!\n", b, ab);
    } else {
        printf("String '%s' is NOT in '%s'!\n", b, ab);
    }

    insert(ab, b, 5);
    printf("Combine strings: %s.\n", ab);

    return 0;
}