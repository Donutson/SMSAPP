#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#define TAILLE_IDENTIFIANT 30
#define TAILLE_MDP 50

    int checkid(char id[TAILLE_IDENTIFIANT]);
    int getid(FILE* fichier, char id[TAILLE_IDENTIFIANT]);
    int takews(char *chaine, int longueur);
    void viderBuffer();
    void createdir(char* chemin);
    void identifiant(char nom[TAILLE_IDENTIFIANT ],char mdp[TAILLE_MDP], int etat);
    void viderBuffer();
    int takews(char *chaine, int longueur);
    void messagebienvenue();

#endif // UTILS_H_INCLUDED
