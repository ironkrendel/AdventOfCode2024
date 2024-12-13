#include <stdio.h>
#include <vector>
#include <math.h>

#define PRECISION 0.001

int main() {
    FILE* input = fopen("input13.txt", "r");

    char c;
    int state = 0;
    double x_1, y_1, x_2, y_2, t_x, t_y;
    double a, b;
    double result = 0;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            if (state < 3) state++;
            else {
                state = 0;

                double bottom_part = x_1 * y_2 - x_2 * y_1;

                double top_part_a = y_2 * t_x - x_2 * t_y;
                a = top_part_a / bottom_part;

                double top_part_b = x_1 * t_y - y_1 * t_x;
                b = top_part_b / bottom_part;


                if ((std::abs(a - std::round(a)) <= PRECISION) && (std::abs(b - std::round(b)) <= PRECISION)) {
                    result += a * 3 + b;
                }
            }
        }
        else {
            if (state == 3) continue;
            if (state == 0) {
                if (c == 'X') {
                    fseek(input, -1, SEEK_CUR);
                    fscanf(input, "X+%lf, Y+%lf", &x_1, &y_1);
                }
            }
            else if (state == 1) {
                if (c == 'X') {
                    fseek(input, -1, SEEK_CUR);
                    fscanf(input, "X+%lf, Y+%lf", &x_2, &y_2);
                }
            }
            else if (state == 2) {
                if (c == 'X') {
                    fseek(input, -1, SEEK_CUR);
                    fscanf(input, "X=%lf, Y=%lf", &t_x, &t_y);
                    t_x += 10000000000000;
                    t_y += 10000000000000;
                }
            }
        }
    }

    printf("%lf\n", result);

    return 0;
}