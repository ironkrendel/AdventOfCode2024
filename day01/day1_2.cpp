#include <stdio.h>
#include <unordered_map>

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
    long long similarity = 0;
    std::unordered_map<int, int> frequency;

    printf("%d\n", length);

    for (int i = 0;i < length;i++) {
        fscanf(input, "%d", &larr[i]);
        fscanf(input, "%d", &rarr[i]);
        frequency[rarr[i]] += 1;
    }

    fclose(input);

    for (int i = 0;i < length;i++) {
        similarity += larr[i] * frequency[larr[i]];
    }

    printf("%lld\n", similarity);

    return 0;
}