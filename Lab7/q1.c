#include <stdio.h>

struct ITEM
{
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio; // This will store the profit/weight ratio
};

// Function to swap two items
void swap(struct ITEM *a, struct ITEM *b)
{
    struct ITEM temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort items by profit/weight ratio in descending order (using bubble sort)
void sortItemsByRatio(struct ITEM arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i].profit_weight_ratio < arr[j].profit_weight_ratio)
            {
                swap(&arr[i], &arr[j]);
            }
        }
    }
}

// Function to calculate maximum profit using the Fractional Knapsack approach
float fractionalKnapsack(struct ITEM items[], int n, float capacity)
{
    float max_profit = 0.0;
    float remaining_capacity = capacity;

    // Output the details of each item and how much can be taken
    printf("\nItem No Profit Weight Amount to be taken\n");

    for (int i = 0; i < n; i++)
    {
        if (items[i].item_weight <= remaining_capacity)
        {
            // Take the whole item
            remaining_capacity -= items[i].item_weight;
            printf("%d %.6f %.6f 1.000000\n", items[i].item_id, items[i].item_profit, items[i].item_weight);
            max_profit += items[i].item_profit;
        }
        else
        {
            // Take the fraction of the item
            float fraction = remaining_capacity / items[i].item_weight;
            max_profit += items[i].item_profit * fraction;
            printf("%d %.6f %.6f %.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, fraction);
            break; // No more capacity to add anything else
        }
    }

    return max_profit;
}

int main()
{
    int n;
    float capacity;

    // Input the number of items
    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct ITEM items[n];

    // Input the profit and weight for each item
    for (int i = 0; i < n; i++)
    {
        items[i].item_id = i + 1;
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].item_profit, &items[i].item_weight);
        // Calculate the profit/weight ratio for each item
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    // Input the capacity of the knapsack
    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);

    // Sort items by profit/weight ratio in descending order
    sortItemsByRatio(items, n);

    // Calculate and output the maximum profit
    float max_profit = fractionalKnapsack(items, n, capacity);

    // Output the maximum profit
    printf("\nMaximum profit: %.6f\n", max_profit);

    return 0;
}
