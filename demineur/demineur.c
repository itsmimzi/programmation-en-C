#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "demineur.h"

int main(void)
{
    int lignes;
    int colonnes;
    int mines;
    int** jeu = NULL;


    // Saisir et valider nombre de lignes et de colonnes du plan
    lignes = valider_int("saisir nombre de lignes", MIN, MAX_LINES);
    colonnes = valider_int("saisir nombre de colonnes", MIN, MAX_COL);

    // Saisir et valider nombre de mines
    mines = valider_int("Saisir nombre de mines", MIN_MINES, MAX_MINES);

    // Initialiser plan de jeu et du plan affiché
    jeu = initialiser_pj(jeu, lignes, colonnes, mines);

    // Afficher le jeu initial
    printf("\nVOICI TON JEU DE DEMINEUR :\n");

    jouer_partie(jeu, lignes, colonnes, mines);


    // Libérer la mémoire allouée pour les tableaux
    for (int i = 0; i < lignes; i++)
    {
        free(jeu[i]);
    }
    free(jeu);

    return EXIT_SUCCESS;
}

char valider_char(char *message, char *valides, char *error)
{
    char saisi; // caractère à valider
    int est_valide = 0;
    size_t valides_taille = strlen(valides);
    do
    {
        // saisir le caractère au clavier
        printf("\n%s", message);
        scanf("\n%c", &saisi);

        // vérifier le caractère
        for (size_t i = 0; i < valides_taille; i++){
            if (saisi == valides[i]){
                est_valide = 1;
                break;
            }
        }
        if (!est_valide)
            printf("%s\n", error);

    } while (!est_valide);

    return saisi;
}

int valider_int(char *message, int min, int max)
{
    int saisi; // entier à valider
    do
    {
        // saisir l'entier au clavier
        printf("\n%s (entre %d et %d) : ", message, min, max);
        scanf("\n%d", &saisi);

        // vérifier que l'entier est dans l'intervalle
        if (saisi < min)
        {
            printf("\nErreur!! trop petite valeur");
            continue;
        }
        if (saisi > max)
        {
            printf("\nErreur!! trop grande valeur");
            continue;
        }
    } while (saisi < min || saisi > max);

    return saisi;
}

void initialiser_pja(char ***pja, int nb_lines, int nb_cols)
{
    int i, j;

    // Allouer mémoire pour pja
    *pja = (char**)malloc(nb_lines * sizeof(char*));

    // Initialiser chaque élément avec 'x'
    for (i = 0; i < nb_lines; i++)
    {
        (*pja)[i] = (char*)malloc(nb_cols * sizeof(char));
        for (j = 0; j < nb_cols; j++)
            (*pja)[i][j] = 'x';
    }
}

int **initialiser_pj(int **pj, int nb_lines, int nb_cols, int nb_mines)
{
    int k;              // compteur pour nombre de mines
    int i, j;           // compteurs pour lignes et colonnes du plan
    int x, y;           // compteurs pour ligne et colonne de case
    int rand_lines, rand_cols;

    pj= (int**)calloc(nb_lines, sizeof(int *));
    for (i = 0; i <nb_lines; i++)
        pj[i] = (int *)calloc(nb_cols, sizeof(int));

    // Ajout des mines aléatoirement
    srand(time(NULL));

    // initialisation du générateur de nombres aléatoires
    for (k = 0; k < nb_mines; k++)
    {
        do
        { // Vérification si la case contient déjà une mine, sinon cherche une autre case
            rand_lines = rand() % nb_lines;
            rand_cols = rand() % nb_cols;
        } while (pj[rand_lines][rand_cols] == 99);

        // Ajout de la mine
        pj[rand_lines][rand_cols] = 99;
    }

    // Ajout du nombre de mines adjacentes dans chaque case non initialisée
    for (i = 0; i < nb_lines; i++)
    {
        for (j = 0; j < nb_cols; j++)
        {
            if (pj[i][j] != 99)
            { // Si la case ne contient pas une mine
                int nb_mines_contigues = 0;

                // On parcourt les cases adjacentes pour compter le nombre de mines
                for (x = i-1; x <= i+1; x++)
                {
                    for (y = j-1; y <= j+1; y++)
                    {
                        // int lines_contigues = i + x;
                        // int cols_contigues = j + y;
                        if ((x >= 0 && x < nb_lines && y >= 0 && y < nb_cols) && !(x==i && y==j))
                        {
                            if (pj[x][y] == 99)
                                nb_mines_contigues++;
                        }
                    }
                }
                pj[i][j] = nb_mines_contigues; // On ajoute le nombre de mines contigues dans la case
            }
        }
    }
    return pj;
}

