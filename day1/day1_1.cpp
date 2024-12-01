#include <stdio.h>
#include <algorithm>

int main() {
    FILE *input;
    input = fopen("input1.txt", "r");

    char c;
    int length = 0;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n')
            length++;
    }
    fseek(input, 0, SEEK_SET);

    int* larr = new int[length];
    int* rarr = new int[length];
    int distance = 0;

    for (int i = 0;i < length;i++) {
        fscanf(input, "%d", &larr[i]);
        fscanf(input, "%d", &rarr[i]);
    }

    fclose(input);

    std::sort(larr, larr + length);
    std::sort(rarr, rarr + length);

    for (int i = 0;i < length;i++) {
        if (larr[i] >= rarr[i]) {
            distance += larr[i] - rarr[i];
        }
        else {
            distance += rarr[i] - larr[i];
        }
    }

    printf("%d\n", distance);

    return 0;
}