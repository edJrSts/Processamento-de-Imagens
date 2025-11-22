#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char tipo[3];
    int colunas;
    int linhas;
    int maxValPixel;
    int pixels[];
} Imagem;

void lerImagem(FILE *input, Imagem **imagem)
{

    char tipo[3];
    if (fscanf(input, "%2s", tipo) != 1)
    {
        printf("Erro ao ler tipo da imagem!\n");
        return;
    }

    // Lendo dimensoes da imagem
    int colunas, linhas;
    if (fscanf(input, "%d %d", &colunas, &linhas) != 2)
    {
        printf("Erro ao ler dimensoes!\n");
        return;
    }

    int maxVal;
    if (fscanf(input, "%d", &maxVal) != 1)
    {
        printf("Erro ao ler dimensoes!\n");
        return;
    }

    long totalPixels = colunas * linhas;

    Imagem *img = malloc(sizeof(Imagem) + totalPixels * sizeof(int));

    strcpy(img->tipo, tipo);
    img->colunas = colunas;
    img->linhas = linhas;
    img->maxValPixel = maxVal;

    for (int i = 0; i < totalPixels; i++)
    {
        if (fscanf(input, "%d", &img->pixels[i]) != 1)
        {
            printf("Erro ao ler pixel %d\n", i);
            free(img);
            return;
        }
    }

    *imagem = img;
}

void salvarImagem(FILE *output, Imagem *imagem)
{
    fprintf(output, "%s\n", imagem->tipo);                   // ex: "P2"
    fprintf(output, "%d %d\n", imagem->colunas, imagem->linhas);
    fprintf(output, "%d\n", imagem->maxValPixel);

    int totalPixels = imagem->colunas * imagem->linhas;
    for (int i = 0; i < totalPixels;i++){
        fprintf(output, "%d\n", imagem->pixels[i]);  
    }
}

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        fprintf(stderr, "Uso: %s <arquivo_de_entrada> <arquivo_de_saida>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    Imagem *imagem = NULL;
    
    lerImagem(input, &imagem);
    salvarImagem(output, imagem);

    free(imagem);

    fclose(input);
    fclose(output);

    return 0;
}