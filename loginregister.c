#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "loginregister.h"
#include "conversation.h"
#include "utils.h"


void Creer_Compte()
{
    //Fonction Creer_Compte
	char user_password[TAILLE_MDP]="a",user_name[TAILLE_IDENTIFIANT], dossier[TAILLE_CHEMIN_COMPTES]="C:Sms app/Comptes/";

	identifiant(user_name,user_password, 1);

	/*Création d'un fichier qui va récupérer le "user_name" et le "user_password" de l'utilisateur*/
	/*Le fichier est ouvert en mode "a"(écriture + ajout à la suite du contenu du fichier)*/
	/*pour pouvoir afficher les infos des utilisateurs les uns à la suite des autres dans notre fichier*/
	FILE* fichier=NULL;
	fichier=fopen(REPERTOIRE,"a");
	if (fichier!=NULL){
		fprintf(fichier,"%s %s\n",user_name,user_password);
		fclose(fichier);
        createdir("C:Sms app/Comptes");
        strcat(dossier,user_name);
		createdir(dossier);
		//envoi du message de bienvenue
		messagebienvenue(user_name);
		printf("\n\n<<<<<<Votre compte a ete cree avec succes!>>>>>>\n");
		system("PAUSE");
	};
};
//Fonction Connexion

void Connexion()
{
	char user_password[TAILLE_MDP]="a",user_name[TAILLE_IDENTIFIANT],nom[TAILLE_IDENTIFIANT]="a",mdp[TAILLE_MDP]="a";
	int fin = 0, trouve = 0;
	identifiant(user_name,user_password, 2);/*appel de la fonction identifiant sur user_name et user_password*/
	/*On ouvre notre fichier en mode lecture uniquement("r") pour lire les infos qu'il contient*/
	FILE* fichier=NULL;
	fichier=fopen(REPERTOIRE,"r");

	do
    {
        fin = fscanf(fichier,"%s %s",nom, mdp) == -1;
        if(!fin)
            trouve = (strcmp(user_name, nom) == 0) && (strcmp(user_password, mdp) == 0);
    }while(!trouve && !fin);
    if(trouve)
    {
        printf("\n<<<<<<CONNEXION REUSSIE>>>>>>");
        connected(user_name);
    }
    else
        printf("\n\nDesole! Vous n\'etes pas enregistre!\n");
    system("PAUSE");
	fclose(fichier);

}
//Fonction Accueil:Affiche le menu principal et appel les fonctions Creer_Compte et Connexion
//en foonction du choix de l'utilisateur
void Accueil()
{
	char r = '0';
    createdir("C:SMS app");//création du dossier de stockage si non existant
	while(r!='3')
    {
		system("cls");
		printf("\n\t\t#----------BIENVENUE DANS SMS_APP----------#\n");
		printf("\n1-Creer un compte\n\n2-Connexion\n\n3-Quitter\n");
		printf("---------------------------------------------------\n\nChoisir 1, 2 ou 3: ");
		r = getchar();
		if(r != '\n')
            viderBuffer();
		switch(r)
		{
        case '1':
            system("cls");
			printf("\t\t*******************CREATION DE COMPTE*******************\n");
			Creer_Compte();
			break;
        case '2':
            system("cls");
			printf("\nEntrez vos identifiants\n");
			Connexion();
			break;
        case '3':
            system("cls");
            printf("Arret du programme\n");
            break;
        default:
            printf("\nChoix non valide==>Veuillez choisir 1, 2 ou 3\n\nTAPEZ ENTREE POUR REESSAYER");
		}
	}
}
