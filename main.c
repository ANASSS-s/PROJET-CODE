#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
===========================================================
 STRUCTURE DRONE
===========================================================
*/
typedef struct
{
    int id;
    float x;
    float y;
    float z;

} Drone;

/*
===========================================================
 CALCUL DE DISTANCE EUCLIDIENNE AU CARRE
 (On évite sqrt pour optimiser les performances)
===========================================================
*/
float distanceCarree(Drone *a, Drone *b)
{
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    float dz = a->z - b->z;

    return (dx * dx) + (dy * dy) + (dz * dz);
}

/*
===========================================================
 FONCTION DE TRI SELON L'AXE X
 Utilisée par qsort()
===========================================================
*/
int comparerX(const void *a, const void *b)
{
    Drone *d1 = (Drone *)a;
    Drone *d2 = (Drone *)b;

    if (d1->x < d2->x)
    {
        return -1;
    }

    if (d1->x > d2->x)
    {
        return 1;
    }

    return 0;
}

/*
===========================================================
 PROGRAMME PRINCIPAL
===========================================================
*/
int main()
{
    int nombreDrones = 10000;

    /*
    =======================================================
     ALLOCATION DYNAMIQUE DE LA MEMOIRE
    =======================================================
    */
    Drone *essaim;

    essaim = (Drone *)malloc(nombreDrones * sizeof(Drone));

    if (essaim == NULL)
    {
        printf("Erreur : allocation mémoire impossible.\n");
        return 1;
    }

    /*
    =======================================================
     INITIALISATION ALEATOIRE DES DRONES
     INTERDICTION D'UTILISER []
    =======================================================
    */
    srand(time(NULL));

    int i = 0;

    while (i < nombreDrones)
    {
        (essaim + i)->id = i + 1;

        (essaim + i)->x = (float)(rand() % 1000);
        (essaim + i)->y = (float)(rand() % 1000);
        (essaim + i)->z = (float)(rand() % 1000);

        i++;
    }

    /*
    =======================================================
     TRI DES DRONES SELON X
    =======================================================
    */
    qsort(
        essaim,
        nombreDrones,
        sizeof(Drone),
        comparerX
    );

    /*
    =======================================================
     RECHERCHE DES DEUX DRONES LES PLUS PROCHES
    =======================================================
    */

    Drone *drone1Min = essaim;
    Drone *drone2Min = essaim + 1;

    float minDistance;

    minDistance = distanceCarree(
        drone1Min,
        drone2Min
    );

    Drone *p1;
    Drone *p2;

    int j;

    i = 0;

    while (i < nombreDrones)
    {
        j = i + 1;

        while (j < nombreDrones)
        {
            p1 = essaim + i;
            p2 = essaim + j;

            /*
            ===============================================
             OPTIMISATION :
             Si la distance sur X dépasse la distance
             minimale trouvée, on arrête immédiatement.
            ===============================================
            */
            float dx = p2->x - p1->x;

            if ((dx * dx) > minDistance)
            {
                break;
            }

            float distanceActuelle;

            distanceActuelle = distanceCarree(
                p1,
                p2
            );

            if (distanceActuelle < minDistance)
            {
                minDistance = distanceActuelle;

                drone1Min = p1;
                drone2Min = p2;
            }

            j++;
        }

        i++;
    }

    /*
    =======================================================
     AFFICHAGE DU RESULTAT
    =======================================================
    */
    printf("\n=====================================\n");
    printf(" DRONES LES PLUS PROCHES\n");
    printf("=====================================\n");

    printf(
        "Drone %d\n",
        drone1Min->id
    );

    printf(
        "Position : (%.2f , %.2f , %.2f)\n\n",
        drone1Min->x,
        drone1Min->y,
        drone1Min->z
    );

    printf(
        "Drone %d\n",
        drone2Min->id
    );

    printf(
        "Position : (%.2f , %.2f , %.2f)\n\n",
        drone2Min->x,
        drone2Min->y,
        drone2Min->z
    );

    printf(
        "Distance minimale au carré : %.4f\n",
        minDistance
    );

    /*
    =======================================================
     LIBERATION DE LA MEMOIRE
    =======================================================
    */
    free(essaim);

    return 0;
}
