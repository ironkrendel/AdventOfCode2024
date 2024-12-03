#include <stdio.h>
#include <math.h>
#include <queue>
#include <cstring>
#include <algorithm>

bool valid_data(int* data, int size) {
    if (size <= 1) {
        return true;
    }
    else if (size == 2) {
        return std::abs(data[1] - data[0]) >= 1 && std::abs(data[1] - data[0]) <= 3;
    }

    if (!(std::abs(data[1] - data[0]) >= 1 && std::abs(data[1] - data[0]) <= 3)) {
        printf("| %d %d | ", data[1], data[0]);
        return false;
    }
    for (int i = 2;i < size;i++) {
        if (!(std::abs(data[i] - data[i - 1]) >= 1 && std::abs(data[i] - data[i - 1]) <= 3)) {
            return false;
        }
        else {
            if ((data[i] - data[i - 1] < 0 && data[i - 1] - data[i - 2] > 0) || \
                (data[i] - data[i - 1] > 0 && data[i - 1] - data[i - 2] < 0)) {
                    return false;
                }
        }
    }
    return true;
}

void remove_element(int** array, int length, int index) {
    int* new_array = new int[length - 1];
    for (int i = 0;i < length;i++) {
        if (i < index) {
            new_array[i] = (*array)[i];
        }
        else if (i > index) {
            new_array[i - 1] = (*array)[i];
        }
    }
    delete *array;
    *array = new_array;

    return;
}

int main() {
    FILE *input;
    input = fopen("input2.txt", "r");

    char c;
    int safe_count = 0;
    int* nums = new int[1];
    int length = 0;
    int num;
    bool new_line = true;
    int skip_index = -1;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            int* new_nums = new int[1];
            for (int i = 0;i < length;i++) {
                delete new_nums;
                new_nums = new int[length];
                std::memcpy(new_nums, nums, length * sizeof(int));
                remove_element(&new_nums, length, i);
                printf("%d ", valid_data(new_nums, length - 1));
                if (valid_data(new_nums, length - 1)) {
                    safe_count++;
                    break;
                }
            }
            delete new_nums;
            if (valid_data(nums, length)) {
                if (safe_count == 0)
                    safe_count++;
            }
            printf("\n");
            new_line = true;
            delete nums;
            nums = new int[1];
            length = 0;
        }
        else {
            fseek(input, -1, SEEK_CUR);
        }
        fscanf(input, "%d", &num);
        length++;
        nums = (int*)realloc(nums, length * sizeof(int));
        nums[length - 1] = num;
        printf("%d ", num);
    }

    printf("- %d\n", safe_count);

    fclose(input);

    return 0;
}