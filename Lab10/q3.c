/*
3. Aim of the program: Write a program to find out the Longest Common
Subsequence of two given strings. Calculate length of the LCS.
Input:

Enter the first string into an array: 10010101
Enter the second string into an array: 010110110

Output:
LCS: 100110
LCS Length: 6
*/

#include <stdio.h>
#include <string.h>

#define MAX 100

void lcs(char *X, char *Y, int m, int n, int dp[MAX][MAX])
{
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
            {
                dp[i][j] = 0;
            }
            else if (X[i - 1] == Y[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                if (dp[i - 1][j] > dp[i][j - 1])
                {
                    dp[i][j] = dp[i - 1][j];
                }
                else
                {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
    }
}

void printLCS(char *X, char *Y, int m, int n, int dp[MAX][MAX])
{
    int index = dp[m][n];
    char lcs[index + 1];
    lcs[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }
    printf("LCS: %s\n", lcs);
    printf("LCS Length: %d\n", dp[m][n]);
}

int main()
{
    char X[MAX], Y[MAX];
    int dp[MAX][MAX];

    printf("Enter string of length 100\n");
    printf("Enter the first string : ");
    scanf("%s", X);
    printf("Enter the second string : ");
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    lcs(X, Y, m, n, dp);

    printLCS(X, Y, m, n, dp);

    return 0;
}
