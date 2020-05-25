#ifndef MESSAGE_H
#define MESSAGE_H

#include "header.h"

/**
 * Envoie une chaine de caractères via un descripteur de fichier
 * @param  fd  entier représentant le descripteur de fichier
 * @param  str la chaine à envoyer
 * @return     renvoie 0 si tout s'est bien passé ou -1 sinon
 */
int send_string(int fd, char *str);

/**
 * Reçoit une chaine de caractère via un descripteur de fichier
 * @param  fd descripteur de fichier
 * @return    renvoie une chaine de caractère ou NULL
 */
char *recv_string(int fd);

/**
 * Envoie un tableau de chaines de caractères
 * @param  fd   descripteur de fichier
 * @param  argv tableau de chaines
 * @return      renvoie un 0 si reussi -1 sinon
 */
int send_argv(int fd, char *argv[]);

/**
 * Recoit un tableau de chaines de caractères via un descripteur
 * @param  fd descripteur de fichier
 * @return    renvoie un tableau de chaine ou NULL
 */
char **recv_argv(int fd);


#endif /* MESSAGE_H */
