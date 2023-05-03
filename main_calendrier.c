#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <time.h>

int pieces[10][4][4] = {
        {{'O', 'X', 'O', 'O'},
                {'O', 'X', 'O', 'O'},
                {'O', 'X', 'O', 'O'},
                {'X', 'X', 'O', 'O'}},
        {{'O', 'X', 'O', 'O'},
                {'O', 'X', 'O', 'O'},
                {'X', 'X', 'X', 'O'},
                {'O', 'O', 'O', 'O'}},
        {{'X', 'X', 'X', 'O'},
                {'X', 'O', 'O', 'O'},
                {'X', 'O', 'O', 'O'},
                {'O', 'O', 'O', 'O'}},
        {{'X', 'X', 'O', 'O'},
                {'O', 'X', 'O', 'O'},
                {'O', 'X', 'X', 'O'},
                {'O', 'O', 'O', 'O'}},
        {{'O', 'X', 'O', 'O'},
                {'O', 'X', 'O', 'O'},
                {'X', 'X', 'O', 'O'},
                {'X', 'O', 'O', 'O'}},
        {{'X', 'O', 'X', 'O'},
                {'X', 'X', 'X', 'O'},
                {'O', 'O', 'O', 'O'},
                {'O', 'O', 'O', 'O'}},
        {{'X', 'O', 'O', 'O'},
                {'X', 'X', 'O', 'O'},
                {'X', 'X', 'O', 'O'},
                {'O', 'O', 'O', 'O'}},
        {{'O', 'X', 'O', 'O'},
                {'O', 'X', 'O', 'O'},
                {'X', 'X', 'O', 'O'},
                {'O', 'O', 'O', 'O'}},
        {{'X', 'O', 'O', 'O'},
                {'X', 'X', 'O', 'O'},
                {'O', 'X', 'O', 'O'},
                {'O', 'O', 'O', 'O'}},
        {{'O', 'O', 'O', 'O'},
                {'O', 'O', 'O', 'O'},
                {'O', 'O', 'O', 'O'},
                {'X', 'X', 'X', 'X'}}};

int board[8][7] = {
        'O', 'O', 'O', 'O', 'O', 'O', 'X',
        'O', 'O', 'O', 'O', 'O', 'O', 'X',
        'O', 'O', 'O', 'O', 'O', 'O', 'O',
        'O', 'O', 'O', 'O', 'O', 'O', 'O',
        'O', 'O', 'O', 'O', 'O', 'O', 'O',
        'O', 'O', 'O', 'O', 'O', 'O', 'O',
        'O', 'O', 'O', 'O', 'O', 'O', 'O',
        'X', 'X', 'X', 'X', 'O', 'O', 'O'
};
static const int board_default[8][7] = {
        'O', 'O', 'O', 'O', 'O', 'O', 'X',
        'O', 'O', 'O', 'O', 'O', 'O', 'X',
        'O', 'O', 'O', 'O', 'O', 'O', 'O',
        'O', 'O', 'O', 'O', 'O', 'O', 'O',
        'O', 'O', 'O', 'O', 'O', 'O', 'O',
        'O', 'O', 'O', 'O', 'O', 'O', 'O',
        'O', 'O', 'O', 'O', 'O', 'O', 'O',
        'X', 'X', 'X', 'X', 'O', 'O', 'O'
};

char mois_autorises[12][5] = {"Jan", "Fev", "Mars", "Avr", "Mai", "Juin", "Juil", "Aout", "Sep", "Oct", "Nov",
                              "Dec"};

char jours_autorises[7][4] = {"Dim", "Lun", "Mdi", "Mer", "Jeu", "Ven", "Sam"};

bool pieces_placed[10];
int solutionCount = 0;

void entrer_mois(char mois[]) {

    int saisie_valide = 0;
    while (!saisie_valide) {
        printf("Veuillez entrer le mois {\"Jan\", \"Fev\", \"Mars\", \"Avr\", \"Mai\", \"Juin\", \"Juil\", \"Aout\", \"Sep\", \"Oct\", \"Nov\",\n"
               "                              \"Dec\"} : ");
        scanf("%s", mois);
        for (int i = 0; i < 12; i++) {
            if (strcmp(mois, mois_autorises[i]) == 0) {
                saisie_valide = 1;
                break;
            }
        }
        if (!saisie_valide) {
            printf("Saisie invalide. Veuillez réessayer.\n");
        }
    }
}

void entrer_jour(char jour[]) {
    int saisie_valide = 0;
    while (!saisie_valide) {
        printf("Veuillez entrer le jour {\"Dim\", \"Lun\", \"Mdi\", \"Mer\", \"Jeu\", \"Ven\", \"Sam\"} : ");
        scanf("%s", jour);
        for (int i = 0; i < 7; i++) {
            if (strcmp(jour, jours_autorises[i]) == 0) {
                saisie_valide = 1;
                break;
            }
        }
        if (!saisie_valide) {
            printf("Saisie invalide. Veuillez réessayer.\n");
        }
    }
}

