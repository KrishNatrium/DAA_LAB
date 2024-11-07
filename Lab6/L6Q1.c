#include<stdio.h>
#include<stdlib.h>

void swap(int *x, int *y) 
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void maxHeapify(int arr[], int n, int i) 
{
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void minHeapify(int arr[], int n, int i)
{
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    
    if (left < n && arr[left] < arr[smallest])
        smallest = left;
    
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void intMax(int arr[], int n, int k) 
{
    int i = n;
    arr[i] = k;
    while (i > 0 && arr[i] > arr[(i-1)/2]) 
    {
        swap(&arr[i], &arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

void intMin(int arr[], int n, int k) 
{
    int i = n;
    arr[i] = k;
    while (i > 0 && arr[i] < arr[(i-1)/2]) 
    {
        swap(&arr[i], &arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

void extMax(int arr[], int* n) 
{
    if (*n == 0)
        return;

    swap(&arr[0], &arr[*n - 1]);
    (*n)--;
    maxHeapify(arr, *n, 0);
}

void extMin(int arr[], int* n) 
{
    if (*n == 0)
        return;

    swap(&arr[0], &arr[*n - 1]);
    (*n)--;
    minHeapify(arr, *n, 0);
}

void delMax(int arr[], int* n, int index) 
{
    if (*n <= 0 || index >= *n)
        return;

    arr[index] = arr[*n - 1];
    (*n)--;
    maxHeapify(arr, *n, index);
}

void delMin(int arr[], int* n, int index) 
{
    if (*n <= 0 || index >= *n)
        return;

    arr[index] = arr[*n - 1];
    (*n)--;
    minHeapify(arr, *n, index);
}

void printArray(int arr[], int n) 
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void hsMax(int arr[], int n)
{
    for (int i = n/2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
        
    for (int i = n-1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        maxHeapify(arr, i, 0);
    }
}


void hsMin(int arr[], int n)
{
    for (int i = n/2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);

    for (int i = n-1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        minHeapify(arr, i, 0);
    }
}

int main() 
{
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int maxHeap[n+10];
    int minHeap[n+10];
    int maxHeapSize = n;
    int minHeapSize = n;

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &maxHeap[i]);
        minHeap[i] = maxHeap[i];
    }

    for (int i = maxHeapSize/2 - 1; i >= 0; i--)
        maxHeapify(maxHeap, maxHeapSize, i);

    for (int i = minHeapSize/2 - 1; i >= 0; i--)
        minHeapify(minHeap, minHeapSize, i);

    int choice, k, z, index;
    while (1) 
    {
        printf("\nMenu:\n");
        printf("1. Insert into Max Heap\n");
        printf("2. Insert into Min Heap\n");
        printf("3. Extract Max\n");
        printf("4. Extract Min\n");
        printf("5. Print Max Heap\n");
        printf("6. Print Min Heap\n");
        printf("7. Delete from Max Heap\n");
        printf("8. Delete from Min Heap\n");
        printf("9. Heap Sort Max Heap\n");
        printf("10. Heap Sort Min Heap\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter the element to insert into Max Heap: ");
                scanf("%d", &k);
                intMax(maxHeap, maxHeapSize++, k);
                printf("Max Heap after insertion:\n");
                printArray(maxHeap, maxHeapSize);
                break;

            case 2:
                printf("Enter the element to insert into Min Heap: ");
                scanf("%d", &k);
                intMin(minHeap, minHeapSize++, k);
                printf("Min Heap after insertion:\n");
                printArray(minHeap, minHeapSize);
                break;

            case 3:
                printf("How many times do you want to extract max: ");
                scanf("%d", &z);
                for (int i = 0; i < z && maxHeapSize > 0; i++) 
                {
                    extMax(maxHeap, &maxHeapSize);
                    printf("Max Heap after extracting max %d times:\n", i+1);
                    printArray(maxHeap, maxHeapSize);
                }
                break;

            case 4:
                printf("How many times do you want to extract min: ");
                scanf("%d", &z);
                for (int i = 0; i < z && minHeapSize > 0; i++) 
                {
                    extMin(minHeap, &minHeapSize);
                    printf("Min Heap after extracting min %d times:\n", i+1);
                    printArray(minHeap, minHeapSize);
                }
                break;

            case 5:
                printf("Max Heap:\n");
                printArray(maxHeap, maxHeapSize);
                break;

            case 6:
                printf("Min Heap:\n");
                printArray(minHeap, minHeapSize);
                break;

            case 7:
                printf("Enter the index to delete from Max Heap: ");
                scanf("%d", &index);
                delMax(maxHeap, &maxHeapSize, index);
                printf("Max Heap after deletion:\n");
                printArray(maxHeap, maxHeapSize);
                break;

            case 8:
                printf("Enter the index to delete from Min Heap: ");
                scanf("%d", &index);
                delMin(minHeap, &minHeapSize, index);
                printf("Min Heap after deletion:\n");
                printArray(minHeap, minHeapSize);
                break;

            case 9:
                printf("Heap Sorting Max Heap:\n");
                hsMax(maxHeap, maxHeapSize);
                printArray(maxHeap, maxHeapSize);
                break;

            case 10:
                printf("Heap Sorting Min Heap:\n");
                hsMin(minHeap, minHeapSize);
                printArray(minHeap, minHeapSize);
                break;

            case 11:
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}