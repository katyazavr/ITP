#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// function to check if given number string is valid based on base provided
int checknum(char *number, int not){
    int length;
    length = strlen(number);  // find length of number string

    int check;

    // define valid characters for different bases
    char not2[10] = "01";  // valid digits for binary system 
    char not8[20] = "01234567";  // valid digits for octal system
    char not10[20] = "0123456789";  // valid digits for decimal system
    char not16[20] = "0123456789ABCDEF";  // valid digits for hexadecimal system

    // check if number belongs to binary
    if (not == 2) {
        for (int i = 0; i < length; i++) {
            int check = 0;
            for (int j = 0; j < not; j++) {
                if (number[i] == not2[j]) {
                    check++;
                }
            }
            if (check == 0) { 
                return 0;
            }
        }
        return 1;
    }

    // check if number belongs to octal
    else if (not == 8) {
        for (int i = 0; i < length; i++) {
            int check = 0;
            for (int j = 0; j < not; j++) {
                if (number[i] == not8[j]) {
                    check++;
                }
            }
            if (check == 0) {
                return 0;
            }
        }
        return 1;
    }

    // check if number belongs to decimal
    else if (not == 10) {
        for (int i = 0; i < length; i++) {
            int check = 0;
            for (int j = 0; j < not; j++) {
                if (number[i] == not10[j]) {
                    check++;
                }
            }
            if (check == 0) {
                return 0;
            }
        }
        return 1;
    }

    // check if number belongs to hexadecimal
    else if (not == 16) {
        for (int i = 0; i < length; i++) {
            int check = 0;
            for (int j = 0; j < not; j++) {
                if (number[i] == not16[j]) {
                    check++;
                }
            }
            if (check == 0) {
                return 0;
            }
        }
        return 1;
    }
}

// function to calculate the power of a number
int poww(int not, int order){
    int rez = 1;
    for (int i = 0; i < order; i++) {
        rez *= not;
    }
    return rez;
}

// function to convert a number string from specific base to decimal
int calc(char *number, int not){
    int finalnum = 0;

    // characters representing digits for all bases
    char z[2] = "0", o[2] = "1", w[2] = "2", t[2] = "3";
    char fo[2] = "4", v[2] = "5", s[2] = "6", se[2] = "7";
    char ei[2] = "8", n[2] = "9", a[2] = "A", b[2] = "B";
    char c[2] = "C", d[2] = "D", e[2] = "E", f[2] = "F";

    int length = strlen(number); 

    // loop through each digit and convert based on the base provided
    for (int i = 0; i < length; i++) {
        // convert digits directly
        if (number[i] == a[0]) { finalnum += 10 * poww(not, length-i-1); }
        else if (number[i] == b[0]) { finalnum += 11 * poww(not, length-i-1); }
        else if (number[i] == c[0]) { finalnum += 12 * poww(not, length-i-1); }
        else if (number[i] == d[0]) { finalnum += 13 * poww(not, length-i-1); }
        else if (number[i] == e[0]) { finalnum += 14 * poww(not, length-i-1); }
        else if (number[i] == f[0]) { finalnum += 15 * poww(not, length-i-1); }
        else if (number[i] == z[0]) { finalnum += 0 * poww(not, length-i-1); }
        else if (number[i] == o[0]) { finalnum += 1 * poww(not, length-i-1); }
        else if (number[i] == w[0]) { finalnum += 2 * poww(not, length-i-1); }
        else if (number[i] == t[0]) { finalnum += 3 * poww(not, length-i-1); }
        else if (number[i] == fo[0]) { finalnum += 4 * poww(not, length-i-1); }
        else if (number[i] == v[0]) { finalnum += 5 * poww(not, length-i-1); }
        else if (number[i] == s[0]) { finalnum += 6 * poww(not, length-i-1); }
        else if (number[i] == se[0]) { finalnum += 7 * poww(not, length-i-1); }
        else if (number[i] == ei[0]) { finalnum += 8 * poww(not, length-i-1); }
        else if (number[i] == n[0]) { finalnum += 9 * poww(not, length-i-1); }
    }
    return finalnum;
}

int main(){
    // open input and output files
    FILE *filein;
    filein = fopen("input.txt", "r"); 

    FILE *fileout;
    fileout = fopen("output.txt", "w");

    if (filein == NULL) {
        fprintf(fileout, "%s", "Invalid inputs\n");
        return 0;
    }
    
    char nstr[100];
    if (fgets(nstr, 100, filein) == NULL) {
        fprintf(fileout, "%s", "Invalid inputs\n");
        return 0;
    }
    long int n = strtol(nstr, NULL, 10);

    // check if N is within valid range
    if (n < 1 || n > 40) {
        fprintf(fileout, "%s", "Invalid inputs\n");
    } else {
        char listnum[n][100];
        for (int i = 0; i < n; i++) {
            fscanf(filein, "%s", listnum[i]);
        }

        int sum = 0;  // sum of the modified numbers
        int notation;
        int input = 0;

        // process each number
        for (int i = 0; i < n; i++) {
            fscanf(filein, "%d", &notation);  // read the base of the current number
            if (notation == 2 || notation == 8 || notation == 10 || notation == 16) {
                int result = checknum(listnum[i], notation);  // check if the number is valid
                input += result;
                if (result == 1) {
                    // perform the arithmetic operation
                    if (i % 2 == 0) {
                        sum += calc(listnum[i], notation) - 10;
                    } else {
                        sum += calc(listnum[i], notation) + 10;
                    }
                } else {
                    fprintf(fileout, "%s", "Invalid inputs\n"); 
                    return 0;
                }
            } else {
                fprintf(fileout, "%s", "Invalid inputs\n"); 
                return 0;
            }
        }

        // check if there is unexpected number
        if (fscanf(filein, "%d", &notation) == 1) {
            fprintf(fileout, "%s", "Invalid inputs\n");
            return 0;
        }

        // print result
        if (input == n) {
            fprintf(fileout, "%d\n", sum);
        }
    }
    fclose(filein);
    fclose(fileout);
    
    return 0;
}