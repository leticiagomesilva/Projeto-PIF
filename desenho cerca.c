#include <stdio.h>

// Função para exibir uma imagem (matriz) no console
void displayImage(char image[][7], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", image[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Exemplo de uma imagem representada por uma matriz de caracteres
    char smiley[2][7] = {
        { '|', '-', '-', '|', '-', '-', '|' },
        { '|', '-', '-', '|', '-', '-',  '|' },
    };

    // Exibe a imagem no console
    displayImage(smiley, 2, 7);

    return 0;
}
