#include "header.h"
#include "helpers.h"
#include "message.h"

// message à afficher en cas d'arreur
#define USAGE "Usage : ./periodic start period cmd [args]\n"

/* 
* Programme principal
*/
int main(int argc, char *argv[]) {

	// valeurs de retour utilisée pour les contrôle
	int ret;
	char buffer[BUFSIZE];

	/*=========================================
	=           CONTRÔLES ARGUMENTS           =
	=========================================*/
	
	// test du nb d'arguments
	if (argc < 4) {
		fprintf(stderr, "Mauvais nombre d'arguments.\n%s", USAGE);
		exit(EXIT_FAILURE);
	}
	
	// si start ne vaut pas "now" ou ne commence pas par '+', on stock start dans une variable en vue de tester sa validité
	char *endptr;
	long int start;
	if (strcmp(argv[1], "now") != 0 && argv[1][0] != '+') {
		start = strtol(argv[1], &endptr, 10);
		// test du type de l'argument 1 (start)
		if (strcmp(endptr, argv[1]) == 0) {
	        fprintf(stderr, "start n'est pas un nombre\n%s", USAGE);
	        erroroccurred("args");
	    }
	}
	// si start vaut now
	if (strcmp(argv[1], "now") != 0) {
		start = time(NULL) + 1;
	}
	// si start vaut +N
	if (argv[1][0] != '+') {
		start = time(NULL) + 1 + atol(argv[1]);
	}

    // définition du tableau des infos à envoyer plus tard dans le tube
    char *infos_to_send[argc];
    assert(infos_to_send != NULL);
    infos_to_send[0] = malloc(BUFSIZE * sizeof(char));
    sprintf(infos_to_send[0], "%ld", start);
    infos_to_send[1] = malloc(sizeof(argv[2]));
    strcpy(infos_to_send[1], argv[2]);
    for (int i = 3; i < argc; ++i) {
    	infos_to_send[i - 1] = malloc(sizeof(argv[i]));
    	infos_to_send[i - 1] = argv[i];
    }
    infos_to_send[argc - 1] = NULL;

    /*=========================================
	=        RECUPERATION PID DAEMON          =
	=========================================*/

    // pid du daemon
    pid_t daemon_pid;
    // ouverture du fichier contenant le pid du daemon
    pid_t daemon_pid_file = open("./tmp/period.pid", O_RDONLY);
    if (daemon_pid_file == -1) {
    	erroroccurred("open");
    }
    
    // récupération du pid (chaine) depuis le fichier
    ret = read(daemon_pid_file, buffer, 2);
	if (ret == -1) {
		erroroccurred("gets");
	}

	// conversion en entier
    daemon_pid = atoi(buffer);

    // fermeture du fichier
    ret = close(daemon_pid_file);
    if (ret == -1) {
    	erroroccurred("close");
    }

    /*=========================================
	=    AJOUT D'UNE ENTREE DANS LA TABLE     =
	=========================================*/

    // envoi du signal SIGUSR1
    ret = kill(daemon_pid, SIGUSR1);
    if (ret == -1) {
    	erroroccurred("SIGUSR1");
    }

    // ouverture du descripteur
    int pipe_in = open("/tmp/period.fifo", O_WRONLY);
    if (pipe_in == -1) {
    	erroroccurred("open");
    }

    // envoi des infos dans le tube
    ret = send_argv(pipe_in, infos_to_send);

    // fermeture du descripteur
    ret = close(pipe_in);
    if (ret == -1) {
    	erroroccurred("close");
    }

    /*=========================================
	=        RECUPERATION DE LA TABLE         =
	=========================================*/

	// envoi du signal SIGUSR2
    ret = kill(daemon_pid, SIGUSR2);
    if (ret == -1) {
    	erroroccurred("SIGUSR2");
    }

    // ouverture du tube
    int pipe_out = open("/tmp/period.fifo", O_RDONLY);
    if (pipe_out == -1) {
    	erroroccurred("open");
    }

    // réception de la table dans tab
    char **tab = NULL;
	tab = recv_argv(pipe_out);
	if (tab == NULL) {
		erroroccurred("recv");
	}

	// affichage de l'ensemble des commandes
	for (size_t i = 1; tab[i] != NULL; ++i) {
		printf("%s ", tab[i]);
	}

	// fermeture du descripteur
    ret = close(pipe_out);
    if (ret == -1) {
    	erroroccurred("close");
    }

	return 0;
}


