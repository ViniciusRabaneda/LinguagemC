#include <stdio.h> // biblioteca padrão de interação
#include <locale.h> // permite uso de caracteres especiais
#include <stdlib.h> // função rand
#include <string.h> // utilizada para puxar a função strlen
#include <time.h> // biblioteca utilizada para gerar valores randomicos
#include "forca.h" // funções declaradas em outro header que criamos


char palavrasecreta[TAMANHO_PALAVRA]; // É uma variavel global declarada no header forca.h 
char chutes[26];
int chutesdados = 0;


int letraexiste(char letra) {
	int j;
    for(j = 0; j < strlen(palavrasecreta); j++) {
        if(letra == palavrasecreta[j]) {
            return 1;
        }
    }

    return 0;
}

int chuteserrados() {
    int erros = 0;
	int i;
    for( i = 0; i < chutesdados; i++) {

        if(!letraexiste(chutes[i])) {
            erros++;
        }
    }

    return erros;
}

int enforcou() {
    return chuteserrados() >= 5;
}

int ganhou() {
    int i;
	for( i = 0; i < strlen(palavrasecreta); i++) {
        if(!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }

    return 1;
}


void abertura() {
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}

void chuta() {
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    if(letraexiste(chute)) {
        printf("Você acertou: a palavra tem a letra %c\n\n", chute);
    } else {
        printf("\nVocê errou: a palavra NÃO tem a letra %c\n\n", chute);
    }

    chutes[chutesdados] = chute;
    chutesdados++;
}

int jachutou(char letra) {
    int achou = 0;
    int j;
	for(j = 0; j < chutesdados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}

void desenhaforca() {

    int erros = chuteserrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' ')); // if ternário, utilizado quando ou é uma coisa ou outra. No caso aqui de acordo com o numero de erros o programa exibe a parte do corpo ou vazio
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    int i;
	for(i = 0; i < strlen(palavrasecreta); i++) { // percorre letra por letra da palavra

        if(jachutou(palavrasecreta[i])) { // compara os espaços do vetor com o chute do usuário devolvendo o espaço fechado ou com a letra
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }

    }
    printf("\n");

}

void escolhepalavra() {
    FILE* f;  // abre o conteudo do arquivo

    f = fopen("palavras.txt", "r"); // lê o arquivo
    if(f == 0) {
        printf("Banco de dados de palavras não disponível\n\n"); //verifica se tem algo dentro
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras); // le a quantidade de palavras

    srand(time(0)); // gera um valor randomico apartir de uma semente calculada através do time APOCHE
    int randomico = rand() % qtddepalavras; // utilizado para delimitar o número maximo de valores gerados!

    int i;
	for( i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}


void adicionapalavra() {
    char quer;

    printf("Você deseja adicionar uma nova palavra no jogo (S/N)?");
    scanf(" %c", &quer);

    if(quer == 'S') {
        char novapalavra[TAMANHO_PALAVRA];

        printf("Digite a nova palavra, em letras maiúsculas: ");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");
        if(f == 0) {
            printf("Banco de dados de palavras não disponível\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);

    }

}

int main() {
	setlocale(LC_ALL, "Portuguese");
    abertura();
    escolhepalavra();

    do {

        desenhaforca();
        chuta();

    } while (!ganhou() && !enforcou());

    if(ganhou()) {
        printf("Você ganhou!\n\n");

    } else {
        printf("Você foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);
    }

    adicionapalavra();
}
