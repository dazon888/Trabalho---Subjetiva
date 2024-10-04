#include <iostream>
#include <cctype>

void verificarDisponibilidade(char reserva[10][6], int fileira, int assento) {
    if (reserva[fileira - 1][assento] == 'x') {
        printf("\nAssento indisponível, por favor escolha outro.");
    } else {
        reserva[fileira - 1][assento] = 'x'; // Reserva o assento
        printf("\nAssento reservado com sucesso!");
    }
}

bool boasVindas() {
    char resposta;
    printf("Bem-vindo à Ateneu Airlines! Este é o sistema de reserva de assentos\n");
    printf("Deseja começar a reservar assentos? (s/n): ");
    scanf(" %c", &resposta);

    return (resposta == 's' || resposta == 'S');
}

void visualizarAssentos(char reserva[10][6]) {
    printf("\n\t\t[A] [B] [C]\t[D] [E] [F]\n");
    for (int x = 0; x < 10; x++) {
        if (x != 9) printf("\n\t0%d\t", x + 1);
        else printf("\n\t%d\t", x + 1);
        
        for (int y = 0; y < 6; y++) {
            printf("[%c] ", reserva[x][y]);
            if (y == 2) {
                printf("\t");
            }
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    char reserva[10][6] = {
        {' ', ' ', 'x', ' ', ' ', ' '}, 
        {' ', ' ', ' ', 'x', ' ', ' '}, 
        {' ', ' ', ' ', ' ', ' ', ' '},
        {'x', ' ', ' ', ' ', ' ', ' '}, 
        {' ', ' ', ' ', ' ', 'x', ' '}, 
        {' ', ' ', ' ', ' ', ' ', ' '},
        {' ', 'x', ' ', ' ', ' ', ' '}, 
        {' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' '}
    }; // Já deixei alguns assentos previamente reservados, à fim de uma experiência mais "realista"

    if (!boasVindas()) {
        printf("\nObrigado por sua visita! Até a próxima!");
        return 0;
    }

    char visualizar;
    printf("\nDeseja visualizar os assentos disponíveis? (s/n): ");
    scanf(" %c", &visualizar);

    if (visualizar == 's' || visualizar == 'S') {
        visualizarAssentos(reserva);
    }

    int fileira;
    char poltrona;
    char tipoPassagem;

    // Escolha entre passagem Econômica ou Executiva
    printf("\nEscolha o tipo de passagem (E - Econômica, X - Executiva): ");
    scanf(" %c", &tipoPassagem);
    
    while (true) {
        printf("\nDigite a fileira (1-10): ");
        scanf("%d", &fileira);
        printf("\nDigite a poltrona [A][B][C][D][E][F]: ");
        scanf(" %c", &poltrona);
        
        int assento = -1;
        
        poltrona = tolower(poltrona); //tolower é da biblioteca cctype que permite que o código seja insensível à Caixa
        
        switch(poltrona) {
            case 'a': assento = 0; break;
            case 'b': assento = 1; break;
            case 'c': assento = 2; break;
            case 'd': assento = 3; break;
            case 'e': assento = 4; break;
            case 'f': assento = 5; break;
            default:
                printf("\nPoltrona inválida. Tente novamente.");
                continue;
        }

        // Verifica se o assento está disponível
        if (tipoPassagem == 'e' || tipoPassagem == 'E') {
            if (poltrona == 'a' || poltrona == 'f') {
          
                printf("\nPassagem Econômica: Não é permitido reservar poltronas A e F.");
                continue;
            }
        } else if (tipoPassagem == 'x' || tipoPassagem == 'X') {
            // Para passagens executivas, recomenda as poltronas A e F se não for escolhida
            if (poltrona == 'b' || poltrona == 'e') {
                printf("\nPassagem Executiva: Recomenda-se reservar as poltronas A ou F. ");
                char alterar;
                printf("Deseja alterar para A ou F? (s/n): ");
                scanf(" %c", &alterar);
                if (alterar == 's' || alterar == 'S') {
                    printf("\nDigite a nova poltrona [A][F]: ");
                    scanf(" %c", &poltrona);
                    poltrona = tolower(poltrona);
                    if (poltrona == 'a') assento = 0;
                    else if (poltrona == 'f') assento = 5;
                    else {
                        printf("\nPoltrona inválida. Tente novamente.");
                        continue;
                    }
                }
            }
        }

        verificarDisponibilidade(reserva, fileira, assento);

        // Exibe a matriz de reservas após a reserva
        printf("\n\t\t[A] [B] [C]\t[D] [E] [F]\n");
        for (int x = 0; x < 10; x++) {
            if (x != 9) printf("\n\t0%d\t", x + 1);
            else printf("\n\t%d\t", x + 1);
            
            for (int y = 0; y < 6; y++) {
                printf("[%c] ", reserva[x][y]);
                if (y == 2) {
                    printf("\t");
                }
            }
        }
        printf("\n");

        // Pergunta se o usuário deseja escolher mais um assento
        char continuar;
        printf("\nDeseja escolher mais um assento? (s/n): ");
        scanf(" %c", &continuar);
        
        if (continuar == 's' || continuar == 'S') {
            printf("\nEscolha o tipo de passagem (E - Econômica, X - Executiva): ");
            scanf(" %c", &tipoPassagem); // Pergunta novamente o tipo de passagem
            continue; // Retorna ao início do loop para escolher mais assentos
        } else {
            printf("\nObrigado por voar conosco!");
            break; // Sai do loop e encerra o programa
        }
    }
    return 0;
}