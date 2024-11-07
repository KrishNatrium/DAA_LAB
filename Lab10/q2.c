/*
2. Aim of the program: Write a program to implement the matrix chain multiplication
problem using M-table &amp; S-table to find optimal parenthesization of a matrix-chain
product. Print the number of scalar multiplications required for the given input.
Note# Dimensions of the matrices can be inputted as row and column values. Validate
the dimension compatibility.
Input:
Enter number of matrices: 4
Enter row and col size of A1: 30 35
Enter row and col size of A2: 35 15
Enter row and col size of A3: 15 5
Enter row and col size of A4: 5 10
Output:
M Table:
0 15750 7875 9375
0 0 2625 4375
0 0 0 750
0 0 0 0
S Table:
0 1 1 3
0 0 2 3
0 0 0 3
0 0 0 0
Optimal parenthesization: ( ( A1 (A2 A3)) A4)
The optimal ordering of the given matrices requires 9375 scalar multiplications.
*/

#include <stdio.h>
#include <limits.h>

void print_optimal_parenthesization(int i, int j, int n, int s[][n], char *name)
{
    if (i == j)
    {
        printf("%c", (*name)++);
    }
    else
    {
        printf("(");
        print_optimal_parenthesization(i, s[i][j], n, s, name);
        print_optimal_parenthesization(s[i][j] + 1, j, n, s, name);
        printf(")");
    }
}

void matrix_chain_order(int p[], int n)
{
    int m[n][n];
    int s[n][n];
    for (int i = 1; i < n; i++)
    {
        m[i][i] = 0;
    }
    for (int L = 2; L < n; L++)
    {
        for (int i = 1; i < n - L + 1; i++)
        {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k < j; k++)
            {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("\nM Table:\n");
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (i > j)
            {
                printf("0\t");
            }
            else
            {
                printf("%d\t", m[i][j]);
            }
        }
        printf("\n");
    }

    printf("\nS Table:\n");
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (i > j)
            {
                printf("0\t");
            }
            else
            {
                printf("%d\t", s[i][j]);
            }
        }
        printf("\n");
    }
    printf("\nOptimal parenthesization: ");
    char name = 'A';
    print_optimal_parenthesization(1, n - 1, n, s, &name);
    printf("\n");
    printf("The optimal ordering of the given matrices requires %d scalar multiplications.\n", m[1][n - 1]);
}

int main()
{
    int n;
    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int p[n + 1];
    printf("Enter the row and col size of A1: ");
    scanf("%d %d", &p[0], &p[1]);

    for (int i = 2; i <= n; i++)
    {
        printf("Enter the row and col size of A%d: ", i);
        int row, col;
        scanf("%d %d", &row, &col);
        if (p[i - 1] != row)
        {
            printf("Matrix dimensions are incompatible for multiplication. Exiting.\n");
            return 1;
        }
        p[i] = col;
    }
    matrix_chain_order(p, n + 1);

    return 0;
}