void afficher_jeu(char **pja, int nb_lines, int nb_cols, int nb_mines)
{
    int i, j;

    // Affichage de la première ligne du plan
    printf("\n  ");
    for (j = 0; j < nb_cols; j++)
    {
        printf(" %2d", j + 1);
    }

    // Affichage des tirets separant les lignes du plan
    for (j = 0; j < nb_cols; j++)
    {
        printf("---");
    }
    printf("-\n");

    // Affichage de chaque ligne du plan
    for (i = 0; i < nb_lines; i++)
    {
        // Affichage du numéro de la ligne
        printf("%2d |", i + 1);
        // Affichage des caractères de chaque colonne de la ligne
        for (j = 0; j < nb_cols; j++)
        {
            printf(" %c ", pja[i][j]);
        }
        // Affichage de la barre verticale à la fin de la ligne
        printf("|\n");
    }

    // Separation des lignes du plan
    printf("\n   ");
    for (j = 0; j < nb_cols; j++)
    {
        printf("---");
    }
    printf("-");

    // Affichage du nombres de mines
    printf("\nMines à trouver: %d", nb_mines);
}

int *valider_coup(char **pja, int nb_lines, int nb_cols)
{
    int line, col; // coordonnées de la case à jouer

    // allocation et verification de l'allocation mémoire des coordonnées
    int *coup = malloc(2 * sizeof(int));
    if (coup == NULL)
    {
        printf("Erreur : impossible d'allouer la mémoire pour les coordonnées du coup.\n");
        exit(EXIT_FAILURE);
    }

    do
    {
        // Saisi du numéro de ligne et de colonne
        line = valider_int("entrer un numero de ligne", MIN, nb_lines);
        col = valider_int("entrer un numero de colonne", MIN, nb_cols);

        // Vérification que le coup est valide
        if (line < MIN || line >= nb_lines || col < MIN || col >= nb_cols)
            printf("Coup invalide : la case est hors du plan de jeu.\n");
        else if (pja[line][col] != 'x')
            printf("Coup invalide : la case a déjà été jouée.\n");
    } while (line < MIN || line >= nb_lines || col < MIN || col >= nb_cols || pja[line][col] != 'x');

    coup[0] = line;
    coup[1] = col;

    return coup;
}

int jouer_coup(int **pj, char **pja, int nb_lines, int nb_cols, int line_case, int col_case)
{
    int i, j;
    int coup = 0; // nombre de coups possibles

    // Vérifier si la case contient une mine
    if (pj[line_case][col_case] == 99)
    {
        pja[line_case][col_case] = 'M';
        coup = 0;
    }

    else
    {
        int nb_mines_contigues = 0; // nombres de mines contigues à la case

        // Vérifier du nombre de mines dans les cases voisines
        for (i = max(0, line_case - 1); i < min(nb_lines, line_case + 2); i++)
        {
            for (j = max(0, col_case - 1); j < min(nb_cols, col_case + 2); j++)
            {
                if (pj[i][j] == 99)
                    nb_mines_contigues++;
            }
        }

        // Insérer nombre de mines dans la case du plan de jeu affiché
        if(nb_mines_contigues > 0)
            sprintf(&pja[line_case][col_case], "%c", '0' + nb_mines_contigues);

        // Si la case est vide, dévoiler récursivement cases voisines de la case(i,j)
        if (nb_mines_contigues == 0)
        {
            for (i = max(0, line_case - 1); i < min(nb_lines, line_case + 2); i++)
            {
                for (int j = max(0, col_case - 1); j < min(nb_cols, col_case + 2); j++)
                {
                    if (pja[i][j] == 'x')
                        jouer_coup(pj, pja, nb_lines, nb_cols, i, j);
                }
            }
        }
        coup = 1;
    }
    return coup;
}

