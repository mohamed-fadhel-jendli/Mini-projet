#include <stdio.h>
#include <string.h>
#define MAX_ETUDIANTS 46
#define MAX_MATIERES 12

typedef struct
{
    int id;
    char nom[50];
    char prenom[50];
    char groupe[10];
} Etudiant;

typedef struct
{
    int id;
    char code[10];
    char nom[50];
} Matiere;

typedef struct
{
    float controleContinu;
    float travauxPratiques;
    float examenFinal;
    float moyenne;
} Notes;

Etudiant etudiants[MAX_ETUDIANTS];
Matiere matieres[MAX_MATIERES];
float coefficients[MAX_MATIERES];
Notes notes[MAX_ETUDIANTS][MAX_MATIERES];

float calculerMoyenneMatiere(float travauxPratiques,float controleContinu,float examenFinal)
{
    return (0.25*travauxPratiques)+(0.35*controleContinu)+(0.4*examenFinal);
}

float calculerMoyenneGenerale(int indiceEtudiant,int totalMatieres)
{
    float somme=0.0;
    float totalCoef=0.0;
    for(int j=0;j<totalMatieres;j++)
    {
        somme+=(notes[indiceEtudiant][j].moyenne*coefficients[j]);
        totalCoef+=coefficients[j];
    }
    return (totalCoef>0 ? (somme/totalCoef):0.0);

}

void saisirEtudiants(int totalEtudiants)
{
    for(int i=0;i<totalEtudiants;i++)
    {
        printf("Saisir les informations pour l'etudiant %d :\n",i+1);
        printf("ID : ");
        scanf("%d",&etudiants[i].id);
        printf("Nom : ");
        scanf("%s",etudiants[i].nom);
        printf("Prenom : ");
        scanf("%s",etudiants[i].prenom);
        printf("Groupe : ");
        scanf("%s",etudiants[i].groupe);
    }
}

void saisirMatieres(int totalMatieres)
{
    for(int i=0;i<totalMatieres;i++)
    {
        printf("Saisir les informations pour la matiere %d :\n",i+1);
        printf("Code : ");
        scanf("%s",matieres[i].code);
        printf("Nom : ");
        scanf("%s",matieres[i].nom);
    }
}

void saisirCoefficients(int totalMatieres)
{
    for(int i=0;i<totalMatieres;i++)
    {
        printf("Saisir le coefficient pour la matiere %d : ",i+1);
        scanf("%f",&coefficients[i]);
    }
}

void saisirNotes(int totalEtudiants,int totalMatieres)
{
    for(int i=0;i<totalEtudiants;i++)
    {
        printf("Saisie des notes pour l'etudiant %d (%s %s) :\n",etudiants[i].id,etudiants[i].nom,etudiants[i].prenom);
        for(int j=0;j<totalMatieres;j++)
        {
            printf("Matiere %s :\n",matieres[j].nom);
            printf("Controle Continu : ");
            scanf("%f",&notes[i][j].controleContinu);
            printf("Travaux Pratiques : ");
            scanf("%f",&notes[i][j].travauxPratiques);
            printf("Examen Final : ");
            scanf("%f",&notes[i][j].examenFinal);
            notes[i][j].moyenne=calculerMoyenneMatiere(notes[i][j].travauxPratiques,notes[i][j].controleContinu,notes[i][j].examenFinal);
        }
    }
}

void afficherResultats(int totalEtudiants,int totalMatieres)
{
    for(int i=0;i<totalEtudiants;i++)
    {
        float moyenneGenerale=calculerMoyenneGenerale(i,totalMatieres);
        char statut[10]="REFUSE";
        if(moyenneGenerale>=10)
        {
            strcpy(statut,"ADMIS");
        }
        printf("\nEtudiant %d :\n",etudiants[i].id);
        printf("Nom : %s %s Groupe : %s\n",etudiants[i].nom,etudiants[i].prenom,etudiants[i].groupe);
        printf("Moyenne Generale : %.2f Statut : %s\n",moyenneGenerale,statut);
        printf("Matieres sous la moyenne : ");
        for(int j=0;j<totalMatieres;j++)
        {
            if(notes[i][j].moyenne<8)
            {
                printf("%s ",matieres[j].code);
            }
        }
        printf("\n");
    }
}

int main()
{
    int totalEtudiants, totalMatieres;
    printf("Nombre d'etudiants : ");
    scanf("%d", &totalEtudiants);
    printf("Nombre de matieres : ");
    scanf("%d", &totalMatieres);
    saisirEtudiants(totalEtudiants);
    saisirMatieres(totalMatieres);
    saisirCoefficients(totalMatieres);
    saisirNotes(totalEtudiants, totalMatieres);
    afficherResultats(totalEtudiants, totalMatieres);
    return 0;
}
