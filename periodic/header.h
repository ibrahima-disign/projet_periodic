#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

// taille du buffer
#define BUFSIZE 256

struct table{
    char **data[1024];
    size_t size;
};

struct table tab; // allocation dans le tas pour faciliter les libérations plus tard

// tab[0][0][]

#endif /* HEADER_H */
