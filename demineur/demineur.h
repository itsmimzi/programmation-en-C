#ifndef INF1643PP2_H
#define INF1643PP2_H

/***************************************************************************************
 * Auteur	: Maryam Mouat.
 * Dernière modification : 12 avril 2023
 *
 * Description : Ce programme implémente le jeu démineur.
 ****************************************************************************************/

#define MAX_LINES 10            // Nombre maximum de lignes du plan de jeu
#define MAX_COL 15              // Nombre maximum de colonnes du plan de jeu
#define MIN 1                   // Nombre minimum de lignes ou de colonnes du plan de jeu
#define oper_valides "DdMm?Qq"  // Ensemble des caractères valides pour une opérayion sur un coup
#define verif_valides "OoNn"    // Ensemble des caractères valides pour quitter/continuer une partie
// Nombre minimum de mines, correspond à 10% des cases du plan de jeu.
#define MIN_MINES 0.1 * (lignes * colonnes)
// Nombre maximum de mines, correspond à 80% des cases du plan de jeu.
#define MAX_MINES 0.8 * (lignes * colonnes)
// ces fonctions sont utilisées pour déterminer les bornes des boucles de recherche des cases contigues:
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

//**************************************************************************************
// valider_char
//**************************************************************************************
// Cette fonction permet de valider qu'un caractère saisi au clavier fait partie d'un
// ensemble de caractères donnés, et retourne celui-ci. Autrement, la fonction
// redemande un caractère valide.
//**************************************************************************************
// Paramètres : message - message de sollicitation
//              valides - ensemble des caractères valides
//              error - message d'erreur affiché si caractère non valide
//**************************************************************************************

char valider_char(char *message, char *valides, char *error);

//**************************************************************************************
// valider_int
//**************************************************************************************
// Cette fonction permet de valider qu'un entier saisi au clavier est compris dans une
// intervalle donnée, et retourne celui-ci. Si l'entier n'est pas dans l'intervalle,
// elle affiche un message d'erreur et redemande une nouvelle saisie.
//**************************************************************************************
// Pré-condition : min <= max
//**************************************************************************************
// Paramètres : message - message de sollicitation
//              min - borne min de l'intervalle
//              max - borne max de l'intervalle
//**************************************************************************************

int valider_int(char *message, int min, int max);

//***************************************************************************************
// initialiser_pja
//***************************************************************************************
// Cette fonction permet d'initialiser le plan de jeu affiché, chaque case est initialisée
// avec le caractères 'x'.
//***************************************************************************************
// Paramètres : **pja - matrice de chars du plan de jeu affiché
//              nb_lines - nombre de lignes
//              nb_cols - nombre de colonnes
//***************************************************************************************

void initialiser_pja(char ***pja, int nb_lines, int nb_cols);

//***************************************************************************************
// initialiser_pj
//***************************************************************************************
// Cette fonction permet d’initialiser le plan de jeu. Les mines y sont insérées
// aléatoirement et sont représentées par le chiffre 99. La fonction insère dans chaque
// case non initialisée un chiffre qui représente le nombre de mines contiguës à cette
// case (minimum 0 et maximum 8).
//***************************************************************************************
// Paramètres : pj - matrice d'entiers du plan de jeu
//              nb_lines - nombre de lignes
//              nb_cols - nombre de colonnes
//              nb_mines - nombre de mines inséré
//***************************************************************************************

int ** initialiser_pj(int **pj, int nb_lines, int nb_cols, int nb_mines);

//***************************************************************************************
// afficher_jeu
//***************************************************************************************
// Cette fonction permet d’afficher le plan de jeu (plan de jeu affiché).
// Le nombre de mines à trouver est également affiché sous le plan de jeu.
//***************************************************************************************
// Paramètres : pja - plan de jeu affiché
//              nb_lines - nombre de lignes
//              nb_cols - nombre de colonnes
//              nb_mines - nombre de mines
//***************************************************************************************

void afficher_jeu(char **pja, int nb_lines, int nb_cols, int nb_mines);

