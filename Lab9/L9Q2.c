#include <stdio.h>
#include <string.h>

void findLCS(char *str1, char *str2, int m, int n) {
    int LCS_table[m+1][n+1];
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                LCS_table[i][j] = 0;
            else if (str1[i-1] == str2[j-1])
                LCS_table[i][j] = LCS_table[i-1][j-1] + 1;
            else
                LCS_table[i][j] = (LCS_table[i-1][j] > LCS_table[i][j-1]) ? LCS_table[i-1][j] : LCS_table[i][j-1];
        }
    }
    
    int index = LCS_table[m][n];
    char lcs[index+1];
    lcs[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (str1[i-1] == str2[j-1]) {
            lcs[index-1] = str1[i-1];
            i--;
            j--;
            index--;
        } else if (LCS_table[i-1][j] > LCS_table[i][j-1])
            i--;
        else
            j--;
    }

    printf("LCS: %s\n", lcs);
    printf("LCS Length: %d\n", LCS_table[m][n]);
}

int main() {
    char str1[100], str2[100];
    printf("Enter the first string into an array: ");
    scanf("%s", str1);
    printf("Enter the second string into an array: ");
    scanf("%s", str2);

    int m = strlen(str1);
    int n = strlen(str2);
    findLCS(str1, str2, m, n);

    return 0;
}
