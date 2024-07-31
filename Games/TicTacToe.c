#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

void _i(char b[], const int* s){
    for (int x = 0; x < *s; x++){
        for (int y = 0; y < *s; y++){
            b[x + (y * *s)] = ' ';
        }
    }
}
void _dB(char b[], const int* s, char* cD){
    char* c;
    system("clear");
    for (int x = 0; x < *s; x++){
        for (int y = 0; y < *s; y++){
            c = &b[x + (y * *s)];
            if (*&cD == c){
                printf("[\033[0;31m%c\033[0m]", *c);
            } else if ('X' == *c){
                printf("[\033[0;34m%c\033[0m]", *c);
            } else if ('O' == *c){
                printf("[\033[0;32m%c\033[0m]", *c);
            } else{
                printf("[%c]", *c);
            }
        }
        printf("\n");
    }
}
void _dO(char b[], const int* s){
    char* c;
    for (int x = 0; x < *s; x++){
        for (int y = 0; y < *s; y++){
            c = &b[x + (y * *s)];
            if ('X' == *c){
                printf("[\033[0;34m%c\033[0m]", *c);
            } else if ('O' == *c){
                printf("[\033[0;32m%c\033[0m]", *c);
            } else{
                printf("[%c]", *c);
            }
        }
        printf("\n");
    }
}
bool _cW(char b[], const int* s){
    for (int i = 0; i < *s; i++){
        if (b[i + 0 * *s] == b[i + 1 * *s] && b[i + 1 * *s] == b[i + 2 * *s] && b[i + 2 * *s] != ' ') return true;
        if (b[0 + i * *s] == b[1 + i * *s] && b[1 + i * *s] == b[2 + i * *s] && b[2 + i * *s] != ' ') return true;
    }
    if (b[0 + 0 * *s] == b[1 + 1 * *s] && b[1 + 1 * *s] == b[2 + 2 * *s] && b[2 + 2 * *s] != ' ') return true;
    if (b[2 + 0 * *s] == b[1 + 1 * *s] && b[1 + 1 * *s] == b[0 + 2 * *s] && b[0 + 2 * *s] != ' ') return true;

    return false;
}


int main(){

    const int s = 3;
    int p1 = 0;
    int p2 = -7;
    int r, c;

    const char c1 = 'X';
    const char c2 = 'O';

    char* pA[2 * s + 1];
    char b[s * s];
    char cP = c1;
    bool o = false;

    _i(b, &s);
    _dB(b, &s, NULL);

    printf("\033]0;Tic-Tac-Toe v2.1\007");
    while (!o){

        (c1 == cP) ? printf("Player \033[0;34m%c\033[0m turn\n", cP) : printf("Player \033[0;32m%c\033[0m turn\n", cP);

        printf("Please enter raw: ");
        if (scanf("%d", &r) != 1){
            printf("\033[1;31mError: You can use only numbers\033[0m\n");
            exit(1);
        } else if (r > s || r < 1){
            printf("Incorrect argument, please try again\n");
            continue;
        }

        printf("Please enter column: ");
        if (scanf("%d", &c) != 1){
            printf("\033[1;31mError: You can use only numbers\033[0m\n");
            exit(1);
        } else if (c > s || c < 1){
            printf("Incorrect argument, please try again\n");
            continue;
        }

        c--;
        r--;


        if (b[r + c * s] != ' '){
            printf("\nBox with coordinates (%d,%d) is already occupied\nPlease try again\n\n", ++r, ++c);
            continue;
        }

        b[r + c * s] = cP;
        pA[p1] = &b[r + c * s];
        p1++;
        p2++;

        if (7 == p1) p1 = 0;
        if (7 == p2) p2 = 0;


        if (p2 >= 0){
            *pA[p2] = ' ';
            if (p2 == 7){
                _dB(b, &s, pA[0]);
            } else{
                _dB(b, &s, pA[p2 + 1]);
            }
        } else if (p2 == -1){
            _dB(b, &s, pA[0]);
        } else{
            _dB(b, &s, NULL);
        }

        o = _cW(b, &s);

        cP = (c1 == cP) ? c2 : c1;

    }

    system("clear");
    printf("---------------------\nPlayer % c won the game\n-------------------- - \n", (cP == 'X') ? 'O' : 'X');
    _dO(b, &s);
    printf("\n");


    return 0;

}