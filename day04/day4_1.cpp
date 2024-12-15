#include <stdio.h>
#include <vector>

#include "day4_lib.h"

int main() {
    FILE *input;
    input = fopen("input4.txt", "r");

    char c;
    int line_count = 0;
    int line_size = 0;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n')
            line_count++;
    }
    fseek(input, 0, SEEK_SET);
    while ((c = fgetc(input)) != '\n') {
        line_size++;
    }
    fseek(input, 0, SEEK_SET);

    char data[line_count * line_size];
    int current_index = 0;

    while ((c = fgetc(input)) != EOF) {
        if (c != '\n') {
            data[current_index] = c;
            current_index++;
        }
    }

    fclose(input);

    std::vector<Vector2D> x_pos;
    std::vector<Vector2D> a_pos;
    Vector2D data_size = Vector2D{line_size, line_count};
    int result = 0;

    // for (int i = 0;i < line_size * line_count;i++) {
    //     if (data[i] == 'X') {
    //         x_pos.push_back(Vector2D{i % line_size, i / line_size});
    //     }
    // }

    // for (long unsigned i = 0;i < x_pos.size();i++) {
    //     if (check_right(data, data_size, x_pos[i])) result++;
    //     if (check_left(data, data_size, x_pos[i])) result++;
    //     if (check_down(data, data_size, x_pos[i])) result++;
    //     if (check_up(data, data_size, x_pos[i])) result++;
    //     if (check_up_right(data, data_size, x_pos[i])) result++;
    //     if (check_up_left(data, data_size, x_pos[i])) result++;
    //     if (check_down_right(data, data_size, x_pos[i])) result++;
    //     if (check_down_left(data, data_size, x_pos[i])) result++;
    // }

    for (int i = 0;i < line_size * line_count;i++) {
        if (data[i] == 'A') {
            a_pos.push_back(Vector2D{i % line_size, i / line_size});
        }
    }

    for (long unsigned int i = 0;i < a_pos.size();i++) {
        if (check_mas(data, data_size, a_pos[i])) result++;
    }

    printf("%d\n", result);
    
    return 0;
}