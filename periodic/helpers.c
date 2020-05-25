#include "header.h"
#include "helpers.h"
#include "message.h"

/*=============================================
=            Affichage des erreurs            =
=============================================*/
void erroroccurred(const char *description){
	perror(description);
	exit(EXIT_FAILURE);
}

/*================================
=            Handlers            =
================================*/
void handSIGUSR1(int sig){
	get_entry();
}

void handSIGUSR2(int sig){
	send_entries();
}

/*========================================================
=            Gestion des commandes à exécuter            =
========================================================*/

void get_entry(){
	// Lecture du tube nommée de la commande
	int pipe_out = open("/tmp/period.fifo", O_RDONLY);
	if (pipe_out == -1) {
		erroroccurred("open");
	}

	// Récupération de la chaine
	char **entry = recv_argv(pipe_out);

	// Ajout de la commande et des arguments dans la table des commandes
	if(entry != NULL){
		int i;
		for(i = 0; entry[i] != NULL; i++){
			// construction de la chaine
			strcpy(tab.data[tab.size][i], entry[i]);
		}

		// fin de la chaine
		tab.data[tab.size][i] = NULL;
		tab.size++;
	}

	// fermeture du tube nommé
	pipe_out = close(pipe_out);
	if(pipe_out == -1){
		erroroccurred("close");
	}
}

void send_entries(){
	// Lecture du tube nommée de la commande
	int pipe_in = open("/tmp/period.fifo", O_RDONLY);

	// envoie des entrées de la table
	int i;
	for(i = 0; i < tab.size; i++){
		// envoie de chaque entrée contenu dans la table
		int ret = send_argv(pipe_in, tab.data[i]);
		if(ret != 0){
			erroroccurred("send_argv");
		}
	}

	// fermeture du tube nommée
	if (pipe_in == -1) {
    	erroroccurred("open");
    }
}

int next_action(){
	int index_min_timestamp = -1;

	// on recherche la prochaine action à effectuer en fonction du timestamp le plus petit
	for(int i = 1; i < tab.size; i++){
		if(tab.data[i][0] < tab.data[i-1][0]){
			index_min_timestamp = i;
		}
	}
	
	return index_min_timestamp;
}

long int next_action_timestamp(){
	int i = next_action();
	long int start = atol(tab.data[i][0]);

	return (start - time(NULL));
}

void delete_entry(){
	// libérer la mémoire
}

void free_data(){
	// gérer les malloc
}
