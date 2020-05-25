//#include "libmessage.h"
#include "message.h"

int send_string(int fd, char *str){
	int s1 = 0, s2 = 0, length = strlen(str);
	//printf("length chaine %zu\n", length);
	// Ecriture de la taille de la chaine
	s1 = write(fd, &length, sizeof(length));
	
	// Valeur de retour
	if(s1 != sizeof(length))
	{
		perror("send_string write s1");
		return -1; // on renvoie -1 en cas d'erreur
	}
	
	// Ecriture de la chaine elle-même
	int to_read = sizeof(char)*length;
	s2 = write(fd, str, to_read);
	
	// Valeur de retour
	if(s2 != to_read)
	{
		perror("send_string write s2");
		return -1; // on renvoie -1 en cas d'erreur
	}
	
	// Fermeture du descripteur de fichier à faire plus tard
	// close(fd);
	return 0;
}

char *recv_string(int fd){

	int buf;
	// Lecture de la taille de la chaine
	size_t sz = read(fd, &buf, sizeof(buf));
	
	// Valeur de retour
	if(sz != sizeof(buf))
	{
		perror("recv_string read sz 1");
		return NULL;
	}
	
	// Constitution de la chaine à lire
	char *string = malloc((buf + 1) * sizeof(char));
	if(string == NULL)
	{
		printf("Allocation mémoire non reussie\n");
		return NULL;
	}

	// Lecture de la chaine
	size_t to_read = sizeof(char)*buf;
	sz = read(fd, string, to_read);
	
	// On ajoute le "\0" à la fin de la chaine
	string[buf+1] = '\0';

	if(sz != to_read)
	{
		perror("recv_string read sz 2");
		return NULL;
	}
	
	// Fermeture du descripteur de fichier à faire plus tard
	// close(fd);
	return string;
}

int send_argv(int fd, char *argv[]){
	// On détermine la taille du tableau de chaine
	int array_size = 0;;
	for (;argv[array_size] != NULL; array_size++);
		// printf("Array_size : %d\n", array_size);

	// Envoie de la taille du tableau
		size_t s1 = write(fd, &array_size, sizeof(array_size));
	
	// Valeur de retour
	if(s1 != sizeof(array_size))
	{
		perror("send_argv write s1");
		return -1; // on renvoie -1 en cas d'erreur
	}

	// On parcourt tout le tableau
	for(size_t i = 0; i < array_size; ++i) 
	{
		// Ecriture de chaque chaine de caractères
		int to_write = sizeof(char)*strlen(argv[i]);
		size_t s2 = write(fd, argv[i], to_write);
		
		// Valeur de retour
		if(s2 != to_write)
		{
			perror("send_argv write s2");
			return -1; // on renvoie -1 en cas d'erreur
		}

		char fin_de_chaine = '\0';
		size_t s3 = write(fd, &fin_de_chaine, sizeof(char));

		// Valeur de retour
		if(s3 != sizeof(char))
		{
			perror("send_argv write s2");
			return -1; // on renvoie -1 en cas d'erreur
		}
	}
	return 0; // <<========== tout s'est bien passé
}

char **recv_argv(int fd){
	int array_size;
	// Lecture de la taille du tableau
	size_t sz = read(fd, &array_size, sizeof(array_size));
	// printf("recv_argv : %d\n", array_size);

	// Valeur de retour
	if(sz != sizeof(array_size))
	{
		perror("recv_argv read sz 1");
		return NULL;
	}

	// Allocation de la taille du tableau de chaine nécessaire
	char **argv_string = malloc((array_size) * sizeof(char*));
	// vérification de l'allocation mémoire
	if(argv_string == NULL)
	{
		printf("Allocation mémoire non reussie\n");
		return NULL;
	}

	// On parcourt tout le fichier pour récupérer toutes les chaines
	// on lit le fichier caractère par caractère

	for(size_t i = 0; i < array_size; ++i)
	{	
		char char_read;		
		char arg_string[BUFSIZE];

		do
		{
			//printf("%zu\n", strlen(arg_string));
			// Ecriture de chaque chaine de caractères
			size_t s2 = read(fd, &char_read, sizeof(char));

			// Valeur de retour
			if(s2 != sizeof(char))
			{
				perror("recv_argv read s2");
				return NULL; // on renvoie -1 en cas d'erreur
			}

			arg_string[strlen(arg_string)] = char_read;
		}while(char_read != '\0');

		// arg_string[strlen(arg_string)+1] ='\0';
		argv_string[i] = malloc(strlen(arg_string) * sizeof(char)); 
		
		// ajout de la chaine au tableau de chaine
		strcpy(argv_string[i], arg_string);

		// reinitialisation du buffer
		for(int k = 0; k < BUFSIZE; k++)
		{
		    arg_string[k] = 0;
		}
		
	} // fin du for
	
	// On ajoute le NULL à la fin de la chaine
	argv_string[array_size] = NULL;

	return argv_string;
}

// send_string(4, "blabla"); 
// 7Bonjour
