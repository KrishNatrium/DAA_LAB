#include <stdio.h>
#include <stdlib.h>

void findDuplicatesAndMostRepeating(int arr[], int n, int *totalDuplicates, int *mostRepeating) {
    int maxCount = 0;
    *totalDuplicates = 0;

    for (int i = 0; i < n; i++) {
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }

        if (count > 1) {
            *totalDuplicates += count - 1;
        }

        if (count > maxCount) {
            maxCount = count;
            *mostRepeating = arr[i];
        }
    }
}

int main() {
    FILE *file;
    int n;

    printf("Enter how many numbers you want to read from file: ");
    scanf("%d", &n);

    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);

    printf("The content of the array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int totalDuplicates, mostRepeating;

    findDuplicatesAndMostRepeating(arr, n, &totalDuplicates, &mostRepeating);

    printf("Total number of duplicate values = %d\n", totalDuplicates);
    printf("The most repeating element in the array = %d\n", mostRepeating);

    free(arr);

    return 0;
}
