#ifndef CONVERSATION_H_INCLUDED
#define CONVERSATION_H_INCLUDED
#define TAILLE_IDENTIFIANT 30
#define TAILLE_MDP 50
#define TAILLE_CHEMIN_COMPTES TAILLE_IDENTIFIANT + 35
#define TAILLE_CHEMIN_DERNIER_MESSAGE TAILLE_IDENTIFIANT + 25
#define TAILLE_MESSAGE 51

    void connected(char identifiant[TAILLE_IDENTIFIANT] );
    void add(char identifiant[TAILLE_IDENTIFIANT] );
    void see(char identifiant[TAILLE_IDENTIFIANT] );
    void look(char identifiant[TAILLE_IDENTIFIANT] );
    void send(char identifiant[TAILLE_IDENTIFIANT] );

#endif // CONVERSATION_H_INCLUDED
