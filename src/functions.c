#include "task7.h"
#include <string.h>
#include <stdlib.h>

#define FORBIDDEN_COUNT 6

static const char forbidden_symb[FORBIDDEN_COUNT] = ".,;:!?";

int comparator(const void *arg1, const void *arg2) {

    return -strcmp(*((char* const*) arg1), *((char* const*) arg2));
}

void polish_lines(char **ar, int lines_count) {

    int index;
    for (int i = 0; i < lines_count; i++) {

        for (int j = 0; j < FORBIDDEN_COUNT; j++)  {

            while (strchr(ar[i], forbidden_symb[j]) != NULL) {

                index = strchr(ar[i], forbidden_symb[j]) - ar[i];
                memmove(&ar[i][index], &ar[i][index + 1], strlen(ar[i]) - index);
            }
        }
    }
}

int read_file(FILE *file, char ***ar, int *lines_count) {

    fseek(file, 0, SEEK_END);
    long long symb_count = ftell(file);
    char *heap = calloc(symb_count + 1, sizeof(char));
    if (heap == NULL) {

        fprintf(stderr, "Couldn't allocate memory!");
        return -1;
    }
    rewind(file);
    fread(heap, symb_count, 1, file);
    *lines_count = 1;
    char *temp = heap;
    while ((temp = strchr(temp, '\n')) != NULL) {

        if (temp[1] == '\0') break;
        temp++;
        *lines_count += 1;
    }
    if (temp == NULL) strcat(heap, "\n");
    *ar = malloc(sizeof(char *) * *lines_count);
    temp = heap;
    for (int i = 0; i < *lines_count; i++) {

        (*ar)[i] = malloc(MAX_INPUT_STRING_SIZE);
        sscanf(temp, "%s\n", (*ar)[i]);
        strcat((*ar)[i], "\n");
        temp = strchr(temp, '\n') + 1;
    }
    free(heap);
    return 0;
}

void print_sorted(int count, char **ar) {

    for (int i = 0; i < count; i++) {

        printf("%s", ar[i]);
    }
}

