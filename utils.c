#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dir.h>
#include <dirent.h>
#include "utils.h"


int checkid(char id[TAILLE_IDENTIFIANT])
{
    //cette fonction v�rifie qu'une identifiant se trou:ve parmi les comptes inscrits
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
    //il faut n�anmoins s'assurer d'�tre en d�but de ligne
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
        //on va � la ligne suivantz
        //si nous e= s�mmes pas �  la derni�re ligne
    {
        lettre = fgetc(fichier);
    }
    if(lettre == EOF)
            i = 0;
    return i;
}

int takews(char *chaine, int longueur)
{
    //cette fonction lit l'entr�e standard en prenant en compte les espaces
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
    //cette fonction permet de cr�er un dossier si celui-ci n'existe pas
    //elle a juste besoin du chemin de ce dossier
    //elle a besoin de dirent.h et dir.h pour fonctionner
    DIR* dir;
    dir = opendir(chemin);//on �ssaye d'ouvrir le dossier
    if(dir == NULL)//si l'ouverture �choue
    {
        mkdir(chemin);//on cr�e le dossier
    }
    closedir(dir);
}


void identifiant(char nom[TAILLE_IDENTIFIANT],char mdp[TAILLE_MDP], int etat)
{
    //Cette fonction n'est pas n�cessaire,c'est juste pour �viter de rep�ter le m�me code
    //dans nos fonctions principales

    //le param�tre etat permet de g�rer diff�remment une connnexion d'un enregistrement
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

	/*fgets prend en compte le caract�re de saut de ligne "\n" lorsqu'on frappe sur "entr�e"*/
	/*on va donc remplacer ce saut de ligne par un caract�re de fin de chaine "\0"*/
	/*si on ne le fait pas,on aura un saut de ligne avant l'impression du mot de passe*/
	while(i<TAILLE_IDENTIFIANT ){
		if (nom[i]=='\n') {
			nom[i]='\0';
			break;}
		i++;
	};
	i = 0;//r�initialisation
	/*Saisie s�curis�e du mot de passe*/
	printf("\nMot de passe:");
	/* Ici getch est utilis� pour la saisie s�curis�e du mot de passe(il n'affiche pas ce qu'on �crit)*/
	/*A la place des caract�res invisibles,on affiche des "*" en nous assurant que */
	/*chaque caract�re saisi est bien plac� dans un endroit(une variable),dans notre cas*/
	/*l'endroit c'est user_password que l'on forme caract�re par caract�re*/
	/*<getch!='\r'> est n�cessaire pour que la boucle s'arr�te d�s qu'on frappe sur "entr�e"*/
	/*pour rappel,"\r"(retour chariot) <==>"\n"(saut de ligne) sur la plupart des OS mais sur windows,*/
	/*les deux ne signifient pas vraiment la m�me chose*/
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
    //cette fonction se charge d'�diter et d'envoyer le message de bienvenue
    //elle cr�e par la m�me occasion un fichier contenat le numm�ro du dernier message
    char welcome[TAILLE_CHEMIN_COMPTES]= "C:Sms app/Comptes/", index[TAILLE_CHEMIN_COMPTES]="C:Sms app/Comptes/";
    FILE* fichier = NULL;
    //�dition des diff�rents ch�mins
    strcat(welcome,id);
    strcat(welcome,"/0.txt");
    strcat(index,id);
    strcat(index,"/derniermessage.txt");
    //on s'assure que la chose n'a pas d�j� �t� fait,e
    fichier = fopen(index, "r");
    if(fichier == NULL)
    {
        fclose(fichier);
        //cr�ation et remplissage de derniermessage.txt
        fichier = fopen(index, "w");
        fprintf(fichier, "%d",0);
        fclose(fichier);
        //envoi du message d'accueil
        fichier = fopen(welcome, "w");
        fputs("SMS app:\nBienvenue et merci d'utiliser notre app.\nPour tout soucis, veuillez consulter l'�quipe technique:\nSabo-kun qui a r�alis� la partie apr�s connexion.\nEvrard qui a r�alis� la partie avant connexion.",fichier);
        fclose(fichier);
    }
}