int entrer_date() {
    int date;
    while (1) {
        printf("Veuillez entrer la date (1-31): ");
        if (scanf("%d", &date) != 1) {
            while (getchar() != '\n');
            printf("Saisie invalide. Veuillez réessayer.\n");
            continue;
        }
        if (date < 1 || date > 31) {
            printf("Saisie invalide. Veuillez réessayer.\n");
            continue;
        }
        break;
    }
    return date;
}

void tourner_piece(int id) {
    char temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = pieces[id][i][j];

        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            pieces[id][i][j] = temp[j][3 - i];
        }
    }
}

void mirror_piece(int id) {
    int temp;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 / 2; j++) {
            temp = pieces[id][i][j];
            pieces[id][i][j] = pieces[id][i][4 - 1 - j];
            pieces[id][i][4 - 1 - j] = temp;
        }
    }
}


bool canPlacePiece(int id, int x, int y) {
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            if (pieces[id][a][b] == 'X') {
                int c = x + a, d = y + b;
                if (c < 0 || c >= 8 || d < 0 || d >= 7 || board[c][d] == 'X') {
                    return false;
                }
            }
        }
    }
    return true;
}

void placePiece(int id, int x, int y) {
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            if (pieces[id][a][b] == 'X') {
                int c = x + a, d = y + b;
                board[c][d] = 'X';
            }
        }
    }
    pieces_placed[id] = true;
}

void removePiece(int id, int x, int y) {
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            if (pieces[id][a][b] == 'X') {
                int c = x + a, d = y + b;
                board[c][d] = 'O';
            }
        }
    }
    pieces_placed[id] = false;
}

void findSolutions(int id, int *numSolutions,clock_t debut) {
    if (id == 10) {
        (*numSolutions)++;
        return;
    }
    if (*numSolutions!=0)
        return;

    for (int a = 0; a < 8; a++) {
        for (int b = 0; b < 7; b++) {
            for (int c = 0; c < 4; c++) {
                for (int d = 0; d < 2; d++) {
                    if (canPlacePiece(id, a, b)) {
                        placePiece(id, a, b);
                        findSolutions(id + 1, numSolutions,clock());
                        removePiece(id, a, b);
                    }
                    mirror_piece(id);
                }
                tourner_piece(id);
            }
            if ((((double) ( clock() - debut)) / CLOCKS_PER_SEC) > 30)
                break;
        }
        if ((((double) ( clock() - debut)) / CLOCKS_PER_SEC) > 30)
            break;
    }
}

int main() {

    const char *tableau[8][7] = {
            {"Jan",  "Fev",  "Mars", "Avr", "Mai", "Juin", "NA"},
            {"Juil", "Aout", "Sep", "Oct", "Nov", "Dec",  "NA"},
            {"1",    "2",    "3",   "4",   "5",   "6",    "7"},
            {"8",    "9",    "10",  "11",  "12",  "13",   "14"},
            {"15",   "16",   "17",  "18",  "19",  "20",   "21"},
            {"22",   "23",   "24",  "25",  "26",  "27",   "28"},
            {"29",   "30",   "31",  "Dim", "Lun", "Mdi",  "Mer"},
            {"NA",   "NA",   "NA",  "NA",  "Jeu", "Ven",  "Sam"}
    };

    char mois[5], jour[4];
    int date;
//    entrer_mois(mois);
//    date = entrer_date();
//    entrer_jour(jour);
    for (int k = 2; k <31; k++) {
        for (int l = 0; l <7; l++) {
            for (int m = 0; m <12; m++) {
                date = k ;
                strcpy(mois, mois_autorises[m]);
                strcpy(jour, jours_autorises[l]);
                printf("votre choix est: %s %d %s\n", mois, date, jour);

                // Initialiser la grille
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 7; j++) {
                        if (strcmp(tableau[i][j], mois) == 0 || strcmp(tableau[i][j], jour) == 0 || atoi(tableau[i][j]) == date) {
                            board[i][j] = 'X';
                        }
                        printf("%c ", board[i][j]);
                    }
                    printf("\n");
                }

                printf("Calcul en cours ...\n");
                clock_t debut, fin;
                double temps_cpu;
                debut = clock();
                // Résoudre le puzzle
                findSolutions(0, &solutionCount,debut);
                printf("Il y a %d solutions en tout.\n", solutionCount);

                fin = clock();
                temps_cpu = ((double) (fin - debut)) / CLOCKS_PER_SEC;

                printf("Temps CPU = %lf s\n", temps_cpu);
                memcpy(&board, &board_default, sizeof board);
                solutionCount = 0;
            }
        }
    }


    return 0;
}

