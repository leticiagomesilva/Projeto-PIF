#include <stdio.h>

// Função para exibir a matriz no console
void displayMatrix(char matrix[][30], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Matriz para representar uma galinha simples
    char chicken[4][30] = {
        "     _/\\_            ",
        "    (  o )>            ",
        "   /(  \" )      ",
        "     _/_/            ",
    };

    // Exibe a matriz no console
    displayMatrix(chicken, 4, 30);

    return 0;
}
