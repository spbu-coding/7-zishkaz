#include <stdio.h>

#ifndef TASK7_TASK7_H
#define TASK7_TASK7_H

#define MAX_INPUT_STRING_SIZE 1000
#define COUNT_TO_PRINT 100

int comparator(const void *, const void *);
void polish_lines(char **, int);
int read_file(FILE *, char ***, int *);
void print_sorted(int, char **);

#endif //TASK7_TASK7_H
