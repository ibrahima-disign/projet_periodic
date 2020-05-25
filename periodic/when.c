#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc,char *argv[]) {
	
	time_t my_time = atoi(argv[1]);
	
	printf("%s", ctime(&my_time));
	return 0;

}
