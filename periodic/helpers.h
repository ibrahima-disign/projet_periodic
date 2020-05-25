#ifndef HELPERS_H
#define HELPERS_H

#include "header.h"

/**
 * Quiter le programme lorsqu'une erreur s'est produite
 */
void erroroccurred(const char *description);

/**
 * Détermine l'action à exécuter quand le signal SIGUSR1 est capté par period
 * @param sig entier représentant la valeur du signal à exécuter
 */
void handSIGUSR1(int sig);

/**
 * Détermine l'action à exécuter quand le signal SIGUSR2 est capté par period
 * @param sig entier représentant la valeur du signal à exécuter
 */
void handSIGUSR2(int sig);

/**
 * Ajoute une entrée à la table des commandes
 */
void get_entry();

/**
 * Envoie l'ensemble de la table des commandes à dans un tube nommée
 */
void send_entries();

/**
 * Recherche de la prochaine action à exécuter
 * @return l'indice correspondant à l'action dans la table
 */
int next_action();

/**
 * Supprime un entrée de la table des commandes
 */
void delete_entry();

/**
 * Libère toutes la mémoire et toutes les allocat
 */
void free_data();

#endif /* HELPERS_H */