int compter_coups(char **pja, int nb_lines, int nb_cols) {
    int i, j;
    int nb_coups = 0;

    for(i=0; i<nb_lines; i++) {
        for(j=0; j<nb_cols; j++) {
            if(pja[i][j] == 'x' || pja[i][j] == '?' ) {
                nb_coups++;
            }
        }
    }

    if (nb_coups == 0)
    {
        printf("partie terminée. Vous avez gagné !");
        return 0;
    }

    return nb_coups;
}

int etat_partie(int **pj, int last_line, int last_col, int nb_coups)
{
    int i, j;

    if(pj[last_line][last_col] == 99)
    {   // le dernier coup est sur une mine
        printf("BOOM! Vous venez de tomber sur une mine en (%d, %d), la partie est terminée !\n", last_line, last_col);
        return -1;
    } else if (nb_coups == 0){ // Plus aucun coup possible
        printf("BRAVO ! Il ne reste plus de coups, la partie est terminée !\n");
        return 1;
    } else { // La partie continue
        return 0;
    }
}

void jouer_partie(int **pj, int nb_lines, int nb_cols, int nb_mines)
{
    int *coup;
    int line, col, nb_coups;
    char operation;
    char **pja = NULL;

    // Initialiser le plan affiché et Afficher le jeu de départ
    initialiser_pja(&pja, nb_lines, nb_cols);
    afficher_jeu(pja, nb_lines, nb_cols, nb_mines);

    do {
        // Valider coup de l'utilisateur et Enregistrer coordonnées de la case
        coup = valider_coup(pja, nb_lines, nb_cols);
        line = coup[0];
        col = coup[1];
        free(coup);

        // Choisir l'opération à effectuer avec la case
        operation = valider_char("Choisissez l'opération à effectuer pour la case (D, M, ?, Q) : ", oper_valides, "erreur, renouvelez saisi.");

        switch(operation)
        {
            // L'opération 'D' ou 'd' vérifie si la case contient une mine
            case 'd':
            case 'D':
                if(pj[line][col] == 99)
                {   // si mine, la partie est perdue
                    pja[line][col] = 'M';
                    nb_coups = 0;
                    etat_partie(pj, line, col, nb_coups);
                    return;
                }
                jouer_coup( pj, pja, nb_lines, nb_cols, line, col); // sinon Mettre à jour le plan de jeu avec le nouveau coup
                afficher_jeu(pja, nb_lines, nb_cols, nb_mines); // Afficher le plan mis à jour

                // si toutes les cases sont dévoilées, la partie est gagnée
                nb_coups = compter_coups(pja, nb_lines, nb_cols);
                if(nb_coups == 0)
                {
                    printf("\nFélicitations! Vous avez gagné la partie.");
                    return;
                }
                break;
            // L'opération 'M' ou 'm' modifie la case en '*' pour indiquer une mine, donc impossible à jouer
            case 'm':
            case 'M':
                pja[line][col] = '*';
                afficher_jeu(pja, nb_lines, nb_cols, nb_mines); // Afficher le plan mis à jour
                break;
            // L'opération '?' modifie la case en '?' pour indiquer qu'elle est risquée, mais toujours possible à jouer
            case '?':
                pja[line][col] = '?';
                afficher_jeu(pja, nb_lines, nb_cols, nb_mines); // Afficher le plan mis à jour
                break;
            // L'opération 'Q' vérifie si toutes les cases restantes non-dévoilées sont des cases vides
            case 'q':
            case 'Q':
                if(compter_coups(pja, nb_lines, nb_cols) == 0)
                {
                    printf("\nFélicitations! Vous avez gagné la partie.");
                    return;
                } else {
                    char verifier = valider_char("Il reste des cases non-dévoilées. Voulez-vous vraiment quitter le programme? (O/N)", verif_valides, "erreur, renouvelez saisi");
                    if(verifier == 'O' || verifier == 'o')
                    {
                        return;
                    } else {
                        afficher_jeu(pja, nb_lines, nb_cols, nb_mines); // Afficher plan actuel
                    }
                }
                break;
            default:
                printf("\nOpération invalide. Veuillez réessayer.");
        }
    } while(operation != 'Q' && operation != 'q');
}
