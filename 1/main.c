#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

int count_lines(FILE *file, int *lines);
int read_values(FILE *file, int *left, int *right, int line_count);
void sort_list(int *list, size_t size);
void total_distance(int line_count, int *left, int *right, int *result);
void calc_similarity(int line_count, int *left, int *right, int *result);

int main(int argc, char *argv[])
{
    FILE *file = NULL;
    int ret = 0;
    int line_count = 0;
    int distance = 0;
    int similarity = 0;
    int *left_list, *right_list;

    if (argc < 2) {
        printf("No input file given\n");
        return -1;
    }

    file = fopen(argv[1], "r");
    if (!file) {
        printf("Failed to open given file\n");
        return -1;
    }

    ret = count_lines(file, &line_count);
    if(!ret){
        printf("Error counting lines\n");
        goto out;
    }

    left_list = malloc(line_count * sizeof(int));
    right_list = malloc(line_count * sizeof(int));

    ret = read_values(file, left_list, right_list, line_count);

    /* for (int i = 0; i < line_count; i++) {
        printf("Left[%d] = %d, Right[%d] = %d\n", i, left_list[i], i, right_list[i]);
    } */

    sort_list(left_list, line_count);
    sort_list(right_list, line_count);
    for (int i = 0; i < line_count; i++) {
        printf("Left[%d] = %d, Right[%d] = %d\n", i, left_list[i], i, right_list[i]);
    }
    total_distance(line_count, left_list, right_list, &distance);
    printf("Total distance is %d\n", distance);

    calc_similarity(line_count, left_list, right_list, &similarity);
    printf("Calculated similiartiy is %d\n", similarity);

out:
    fclose(file);
    free(left_list);
    free(right_list);

    return ret;
}

int count_lines(FILE *file, int *lines)
{
    int line_count = 0;
    char tmp_char;

    while((tmp_char = fgetc(file)) != EOF) {
        if (tmp_char == '\n') {
            line_count++;
        }
    }
    *lines = line_count;

    return feof(file);
}

int read_values(FILE *file, int *left, int *right, int line_count)
{
    int ret = 0;
    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < line_count; i++) {
        ret = fscanf(file, "%d   %d", &left[i], &right[i]);

        if (ret != 2) {
            printf("Error reading line %d. Expected two integers, got %d.\n", i + 1, ret);
            break;
        }main.c
}

int compare(const void *a, const void *b) 
{
    return (*(int *)a - *(int *)b);
}

void sort_list(int *list, size_t size)
{
    qsort(list, size, sizeof(int), compare);
}

void total_distance(int line_count, int *left, int *right, int *result)
{
    for(int i = 0; i < line_count; i++)
    {
        *result += abs(left[i] - right[i]);
    }
}

void calc_similarity(int line_count, int *left, int *right, int *result)
{
    for(int i = 0; i < line_count; i++)
    {
        for(int j = 0; j < line_count; j++)
        {
            if (left[i] == right[j])
                *result += left[i];
        }
    }
}