#include <stdio.h>
#include <stdlib.h>
#include "task7.h"

int main(int argc, char **argv) {

    if (argc != 2) {

        fprintf(stderr, "Invalid arguments!");
        return -1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {

        fprintf(stderr, "Couldn't open the file!");
        return -1;
    }
    char **ar = NULL;
    int lines_count = 0;
    read_file(file, &ar, &lines_count);
    polish_lines(ar, lines_count);
    qsort(ar, lines_count, sizeof(char *), (int (*)(const void *, const void *)) comparator);
    if (lines_count > COUNT_TO_PRINT) print_sorted(COUNT_TO_PRINT, ar); else print_sorted(lines_count, ar);
    for (int i = 0; i < lines_count; i++) {

        free(ar[i]);
    }
    free(ar);
	fclose(file);
    return 0;
}