//***************************************************************************************
// valider_coup
//***************************************************************************************
// Cette fonction permet de valider un coup du joueur.
//
// La fonction saisit au clavier et valide le numéro de ligne et de colonne de la case à
// jouer. Si les numéros sont valides, ils sont retournés. Sinon, ils sont saisis et
// validés à nouveau. Les numéros sont invalides s’ils représentent une case déjà jouée
// ou s’ils représentent une case à l’extérieure du plan de jeu.
//
// La fonction retourne le numéro de ligne et de colonne de la case à jouer.
//***************************************************************************************
// Paramètres : pja - plan de jeu affiché
//              nb_lines - nombre de lignes
//              nb_cols - nombre de colonnes
//***************************************************************************************

int *valider_coup (char **pja, int nb_lines, int nb_cols);

//***************************************************************************************
// jouer_coup
//***************************************************************************************
// Cette fonction permet de jouer un coup dans une case aux coords: line_case, col_case.
//
// La fonction verifie :
// Si la case contient une mine, alors un ‘M’ est inséré dans le plan de jeu affiché et
// le nombre de coups encore possibles devient 0.
// Si la case ne contient pas de mine, alors le chiffre se trouvant dans la case (0..8)
// est inséré dans le plan de jeu affiché.
// Si le chiffre découvert est 0, alors elle découvre toutes les 8 cases voisines.
//***************************************************************************************
// Paramètres : pj - plan de jeu
//              pja - plan de jeu affiché
//              nb_lines - nombre de lignes du plan de jeu
//              nb_cols - nombre de colonnes du plan de jeu
//              line_case - ligne de la case à jouer
//              col_case - colonne de la case à jouer
//***************************************************************************************

int jouer_coup(int **pj, char **pja, int nb_lines, int nb_cols, int line_case, int col_case);

//***************************************************************************************
// compter_coups
//***************************************************************************************
// Cette fonction permet de compter le nombre de coups qui restent à jouer.
//
// La fonction vérifie toutes les cases du plan de jeu affiché et renvoie le nombre de
// cases qui n’ont pas encore été dévoilées (les cases avec un « x » ou un « ? »).
// Si ce nombre est 0, la partie est terminée et on déclarera le joueur vainqueur.
// La fonction retourne le nombre de coups qui restent à jouer.
//***************************************************************************************
// Paramètres : pja - plan de jeu affiché
//              nb_lines - nombre de lignes du plan de jeu
//              nb_cols - nombre de colonnes du plan de jeu
//***************************************************************************************

int compter_coups(char **pja, int nb_lines, int nb_cols);

//***************************************************************************************
// etat_partie
//***************************************************************************************
// Cette fonction permet de déterminer l'état de la partie et affiche un message pour
// l'indiquer.
//
// La fonction vérifie :
// Si la case à jouer contient une mine, retourne -1.
// Si le nombre de coups possibles est 0, retourne 1.
// Sinon, la fonction retourne la valeur 0 pour indiquer que la partie continue.
//***************************************************************************************
// Paramètres : pj - plan de jeu
//              last_line - numéro de ligne du dernier coup joué
//              last_col - numéro de colonne du dernier coup joué
//              nb_coups - nombre coups encore possibles
//***************************************************************************************

int etat_partie(int **pj, int last_line, int last_col, int nb_coups);

//***************************************************************************************
// jouer_partie
//***************************************************************************************
// Cette fonction permet de jouer une partie de démineur.
//
// La fonction commence par initialiser le plan de jeu affiché et afficher le jeu de départ.
// La fonction valide le coup du joueur avant de demander l’opération à effectuer pour
// la case choisie.
// la fonction joue ensuite le coup et affiche le jeu à nouveau avec un message qui indique
// l’état de la partie. Elle recommence (valider, jouer, afficher) tant que la partie n’est
// pas terminée.
// Si l’utilisateur choisi de quitter, la fonction vérifie si toutes les cases restantes
// non- dévoilées sont des cases vides (valeurs 0). Si oui, la partie est gagnée.
//***************************************************************************************
// Paramètres : pj - plan de jeu
//              nb_lines - nombre de lignes du plan de jeu
//              nb_cols - nombre de colonnes du plan de jeu
//              nb_coups - nombre coups encore possibles
//***************************************************************************************

void jouer_partie(int **pj, int nb_lines, int nb_cols, int nb_coups);



#endif
