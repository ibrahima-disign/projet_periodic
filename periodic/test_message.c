
#include "message.h"

int main(int argc, char const *argv[])
{
	// Ecriture
	int write = open("fic", O_WRONLY | O_CREAT, 0644);
	if(write == -1){
		perror("open");
		return 3;
	}

	char *arg[] = {"Praspel", "Java", "Laravel", NULL};

	send_string(write, arg[0]);
	
	// send_argv(write, arg);

	// // Lecture 
	int read = open("fic", O_RDONLY);
	if(read == -1){
		perror("open");
		return 3;
	}
	
	printf("%s", recv_string(read));
	
	char **tab = recv_argv(read);

	for(int i = 0; tab[i] != NULL; ++i) {
		printf("%s\n", tab[i]);
	}

	
	close (read);
	close (write);
	return 0; 
}
