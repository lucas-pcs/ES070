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



int main()
{

  senhas[0][0] = '1';
  senhas[0][1] = '2';
  senhas[0][2] = '3';
  senhas[0][3] = '4';

  senhas[1][0] = '1';
  senhas[1][1] = '2';
  senhas[1][2] = '3';
  senhas[1][3] = '5';

  /*    for(i=0;i<5;i++){
          printf("digita numero:");
          scanf("%c", senhad[i]);
      }*/

  for (i = 0; i < 4; i++) {
    std::cout << senha[i];
  }
  printf("\n");

  for (i = 0; i < 4; i++) {
    std::cout << senhad[i];
  }

  printf("\n");

  if (senha[0] == senhad[0]) {
    std::cout << senha[1] << "\n";
  } else {
    std::cout << senha[0] << "\n";
  }

  for (i = 0; i < 5; i++) {
    printf("digita numero:");
    std::cin >> enter[i];

    //senhas[0][i] = enter[i];
    //senhas[1][0] = {'2', '3', '4','5', '6'};
    std::cout << senhas[0][3] << "\n";

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
  }

  //std::cout << enter << "\n";


  /*
    if((enter[0] == senha[0]) && (enter[1] == senha[1]) && (enter[2] == senha[2]) && (enter[3] == senha[3]) && (enter[4] == senha[4])){
      printf("deitou o cabelo");
    }else{
      printf("senha incorreta");
    }*/

  return 0;
}
