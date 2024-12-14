#include <stdio.h>
#include <vector>
#include <chrono>
#include <thread>

#define WIDTH 101
#define HEIGHT 103
#define SECONDS 0

struct Vector2D {
    int x;
    int y;
};

int main() {
    FILE* input = fopen("input14.txt", "r");

    char c;
    int pos_x, pos_y, v_x, v_y;
    std::vector<Vector2D> positions;
    std::vector<Vector2D> velocities;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            positions.push_back(Vector2D{pos_x, pos_y});
            velocities.push_back(Vector2D{v_x, v_y});
        }
        else {
            fseek(input, -1, SEEK_CUR);
            fscanf(input, "p=%d,%d v=%d,%d", &pos_x, &pos_y, &v_x, &v_y);
        }
    }

    int data[HEIGHT][WIDTH];

    for (int i = 0;i < HEIGHT;i++) {
        for (int j = 0;j < WIDTH;j++) {
            data[i][j] = 0;
        }
    }

    for (std::size_t i = 0;i < positions.size();i++) {
        data[positions[i].y][positions[i].x]++;
    }

    // for (int i = 0;i < HEIGHT;i++) {
    //     for (int j = 0;j < WIDTH;j++) {
    //         if (data[i][j] == 0) {
    //             printf(".");
    //         }
    //         else {
    //             printf("%d", data[i][j]);
    //         }
    //     }
    //     printf("\n");
    // }

    int s = SECONDS + 1;
    for (;;) {
        for (std::size_t i = 0;i < positions.size();i++) {
            positions[i].x += velocities[i].x;
            positions[i].y += velocities[i].y;
            if (positions[i].x > 0) positions[i].x = positions[i].x % WIDTH;
            if (positions[i].y > 0) positions[i].y = positions[i].y % HEIGHT;
            if (positions[i].x < 0) positions[i].x = (WIDTH + positions[i].x % WIDTH) % WIDTH;
            if (positions[i].y < 0) positions[i].y = (HEIGHT + positions[i].y % HEIGHT) % HEIGHT;

            // printf("%d %d\n", positions[i].x, positions[i].y);
        }

        for (int i = 0;i < HEIGHT;i++) {
            for (int j = 0;j < WIDTH;j++) {
                data[i][j] = 0;
            }
        }

        for (std::size_t i = 0;i < positions.size();i++) {
            // printf("%d %d\n", positions[i].x, positions[i].y);
            data[positions[i].y][positions[i].x]++;
        }


        // printf("\n%d)\n\n", s);
        // for (int i = 0;i < HEIGHT;i++) {
        //     for (int j = 0;j < WIDTH;j++) {
        //         if (data[i][j] == 0) {
        //             printf(".");
        //         }
        //         else {
        //             printf("%d", data[i][j]);
        //         }
        //     }
        //     printf("\n");
        // }

        for (int i = 0;i < HEIGHT - 1;i++) {
            for (int j = 0;j < WIDTH - 1;j++) {
                if (data[i][j] > 0 && data[i][j + 1] > 0 && data[i + 1][j] > 0) {
                    int w = 0, h = 0;
                    int _i = i, _j = j;
                    while (_j < WIDTH && data[i][_j] > 0) {
                        w++;
                        _j++;
                    }
                    while (_i < HEIGHT && data[_i][j] > 0) {
                        h++;
                        _i++;
                    }
                    if (w > 5 && h > 5) {
                        // printf("%d %d\n", w, h);
                        printf("%d\n", s);
                        return 0;
                    }
                }
            }
        }

        s++;
        // std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    // for (std::size_t i = 0;i < positions.size();i++) {
    //     positions[i].x += velocities[i].x * SECONDS;
    //     positions[i].y += velocities[i].y * SECONDS;
    //     if (positions[i].x > 0) positions[i].x = positions[i].x % WIDTH;
    //     if (positions[i].y > 0) positions[i].y = positions[i].y % HEIGHT;
    //     if (positions[i].x < 0) positions[i].x = (WIDTH + positions[i].x % WIDTH) % WIDTH;
    //     if (positions[i].y < 0) positions[i].y = (HEIGHT + positions[i].y % HEIGHT) % HEIGHT;

    //     // printf("%d %d\n", positions[i].x, positions[i].y);
    // }

    // for (int i = 0;i < HEIGHT;i++) {
    //     for (int j = 0;j < WIDTH;j++) {
    //         data[i][j] = 0;
    //     }
    // }

    // for (std::size_t i = 0;i < positions.size();i++) {
    //     // printf("%d %d\n", positions[i].x, positions[i].y);
    //     data[positions[i].y][positions[i].x]++;
    // }

    // for (int i = 0;i < HEIGHT;i++) {
    //     for (int j = 0;j < WIDTH;j++) {
    //         if (data[i][j] == 0) {
    //             printf(".");
    //         }
    //         else {
    //             printf("%d", data[i][j]);
    //         }
    //     }
    //     printf("\n");
    // }

    // int t_l = 0, t_r = 0, b_l = 0, b_r = 0;
    // for (int i = 0;i < HEIGHT / 2;i++) {
    //     for (int j = 0;j < WIDTH / 2;j++) {
    //         t_l += data[i][j];
    //     }
    // }
    // for (int i = 0;i < HEIGHT / 2;i++) {
    //     for (int j = WIDTH / 2 + 1;j < WIDTH;j++) {
    //         t_r += data[i][j];
    //     }
    // }
    // for (int i = HEIGHT / 2 + 1;i < HEIGHT;i++) {
    //     for (int j = 0;j < WIDTH / 2;j++) {
    //         b_l += data[i][j];
    //     }
    // }
    // for (int i = HEIGHT / 2 + 1;i < HEIGHT;i++) {
    //     for (int j = WIDTH / 2 + 1;j < WIDTH;j++) {
    //         b_r += data[i][j];
    //     }
    // }

    // printf("%d %d %d %d\n", t_l, t_r, b_l, b_r);
    // printf("\n%d\n", t_l * t_r * b_l * b_r);

    return 0;
}