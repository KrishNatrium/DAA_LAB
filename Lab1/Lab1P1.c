#include <stdio.h>
#include <limits.h>

void findSecondSmallestAndLargest(int arr[], int n, int *secondSmallest, int *secondLargest) {
    int firstSmallest, firstLargest;
    firstSmallest = firstLargest = INT_MAX;
    *secondSmallest = *secondLargest = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (arr[i] < firstSmallest) {
            firstSmallest = arr[i];
        }
    }

    for (int i = 0; i < n; i++) {
        if (arr[i] > firstSmallest && arr[i] < *secondSmallest) {
            *secondSmallest = arr[i];
        }
    }

    firstLargest = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (arr[i] > firstLargest) {
            firstLargest = arr[i];
        }
    }


    *secondLargest = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (arr[i] < firstLargest && arr[i] > *secondLargest) {
            *secondLargest = arr[i];
        }
    }


    if (*secondSmallest == INT_MAX) {
        *secondSmallest = firstSmallest;
    }
    if (*secondLargest == INT_MIN) {
        *secondLargest = firstLargest;
    }
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];


    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int secondSmallest, secondLargest;

    findSecondSmallestAndLargest(arr, n, &secondSmallest, &secondLargest);

    if (n < 2) {
        printf("Array needs to have at least two elements to find second smallest and second largest elements.\n");
    } else {
        printf("The second smallest element is %d\n", secondSmallest);
        printf("The second largest element is %d\n", secondLargest);
    }

    return 0;
}