#include <stdio.h>
#include <vector>
#include <set>
#include <iostream>

struct Vector2D {
    int x;
    int y;
};

void GetFrequencyPositions(std::vector<std::vector<char>*> *data, std::vector<Vector2D> *result, char frequency);

int main() {
    FILE *input;
    input = fopen("input8.txt", "r");

    std::set<char> sfrequencies;
    std::vector<char> frequencies;
    std::vector<std::vector<char>*> data;
    int height = 0, width = 0;
    
    char c;
    std::vector<char>* tmp_vec = new std::vector<char>;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            data.push_back(tmp_vec);
            tmp_vec = new std::vector<char>;
            height++;
        }
        else {
            if (c != '.') {
                sfrequencies.insert(c);
            }
            tmp_vec->push_back(c);
            width++;
        }
    }
    width = width / height;
    delete tmp_vec;

    fclose(input);

    std::set<char>::iterator set_iter = sfrequencies.begin();
    for (size_t i = 0;i < sfrequencies.size();i++) {
        frequencies.push_back(*set_iter);
        set_iter++;
    }

    bool results[height][width] = {false};
    for (int i = 0;i < height;i++) {
        for (int j = 0;j < width;j++) {
            results[i][j] = false;
        }
    }

    int answer = 0;
    for (size_t f = 0;f < frequencies.size();f++) {
        std::vector<Vector2D> positions;
        GetFrequencyPositions(&data, &positions, frequencies[f]);

        for (size_t i = 0;i < positions.size();i++) {
            for (size_t j = 0;j < positions.size();j++) {
                if (i == j) continue;

                int delta_x = positions[j].x - positions[i].x;
                int delta_y = positions[j].y - positions[i].y;

                int move_x = delta_x;
                int move_y = delta_y;

                while ((positions[j].x + move_x >= 0) && (positions[j].x + move_x < width) && (positions[j].y + move_y >= 0) && (positions[j].y + move_y < width)) {
                    printf("%d %d\n", delta_x, delta_y);
                    results[positions[j].y + move_y][positions[j].x + move_x] = true;
                    move_x += delta_x;
                    move_y += delta_y;
                }

                move_x = 0;
                move_y = 0;

                while ((positions[j].x + move_x >= 0) && (positions[j].x + move_x < width) && (positions[j].y + move_y >= 0) && (positions[j].y + move_y < width)) {
                    printf("%d %d\n", delta_x, delta_y);
                    results[positions[j].y + move_y][positions[j].x + move_x] = true;
                    move_x -= delta_x;
                    move_y -= delta_y;
                }
            }
        }
    }

    for (int i = 0;i < height;i++) {
        for (int j = 0;j < width;j++) {
            if (results[i][j]) {
                answer++;
                printf("#");
            }
            else {
                printf("%c", (*data[i])[j]);
            }
        }
        printf("\n");
    }

    printf("%d\n", answer);
    
    return 0;
}

void GetFrequencyPositions(std::vector<std::vector<char>*> *data, std::vector<Vector2D> *result, char frequency) {
    for (size_t i = 0;i < data->size();i++) {
        for (size_t j = 0;j < (*data)[0]->size();j++) {
            if ((*(*data)[i])[j] == frequency) {
                result->push_back(Vector2D{(int)j, (int)i});
            }
        }
    }
}