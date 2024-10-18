#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source file> <destination file>\n", argv[0]);
        return 1;
    }

    char *sourceFileName = argv[1];
    char *destFileName = argv[2];

    FILE *sourceFile = fopen(sourceFileName, "r");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return 1;
    }

    FILE *destFile = fopen(destFileName, "w");
    if (destFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
        return 1;
    }

    int num1, num2;
    int pairCount = 0;
    
    while (fscanf(sourceFile, "%d %d", &num1, &num2) == 2) {
        int result = gcd(num1, num2);
        fprintf(destFile, "The GCD of %d and %d is %d\n", num1, num2, result);
        pairCount++;
    }

    if (pairCount < 3) {
        printf("Error: The source file must contain at least 3 pairs of numbers.\n");
        fclose(sourceFile);
        fclose(destFile);
        return 1;
    }

    fclose(sourceFile);
    fclose(destFile);

    printf("GCD results have been written to %s\n", destFileName);
    return 0;
}
