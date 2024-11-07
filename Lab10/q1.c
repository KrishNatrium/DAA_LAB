/*
The difference between this problem and the fractional one is that you can&#39;t take a
fraction of an item. You either take the whole thing or none of it. So here, is the
problem formally described:
Your goal is to maximize the value of a knapsack that can hold at most W units worth of
goods from a list of items I0, I1, ... In1. Each item has two attributes:
1) Value - let this be vi for item Ii.
2) Weight - let this be wi for item Ii.
Now, instead of being able to take a certain weight of an item, you can only either
take the item or not take the item.
To illustrate this, consider the following example:
Item Weight Value
I0 3 10
I1 8 4
I2 9 9
I3 8 11
The maximum weight the knapsack can hold is 20.
*/

#include <stdio.h>

int knapsack(int W, int n, int weights[], int values[])
{
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }
            else if (weights[i - 1] <= w)
            {
                dp[i][w] = (dp[i - 1][w] > dp[i - 1][w - weights[i - 1]] + values[i - 1])
                               ? dp[i - 1][w]
                               : dp[i - 1][w - weights[i - 1]] + values[i - 1];
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][W];
}

int main()
{
    int values[] = {10, 4, 9, 11};
    int weights[] = {3, 8, 9, 8};
    int W = 20;
    int n = sizeof(values) / sizeof(values[0]);

    int max_value = knapsack(W, n, weights, values);

    printf("Maximum value in the knapsack: %d\n", max_value);

    return 0;
}
