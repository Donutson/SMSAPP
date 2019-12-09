#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dir.h>
#include <dirent.h>
#include "utils.h"


int checkid(char id[TAILLE_IDENTIFIANT])
{
    //cette fonction vérifie qu'une identifiant se trou:ve parmi les comptes inscrits
    char identifiant[TAILLE_IDENTIFIANT]={'a'};
    int pasfinir, different = 0;
    FILE* fichier = NULL;
    fichier = fopen("C:SMS app/infos.txt", "r");
    do
    {
        pasfinir = getid(fichier, identifiant) != 0;
        different = strcmp(identifiant, id) != 0;
    }while(different && pasfinir);
    fclose(fichier);
    return strcmp(identifiant, id) == 0;
}

int getid(FILE* fichier, char id[TAILLE_IDENTIFIANT])
{
    //cette fonction permet d'obtenir l'identifiant sur la ligne courante
    //il faut néanmoins s'assurer d'être en début de ligne
    //cette fonction retourne 0 quand elle atteint la fin du fichier
    char lettre;
    int i = 0;
    do
    {
        lettre = fgetc(fichier);
        //printf("%c",lettre);
        if(lettre != ' ' && lettre != EOF)
            id[i] = lettre;
        i++;
    }while(lettre != ' ' && lettre != EOF);
    id[i - 1] = '\0';
    i = 1;
    while(lettre != '\n' && lettre != EOF)
        //on va à la ligne suivantz
        //si nous e= sàmmes pas à  la dernière ligne
    {
        lettre = fgetc(fichier);
    }
    if(lettre == EOF)
            i = 0;
    return i;
}

int takews(char *chaine, int longueur)
{
    //cette fonction lit l'entrée standard en prenant en compte les espaces
    char *positionEntree = NULL;
    if (fgets(chaine, longueur, stdin) != NULL)//si la lecture a reussir
    {
        positionEntree = strchr(chaine, '\n');//on recherche la touche '\n'
        if (positionEntree != NULL)//si trouvee
        {
            *positionEntree = '\0';//on la remplce par une fin de ligne
        }
        else
        {
            viderBuffer();//sinon on vide le buffer
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}

void viderBuffer()
{
    //cette fonction permet de vider le buffer
    int c = 0;
    while (c != '\n' && c != EOF)
    {
            c = getchar();
    }
}

void createdir(char* chemin)
{
    //cette fonction permet de créer un dossier si celui-ci n'existe pas
    //elle a juste besoin du chemin de ce dossier
    //elle a besoin de dirent.h et dir.h pour fonctionner
    DIR* dir;
    dir = opendir(chemin);//on éssaye d'ouvrir le dossier
    if(dir == NULL)//si l'ouverture échoue
    {
        mkdir(chemin);//on crée le dossier
    }
    closedir(dir);
}


void identifiant(char nom[TAILLE_IDENTIFIANT],char mdp[TAILLE_MDP], int etat)
{
    //Cette fonction n'est pas nécessaire,c'est juste pour éviter de repéter le même code
    //dans nos fonctions principales

    //le paramètre etat permet de gérer différemment une connnexion d'un enregistrement
    //etat vaut 1 pour un enregistrement et 2 pour une connexion
	int i=0;
	char ch;
	/*Saisie du nom d'utilisateur*/
	printf("Nom d'utilisateur: ");
	takews(nom,TAILLE_IDENTIFIANT);
	if(etat == 1 && checkid(nom))
    {
        printf("Vous possedez deja un compte, allez vous connectez...\n");
        return;
    }

	/*fgets prend en compte le caractère de saut de ligne "\n" lorsqu'on frappe sur "entrée"*/
	/*on va donc remplacer ce saut de ligne par un caractère de fin de chaine "\0"*/
	/*si on ne le fait pas,on aura un saut de ligne avant l'impression du mot de passe*/
	while(i<TAILLE_IDENTIFIANT ){
		if (nom[i]=='\n') {
			nom[i]='\0';
			break;}
		i++;
	};
	i = 0;//réinitialisation
	/*Saisie sécurisée du mot de passe*/
	printf("\nMot de passe:");
	/* Ici getch est utilisé pour la saisie sécurisée du mot de passe(il n'affiche pas ce qu'on écrit)*/
	/*A la place des caractères invisibles,on affiche des "*" en nous assurant que */
	/*chaque caractère saisi est bien placé dans un endroit(une variable),dans notre cas*/
	/*l'endroit c'est user_password que l'on forme caractère par caractère*/
	/*<getch!='\r'> est nécessaire pour que la boucle s'arrête dès qu'on frappe sur "entrée"*/
	/*pour rappel,"\r"(retour chariot) <==>"\n"(saut de ligne) sur la plupart des OS mais sur windows,*/
	/*les deux ne signifient pas vraiment la même chose*/
	while((ch=getch())!='\r' && i<=TAILLE_MDP - 2)
	{
	    mdp[i]=ch;
	    ch='*';
	    printf("%c",ch);
	    i++;
	};

}

void messagebienvenue(char id[TAILLE_IDENTIFIANT])
{
    //cette fonction se charge d'éditer et d'envoyer le message de bienvenue
    //elle crée par la même occasion un fichier contenat le numméro du dernier message
    char welcome[TAILLE_CHEMIN_COMPTES]= "C:Sms app/Comptes/", index[TAILLE_CHEMIN_COMPTES]="C:Sms app/Comptes/";
    FILE* fichier = NULL;
    //édition des différents chémins
    strcat(welcome,id);
    strcat(welcome,"/0.txt");
    strcat(index,id);
    strcat(index,"/derniermessage.txt");
    //on s'assure que la chose n'a pas déjà été fait,e
    fichier = fopen(index, "r");
    if(fichier == NULL)
    {
        fclose(fichier);
        //création et remplissage de derniermessage.txt
        fichier = fopen(index, "w");
        fprintf(fichier, "%d",0);
        fclose(fichier);
        //envoi du message d'accueil
        fichier = fopen(welcome, "w");
        fputs("SMS app:\nBienvenue et merci d'utiliser notre app.\nPour tout soucis, veuillez consulter l'équipe technique:\nSabo-kun qui a réalisé la partie après connexion.\nEvrard qui a réalisé la partie avant connexion.",fichier);
        fclose(fichier);
    }
}

