#define ESPERA   1
#define CADASTRO 2
#define ESCOLHER 3
#define REMOVER  4
#define DENOVO   5

#include <iostream>

using namespace std;
char senha[ ] = {'1', '2', '3', '4'};
char senhad[ ] = {'1', '2', '3', '5'};
char enter[101];
char enters[101][101];
char senhas[101][101];
int i;
int j;
int Estado = 1;
int erro;
int valid = 0;


void maquinaDeEstados(char enter[], char senhas[][5], char senhad[], int Estado) {
  int i;
  int j;
  int erro;
  int valid = 0;

  switch (Estado) {
    case ESPERA:
      switch (enter[i]) {
        case 'A':
          for (j = 0; j < 101; j++) {
            if ((enter[0] == senhas[1][0]) && (enter[1] == senha[1][1]) && (enter[2] == senha[1][2]) && (enter[3] == senha[1][3])) {
              valid = 1;
              break;
            }
          }

          if (valid) {
            printf("abre a porta!\n");
            break;
          } else if ((enter[0] == senhad[0]) && (enter[1] == senhad[1]) && (enter[2] == senhad[2]) && (enter[3] == senhad[3])) {
            Estado = CADASTRO;
            printf("digite a senha para cadastro:\n");
            break;
          } else {
            printf("senha incorreta\n");
            erro++;
            if (erro == 3) {
              erro = 0;
              printf("se fodeu\n");
              Estado = ESPERA;
            }
          }
        case 'B':

          for (j = 0; j < 101; j++) {
            if ((enter[0] == senhas[1][0]) && (enter[1] == senha[1][1]) && (enter[2] == senha[1][2]) && (enter[3] == senha[1][3])) {
              valid = 1;
              break;
            }
          }
          if (valid) {
            Estado = CADASTRO;
            printf("digite a senha para cadastro:\n");
            break;
          } else if ((enter[0] == senhad[0]) && (enter[1] == senhad[1]) && (enter[2] == senhad[2]) && (enter[3] == senhad[3])) {
            Estado = ESCOLHER;
            printf("Escolher senha\n");
            break;
          } else {
            printf("senha incorreta\n");
            erro++;
            if (erro == 3) {
              erro = 0;
              printf("se fodeu\n");
              Estado = ESPERA;
            }
          }
        case 'C':
          for (j = 0; j < 101; j++) {
            if ((enter[0] == senhas[1][0]) && (enter[1] == senha[1][1]) && (enter[2] == senha[1][2]) && (enter[3] == senha[1][3])) {
              valid = 1;
              break;
            }
          }
          if (valid) {
            Estado = REMOVER;
            printf("Remove senha\n");
            break;
          } else if ((enter[0] == senhad[0]) && (enter[1] == senhad[1]) && (enter[2] == senhad[2]) && (enter[3] == senhad[3])) {
            Estado = ESCOLHER;
            printf("Escolher senha\n");
            break;
          } else {
            printf("senha incorreta\n");
            erro++;
            if (erro == 3) {
              erro = 0;
              printf("se fodeu\n");
              Estado = ESPERA;
            }
          }
      }
  }
  printf("Estado = %d\n", Estado);
  return 0;
}
