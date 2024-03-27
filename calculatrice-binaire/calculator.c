#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**************************************************************************************************************
 * @author      Maryam Mouat.
 * @version     2.0 2023-03-11
 *
 * Une calculatrice binaire :
 * ce programme effectue les opérations de bases (+, -, *, /) avec des nombres pseudo-binaires positifs.
 * ************************************************************************************************************/

// bornes pour valider les nombres PB
#define borne_min 0000000000
#define borne_max 1111111111

//*************************************************************************************************************
// Demande_BIN
//*****************************************************************************
// Cette fonction demande à l'utilisateur de saisir un nombre
//*****************************************************************************

long Demande_BIN();

// ****************************************************************************
// Est_Pb_Valide
//*****************************************************************************
// Cette fonction permet de valider qu'un nombre PB contient seulement les
// chiffres 0 ou 1. Si le nombre est valide, la fonction retourne 1.
// Si le nombre est invalide, la fonction retourne 0.
//*****************************************************************************
// Pré-condition : nombrePB >= 0
//*****************************************************************************
// Paramètre : nombrePB - un nombre à valider.
// ****************************************************************************

int Est_Pb_Valide(long nombrePB);

// ****************************************************************************
// NombrePB_Valide
//*****************************************************************************
// Cette fonction permet de saisir un nombre PB. Elle retourne le nombre PB
// valide compris dans l'intervalle min et max.
//*****************************************************************************
// Pré-condition : min <= max
//*****************************************************************************
// Paramètres : min - nombre PB minimum permis
//              max - nombre PB maximum permis.
// ****************************************************************************

long NombrePB_Valide(long min, long max);

// ****************************************************************************
// Demande_OP
//*****************************************************************************
//  Cette fonction demande à l'utilisateur un choix d'operation
//*****************************************************************************

char Demande_OP();

// ****************************************************************************
// NOMBRE_CONVERTI
//*****************************************************************************
// Cette fonction reçoit un nombre en paramètre et retourne ce
// nombre converti de la base source à la base destination.
//*****************************************************************************
// Pré-condition : nombre >= 0
//*****************************************************************************
// Paramètres : nombre - nombre à convertir
//              baseSrc - base source
//              baseDst - base destination
// ****************************************************************************

long Nombre_Converti(long nombre, int baseSrc, int baseDst);

long Demande_BIN()
{
    long saisi;
    printf("Donnez moi un nombre binaire : ");
    scanf("%ld", &saisi);
    return saisi;
}
int Est_Pb_Valide(long nombrePB)
{
    int reserve;
    // Tant qu'un chiffre est different de 0.
    while (nombrePB > 0)
    {
        // Extraire et verifier le chiffre
        reserve = nombrePB % 10;
        if (reserve != 0 && reserve != 1)
        {
            return 0;
        }
        // Passer au chiffre suivant
        nombrePB = nombrePB / 10;
    }
    return 1;
}
long NombrePB_Valide(long min, long max)
{
    long nbAvalide; // Nombre PB a valider

    // Saisir un nombre PB
    nbAvalide = Demande_BIN();
    int valide = 0;

    while (!valide)
    {
        // Verifier le nombre PB
        while (!Est_Pb_Valide(nbAvalide))
        {
            printf("\n** Ceci n’est pas une valeur binaire ** \n");
            nbAvalide = Demande_BIN();
        }
        if (Nombre_Converti(nbAvalide, 2, 10) >= Nombre_Converti(min, 2, 10) && Nombre_Converti(nbAvalide, 2, 10) <= Nombre_Converti(max, 2, 10))
            valide = 1;
        else
        {
            printf("\n** On déborde sur cette opération ** \n");
            nbAvalide = Demande_BIN();
        }
    }
    return nbAvalide;
}
char Demande_OP()
{
    char op; // Operation a valider
    do
    {
        // Saisir l'operation au clavier
        printf("Opération ? (+, -, *, /, n, q) >");
        scanf(" %c", &op);
    }
    // Verifier l'operation
    while (!(op == '+' || op == '-' || op == '*' || op == '/' || op == 'n' || op == 'N' || op == 'q' || op == 'Q'));
    return op;
    // while (!(op == '+' || op == '-' || op == '*' || op == '/' || op == 'n' || op == 'N' || op == 'q' || op == 'Q')){
    //     printf("opération invalide, nouvelle selection :\n");
    //     printf("Opération ? (+, -, *, /, n, q) >");
    //     scanf(" %c", &op);
    // }
}
long Nombre_Converti(long nombre, int baseSrc, int baseDst)
{
    long convert = 0;
    int pos = 0;

    if (!(nombre >= 0))
        return 0;

    switch (baseSrc)
    {
    case 2:
        if (baseDst == 10)
        {
            while (nombre > 0)
            {
                if (nombre % 10)
                    convert += pow(2, pos);
                nombre /= 10;
                pos++;
            }
        }
        break;

    case 10:
        pos++;
        if (baseDst == 2)
        {
            while (nombre > 0)
            {
                if (nombre % 2)
                    convert += pos;
                nombre /= 2;
                pos *= 10;
            }
        }
        break;

    default:
        break;
    }
    return convert;
}

