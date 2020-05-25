#include "header.h"

/* 
* Programme principal
*/
int main(int argc, char *argv[]) {

	int status;

	// le processus principal forke
	pid_t pid_1 = fork();

	if (pid_1 == -1) {
		errorocurred("fork");
	}
	// fils
	if (pid_1 == 0) {
		// le fils devient leader de session
		pid_t ret = setsid();
		if (ret == -1) {
    		errorocurred("setsid");
    	}
    	// le fils forke
    	pid_t pid_2 = fork();
    	if (pid_2 == -1) {
    		errorocurred("fork");
    	}
    	// fils
    	if (pid_2 > 0) {
    		// le fils quitte
    		exit(0);
    	}
    	// petit fils
    	if (pid_2 == 0) {
    		// Changement du umask à 0
    		umask(0);
    		// Changement du répertoire
    		if ( chdir("/") < 0) {
		        errorocurred("chdir");
		    }
		    // Fermeture des flux standards
		    close(STDIN_FILENO);
    		close(STDOUT_FILENO);
   			close(STDERR_FILENO);
   			// initialisation des arguments pour l'exécution de period
   			char *period_args[] = {argv[1], NULL};
   			// exécution de period
   			if (execv(argv[1], period_args) == -1) {
   				errorocurred("execv");
   			}
    	}
    }
    // père
	if (pid_1 > 0) {
		// le père attend son fils
		wait(&status);
	}

	return 0;
}
