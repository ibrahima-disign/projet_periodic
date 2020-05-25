#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	/**
	
		TODO:
		- Contrôler systématiquement les valeurs de retour des appels systèmes <======== IMPORTANT
		- Commentaires à faire
		- period et periodic à faire avant launch_deamon
		- ./period kl pas de redirection
		- ./periodic et ./period communiquent par un tube nommée crée dans ./tmp/periodic.pid
		- ./periodic +20 6 echo bonjour // toutes les 6 secondes et 20 secondes après l'instant présent
		- DEBUG : pid of period 2325 dans 
		- ./periodic et Appel alarm : 20  
		- Appel alarm : 6
		- 2397 terminé, code = 0
		- ls /tmp/period
		- 1.err 1.out
		- ./periodic
		- DEBUG : pid of period 2325
		- Registred commands : 
			1. 1493905133 6 echo bonjour
		- ./periodic remove 2 // supprimer la commande numéro 2 dans la table de commande 
		- valgrind pour les fuites mémoires
	 */
	
	return 0;
}