int main(void)
{
    char oper = 'c'; // operation a executer
    long Nbin = 0;   // premier nombre PB
    long Nbin2 = 0;  // deuxieme nombre PB

    // Valider le premier nombre PB
    Nbin = NombrePB_Valide(borne_min, borne_max);

    while (oper != 'q' && oper != 'Q')
    {
        long temp = -1; // resultat de l'operation

        oper = Demande_OP(); // Valider l'operation à executer

        switch (oper)
        {
        case 'q':
            break;

        case 'Q':
            break;

        case 'n':
            Nbin = NombrePB_Valide(borne_min, borne_max);
            break;

        case 'N':
            Nbin = NombrePB_Valide(borne_min, borne_max);
            break;

        case '/':
            Nbin2 = 10;
            temp = Nombre_Converti(Nbin, 2, 10) / Nombre_Converti(Nbin2, 2, 10);
            break;

        case '*':
            Nbin2 = 10;
            temp = Nombre_Converti(Nbin, 2, 10) * Nombre_Converti(Nbin2, 2, 10);
            if (temp > Nombre_Converti(borne_max, 2, 10))
            {
                printf("** On déborde sur cette opération ** \n");
                temp = -1;
            }
            break;

        case '+':
            Nbin2 = NombrePB_Valide(borne_min, borne_max);
            temp = Nombre_Converti(Nbin, 2, 10) + Nombre_Converti(Nbin2, 2, 10);
            if (temp < 0 || temp > Nombre_Converti(borne_max, 2, 10))
            {
                printf("** On déborde sur cette opération ** \n");
                temp = -1;
            }
            break;

        case '-':
            Nbin2 = NombrePB_Valide(borne_min, borne_max);
            if (Nombre_Converti(Nbin2, 2, 10) > Nombre_Converti(Nbin, 2, 10))
            {
                printf(" ** Deuxième valeur binaire trop élevée ** \n");
                temp = -1;
            }
            else
            {
                temp = Nombre_Converti(Nbin, 2, 10) - Nombre_Converti(Nbin2, 2, 10);
            }
            break;

        default:
            printf("Réponse par defaut. Fin de programme.\n");
            break;
        }
        if (temp == -1)
        {
            // Afficher la derniere valeur du premier nombre PB
            printf("derniere valeur de Nbin : %ld \n", Nbin);
        }
        else
        {
            // Afficher l'expression
            printf("%ld (%ld) %c %ld (%ld) = %ld (%ld) \n", Nbin, Nombre_Converti(Nbin, 2, 10), oper, Nbin2, Nombre_Converti(Nbin2, 2, 10), Nombre_Converti(temp, 10, 2), temp);
            Nbin = Nombre_Converti(temp, 10, 2);
        }
    }

    return EXIT_SUCCESS;
}
