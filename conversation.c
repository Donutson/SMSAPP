#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "conversation.h"
#include "utils.c"

void connected(char identifiant[TAILLE_IDENTIFIANT])
{
    //cette fonction ne fait que générer l'écran d'affichage quand l'utilisateur est connecté
    int cas;
    do
    {
        system("cls");
        //affichage du menu
        printf("\n0- Ajouter un contact\n1- Voir contacts\n2- Ecrire message\n3- Lire messages\n4- d%cconnexion\n", 130);
        cas = getchar();
        if(cas!='\n')
            viderBuffer();
        switch(cas)
        {
        case '0':
            add(identifiant);
            break;
        case '1':
            see(identifiant);
            break;
        case '2':
            send(identifiant);
            break;
        case '3':
            look(identifiant);
            break;
        case '4':
            printf("D%cconnexion en cours..\n", 130);
            break;
        default:
            printf("R%cponse invalide\nArr%ct du programme...\n", 130,136);
            cas = '4';
            break;
        }
    }while(cas!='4');

}

void add(char identifiant[TAILLE_IDENTIFIANT])
{
    //cette fonction ajoute un nouveau contact
    //daans la liste de l'utilisateur connecté
    char id[TAILLE_IDENTIFIANT];
    system("cls");
    printf("Veuillez saisir l'identifiant du contact %c ajouter\n",133);
    scanf("%s", id);
    viderBuffer();//vidage du buffer
    //on verifie que la personne entrée à un compte
   if(checkid(id))
   {
       FILE* fichier = NULL;
       char chemin[TAILLE_CHEMIN_COMPTES] = "C:Sms app/Comptes/";
       strcat(chemin, identifiant);
       strcat(chemin,"/contacts.txt");
       fichier = fopen(chemin, "a");
       fputs(id, fichier);
       fputc('\n',fichier);
       fclose(fichier);
       printf("Le contact %c bien %ct%c ajout%c\n", 133, 136,136,136);
   }
   else
   {
       printf("Op%cration impossible, cette personne n'a pas de compte\n",130);
   }
    system("PAUSE");
}

void see(char identifiant[TAILLE_IDENTIFIANT])
{
    system("cls");
    //cette fonction permet de voir tous les contcts de l'utilisateur connecté
    FILE* fichier = NULL;
    char chemin[TAILLE_CHEMIN_COMPTES] = "C:Sms app/Comptes/";
    strcat(chemin, identifiant);
    strcat(chemin,"/contacts.txt");
    fichier = fopen(chemin, "r");
    if(fichier != NULL)
    {
        printf("Vos contacts\n");
        while(fgets(chemin,TAILLE_IDENTIFIANT,fichier) != NULL)
        {
            printf("%s",chemin);
        }
    }
    else
        printf("Dommage vous n'avez aucun contact, pensez %c en ajouter\n", 133);
    system("PAUSE");
}

void look(char identifiant[TAILLE_IDENTIFIANT])
{
    system("cls");
    //cette fonction permet d'afficher tous les messages de l'utilisateur connecté
    FILE* fichier = NULL;
    char chemin2[TAILLE_CHEMIN_DERNIER_MESSAGE] = "C:Sms app/Comptes/",chemin1[TAILLE_CHEMIN_COMPTES] = "C:Sms app/Comptes/",indice1[4]= "a";
    char message[TAILLE_MESSAGE], copie[TAILLE_CHEMIN_COMPTES] = "a";
    int indice = 0;
    strcat(chemin1, identifiant);
    strcat(chemin1, "/");
    strcpy(copie, chemin1);
    strcat(chemin2, identifiant);
    strcat(chemin2, "/derniermessage.txt");
    //récupération de l'indice du dernier message
    fichier = fopen(chemin2, "r");
    fscanf(fichier,"%d",&indice);
    fclose(fichier);

    //affichage des messages
    for(int i=0; i <= indice; i++)
    {
        //finnalisation du chemin du message i
        itoa(i, indice1, 10);
        strcat(copie, indice1);
        strcat(copie, ".txt");
        fichier = fopen(copie, "r");
        //affichage du message i
        while(fgets(message,TAILLE_MESSAGE,fichier) != NULL)
        {
            printf("%s",message);
        }
        printf("\n\n");
        fclose(fichier);
        strcpy(copie, chemin1);
    }
    system("PAUSE");
}

void send(char identifiant[TAILLE_IDENTIFIANT])
{
    system("cls");
    //cette fonction permet d'écrire un message
    //à un utilisateur ayant un compte
    char id[TAILLE_IDENTIFIANT], message[TAILLE_MESSAGE];
    printf("Veuillez saisir l'identifiant du contact %c qui envoyer le message\n",133);
    scanf("%s", id);
    viderBuffer();
    //on vérifie que l'utilisateur saisir possède bien un compte
    //avant de pouvoir lui écrire
    if(checkid(id))
    {
        FILE *fichier1 = NULL, *fichier2 = NULL;
        char chemin1[TAILLE_CHEMIN_COMPTES] = "C:Sms app/Comptes/";
        char chemin2[TAILLE_CHEMIN_DERNIER_MESSAGE] = "C:Sms app/Comptes/", indice1[4]= "a";
        int indice = 0;
        //création des chemins vers nos fichiers de stockage
        strcat(chemin1, id);
        strcat(chemin1, "/");
        strcat(chemin2, id);
        strcat(chemin2, "/derniermessage.txt");
        //récupération de l'indice du dernier message
        fichier1 = fopen(chemin2, "r");
        fscanf(fichier1,"%d",&indice);
        fclose(fichier1);
        //mise à jour de l'indice du dernier message
        fichier1 = fopen(chemin2, "w");
        fprintf(fichier1,"%d", indice + 1);
        fclose(fichier1);
        //finalisation du chemin du message
        itoa(indice + 1, indice1, 10);
        strcat(chemin1, indice1);
        strcat(chemin1, ".txt");
        //écriture du mrssage dans le fichier adéquate
        fichier2 = fopen(chemin1, "w");
        printf("Vous pouvez saisir votre message\n");
        takews(message, TAILLE_MESSAGE);
        fputs(identifiant,fichier2);
        fputs(":\n",fichier2);
        fputs(message,fichier2);
        fclose(fichier2);
        printf("Message envoy%c\n",130);

    }
    else
        printf("Vous ne pouvez envoyez de message %c cette personne, elle n'a pas de compte\n", 133);
    system("PAUSE");
}
