#include <stdio.h>
#include <string.h>

#define TAM 50

// Estrutura que representa uma carta de cidade
typedef struct {
    char estado[TAM];           // Estado da cidade
    int codigo;                 // Código identificador da carta
    char cidade[TAM];          // Nome da cidade
    int populacao;             // População da cidade
    float area;                // Área total em km²
    float pib;                 // Produto Interno Bruto (em bilhões)
    int pontosTuristicos;      // Número de pontos turísticos
} Carta;

// Função para cadastrar uma carta com input do usuário
void cadastrarCarta(Carta *c) {
    printf("\n--- Cadastro de Carta ---\n");

    printf("Estado: ");
    fgets(c->estado, TAM, stdin);
    c->estado[strcspn(c->estado, "\n")] = '\0'; // Remove o '\n' do final da string

    printf("Código da carta: ");
    scanf("%d", &c->codigo);
    getchar(); // Limpa o buffer do teclado

    printf("Nome da cidade: ");
    fgets(c->cidade, TAM, stdin);
    c->cidade[strcspn(c->cidade, "\n")] = '\0';

    printf("População: ");
    scanf("%d", &c->populacao);

    printf("Área (km²): ");
    scanf("%f", &c->area);

    printf("PIB (em bilhões): ");
    scanf("%f", &c->pib);

    printf("Número de pontos turísticos: ");
    scanf("%d", &c->pontosTuristicos);
    getchar(); // Limpa o buffer
}

// Exibe os dados de uma carta formatados
void exibirCarta(Carta c) {
    printf("\n--- Carta: %s ---\n", c.cidade);
    printf("Estado: %s\n", c.estado);
    printf("Código: %d\n", c.codigo);
    printf("População: %d\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: R$ %.2f bilhões\n", c.pib);
    printf("Pontos Turísticos: %d\n", c.pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km²\n", c.populacao / c.area);
}

// Retorna o valor numérico do atributo escolhido
float obterValorAtributo(Carta c, int atributo) {
    switch (atributo) {
        case 1: return (float)c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return (float)c.pontosTuristicos;
        case 5: return c.populacao / c.area; // Densidade populacional
        default: return -1.0;
    }
}

// Retorna o nome textual do atributo para exibição
char* nomeAtributo(int atributo) {
    switch (atributo) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Populacional";
        default: return "Desconhecido";
    }
}

// Realiza a comparação de duas cartas com até dois atributos
void compararCartas(Carta c1, Carta c2, int attr1, int attr2) {
    float v1_attr1 = obterValorAtributo(c1, attr1);
    float v2_attr1 = obterValorAtributo(c2, attr1);

    int vencedor = -1; // 0 = carta1, 1 = carta2, -1 = empate

    // Comparação do 1º atributo
    if (attr1 == 5) // Regra especial: densidade → menor vence
        vencedor = (v1_attr1 < v2_attr1) ? 0 : (v1_attr1 > v2_attr1 ? 1 : -1);
    else
        vencedor = (v1_attr1 > v2_attr1) ? 0 : (v1_attr1 < v2_attr1 ? 1 : -1);

    // Se empate, usar o segundo atributo (caso informado)
    if (vencedor == -1 && attr2 != 0) {
        float v1_attr2 = obterValorAtributo(c1, attr2);
        float v2_attr2 = obterValorAtributo(c2, attr2);

        if (attr2 == 5)
            vencedor = (v1_attr2 < v2_attr2) ? 0 : (v1_attr2 > v2_attr2 ? 1 : -1);
        else
            vencedor = (v1_attr2 > v2_attr2) ? 0 : (v1_attr2 < v2_attr2 ? 1 : -1);

        printf("\nEmpate no 1º atributo (%s), usando 2º atributo (%s) para desempate...\n",
               nomeAtributo(attr1), nomeAtributo(attr2));
    }

    // Exibe o resultado da comparação
    if (vencedor == 0)
        printf("🏆 Vencedora: %s (carta 1)\n", c1.cidade);
    else if (vencedor == 1)
        printf("🏆 Vencedora: %s (carta 2)\n", c2.cidade);
    else
        printf("⚖️ Empate! Nenhuma carta venceu.\n");
}

// Exibe o menu com os atributos disponíveis
void mostrarMenuAtributos() {
    printf("\n--- Atributos Disponíveis ---\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Turísticos\n");
    printf("5 - Densidade Populacional (menor vence)\n");
}

int main() {
    Carta carta1, carta2;
    int continuar = 1;

    printf("🧙‍♂️ Super Trunfo - Países (Nível Mestre)\n");

    // Cadastro das duas cartas
    printf("\n📥 Digite os dados da primeira carta:\n");
    cadastrarCarta(&carta1);

    printf("\n📥 Digite os dados da segunda carta:\n");
    cadastrarCarta(&carta2);

    // Exibição inicial das cartas
    exibirCarta(carta1);
    exibirCarta(carta2);

    // Loop de comparação interativo
    while (continuar) {
        int attr1, attr2;

        mostrarMenuAtributos();

        // Escolha do 1º atributo
        printf("\nEscolha o 1º atributo para comparação: ");
        scanf("%d", &attr1);

        // Verificação de 2º atributo opcional
        printf("Deseja escolher um 2º atributo para desempate? (0 = Não / 1 = Sim): ");
        scanf("%d", &attr2);

        if (attr2 == 1) {
            printf("Escolha o 2º atributo: ");
            scanf("%d", &attr2);
        } else {
            attr2 = 0; // Nenhum atributo secundário
        }

        // Realiza a comparação
        compararCartas(carta1, carta2, attr1, attr2);

        // Pergunta se o usuário quer continuar
        printf("\nDeseja fazer outra comparação? (1 = Sim / 0 = Não): ");
        scanf("%d", &continuar);
    }

    printf("\n🚪 Programa encerrado. Até logo!\n");
    return 0;
}