#include <stdio.h>
#include <stdlib.h>

void decimalToBinary(int n, char *binary, int index) {
    if (index >= 0) {
        binary[index] = (n % 2) + '0';
        decimalToBinary(n / 2, binary, index - 1);
    }
}

void writeBinaryToFile(FILE *outputFile, int number) {
    char binary[17] = "0000000000000000";
    decimalToBinary(number, binary, 15);
    binary[16] = '\0';
    fprintf(outputFile, "The binary equivalent of %d is %s\n", number, binary);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <source file> <destination file>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    char *sourceFileName = argv[2];
    char *destFileName = argv[3];

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

    int number, count = 0;
    while (count < n && fscanf(sourceFile, "%d", &number) == 1) {
        writeBinaryToFile(destFile, number);
        count++;
    }

    fclose(sourceFile);
    fclose(destFile);

    destFile = fopen(destFileName, "r");
    if (destFile == NULL) {
        perror("Error reopening destination file");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), destFile)) {
        printf("%s", line);
    }

    fclose(destFile);
    return 0;
}
