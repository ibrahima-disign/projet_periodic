#include "header.h"
#include "helpers.h"

int main(int argc, char const *argv[])
{ 
    /*=======================================
    =            Ecriture du PID            =
    =======================================*/
    
    //Tentative d'ouverture du fichier
    int read_desc = open("/tmp/period.pid", O_RDONLY);
    int ret = 0;

    // Si = -1 le fichier existe déjà
    if(read_desc != -1){
        printf("Le fichier \"/tmp/period.pid\" existe déjà\n");
        // fermeture du descripteur de fichier pour la lecture
        ret = close(read_desc);
        if(ret != 0){
            erroroccurred("close read_desc");
        }
        exit(0); 
    }

    // ouverture d'un descripteur de fichier pour l'écriture
    pid_t pid = getpid();
    printf("%d", pid);
    int write_desc = open("/tmp/period.pid", O_WRONLY | O_CREAT, 0644);

    if(write_desc == -1){
        erroroccurred("period open write_desc 1");
    }

    // Ecriture du pid dans le fichier
    int s1 = write(write_desc, &pid, sizeof(pid_t));

    // Valeur de retour
	if(s1 != sizeof(pid_t))
	{
		erroroccurred("period open write s1");
	}

    // fermeture du descripteur de fichier pour l'écriture'
    ret = close(write_desc);
    if(ret != 0){
        erroroccurred("close write_desc 1");
    }

    /*======================================================
    =            Mise en place des redirections            =
    ======================================================*/

    // SORTIE STANDARD
    // ouverture de ./tmp/period.out s'il n'existe pas il est crée
    write_desc = open("/tmp/period.out", O_WRONLY | O_CREAT, 0644);
    if(write_desc == -1){
        erroroccurred("period write_desc 2");
    }

    // redirections de la sortie standard vers le fichier
    ret = dup2(write_desc, 1);
    if(ret == -1){
        erroroccurred("dup2 write_desc 1");
    }

    // fermeture du descripteur de fichier pour l'écriture'
    ret = close(write_desc);
    if(ret != 0){
        erroroccurred("close write_desc 2");
    }

    // SORTIE D'ERREUR STANDARD
    // ouverture de ./tmp/period.out s'il n'existe pas il est crée
    write_desc = open("/tmp/period.err", O_WRONLY | O_CREAT, 0644);
    if(write_desc == -1){
        erroroccurred("period write_desc 3");
    }

    // redirections de la sortie standard vers le fichier
    ret = dup2(write_desc, 2);
    if(ret == -1){
        erroroccurred("dup2 write_desc 2");
    }

    // fermeture du descripteur de fichier pour l'écriture'
    ret = close(write_desc);
    if(ret != 0){
        erroroccurred("close write_desc 3");
    }

    // CREATION DU REPERTOIRE PERIOD
    if (mkfifo("/tmp/period.fifo", 0644) != 0) {
        erroroccurred("mkfifo");
    }

    ret = mkdir("/tmp/perid", 0755);

    if(ret == -1){
        erroroccurred("mkdir");
    }

    tab.size = 0;

    /*========================================================
    =            Ajout d’une entrée dans la table            =
    ========================================================*/
    
    struct sigaction action1;
    sigemptyset(&action1.sa_mask);
    action1.sa_handler = handSIGUSR1;
    action1.sa_flags = 0;
    sigaction(SIGUSR1, &action1, NULL);

    /*==================================================
    =            Envoi de la table courante            =
    ==================================================*/
    struct sigaction action2;
    sigemptyset(&action2.sa_mask);
    action2.sa_handler = handSIGUSR2;
    action2.sa_flags = 0;
    sigaction(SIGUSR2, &action2, NULL);

}

// start period cmd [args]
// start period cmd [args]
// start period cmd [args]
// start period cmd [args] sort du plus recent au plus tard

// periodic => period SIGUR1
// SIGUR1 => period recevoir des données
// SIGUR2 => period envoie des données
