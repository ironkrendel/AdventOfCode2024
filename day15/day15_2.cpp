#include <stdio.h>
#include <vector>
#include <chrono>
#include <thread>

inline void PrintData(char** data, int width, int height, int pos_x, int pos_y);
#define PRINTDATA PrintData(data, width, height, pos_x, pos_y)

bool CanMove(char** data, int pos_x, int pos_y, int delta_x, int delta_y);
void Move(char** data, int pos_x, int pos_y, int delta_x, int delta_y);

template<typename T>
bool VectorContains(std::vector<T> vec, T val) {
    for (std::size_t i = 0;i < vec.size();i++) {
        if (vec[i] == val)
            return true;
    }
    return false;
}

int main() {
    FILE* input = fopen("input15.txt", "r");

    char c;
    std::vector<char> moves;
    int height = 0, width = 0;
    int state = 0;
    while ((c = fgetc(input)) != EOF) {
        if (state == 0) {
            if (c == '\n') {
                height++;
                if (fgetc(input) == '\n') {
                    state = 1;
                }
                else {
                    fseek(input, -1, SEEK_CUR);
                }
            }
            else {
                width++;
            }
        }
        else if (state == 1) {
            if (c == '\n') {

            }
            else {
                moves.push_back(c);
            }
        }
    }
    width = width / height;
    width *= 2;
    fseek(input, 0, SEEK_SET);

    char** data = new char*[height];
    int pos_x, pos_y;

    for (int i = 0;i < height;i++) {
        data[i] = new char[width * 2];
        for (int j = 0;j < width;j+=2) {
            data[i][j] = fgetc(input);
            if (data[i][j] == '@') {
                pos_x = j;
                pos_y = i;
                data[i][j] = '.';
                data[i][j + 1] = '.';
            }
            else if (data[i][j] == 'O') {
                data[i][j] = '0';
                data[i][j + 1] = 'O';
            }
            else {
                data[i][j + 1] = data[i][j];
            }
        }
        fseek(input, 1, SEEK_CUR);
    }

    // PRINTDATA;

    for (std::size_t i = 0;i < moves.size();i++) {
        int delta_x = 0, delta_y = 0;
        if (moves[i] == '<') {
            delta_x = -1;
        }
        else if (moves[i] == '^') {
            delta_y = -1;
        }
        else if (moves[i] == '>') {
            delta_x = 1;
        }
        else if (moves[i] == 'v') {
            delta_y = 1;
        }

        // PRINTDATA;

        if (data[pos_y + delta_y][pos_x + delta_x] == '#') continue;

        if (data[pos_y + delta_y][pos_x + delta_x] == '.') {
            pos_x += delta_x;
            pos_y += delta_y;
            continue;
        }

        if (data[pos_y + delta_y][pos_x + delta_x] == 'O' || data[pos_y + delta_y][pos_x + delta_x] == '0') {
            int start_x = pos_x + delta_x;
            int start_y = pos_y + delta_y;
            int fin_x = pos_x + delta_x * 2;
            int fin_y = pos_y + delta_y * 2;
            if (delta_y == 0) {
                while (data[fin_y][fin_x] == 'O' || data[fin_y][fin_x] == '0') fin_x += delta_x;
                if (data[fin_y][fin_x] == '.') {
                    pos_x += delta_x;
                    pos_y += delta_y;
                    if (delta_x < 0) {
                        for (int i = fin_x;i < start_x;i++) {
                            data[fin_y][i] = data[fin_y][i + 1];
                        }
                        data[start_y][start_x] = '.';
                    }
                    else {
                        for (int i = fin_x;i > start_x;i--) {
                            data[fin_y][i] = data[fin_y][i - 1];
                        }
                        data[start_y][start_x] = '.';
                    }
                }
            }
            if (delta_x == 0) {
                if (CanMove(data, pos_x + delta_x, pos_y + delta_y, delta_x, delta_y)) {
                    pos_x += delta_x;
                    pos_y += delta_y;
                    Move(data, pos_x, pos_y, delta_x, delta_y);
                }
            }
        }
    }

    int answer = 0;
    for (int i = 0;i < height;i++) {
        for (int j = 0;j < width;j++) {
            if (data[i][j] == '0') {
                answer += i * 100 + j;
            }
        }
    }

    // PRINTDATA;

    printf("%d\n", answer);

    return 0;
}

inline void PrintData(char** data, int width, int height, int pos_x, int pos_y) {
    for (int i = 0;i < height;i++) {
        for (int j = 0;j < width;j++) {
            if (i == pos_y && j == pos_x) {
                printf("@");
            }
            else if (data[i][j] == '0') {
                printf("[");
            }
            else if (data[i][j] == 'O') {
                printf("]");
            }
            else {
                printf("%c", data[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");

    // std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

bool CanMove(char** data, int pos_x, int pos_y, int delta_x, int delta_y) {
    if (data[pos_y][pos_x] == '.') return true;
    if (data[pos_y][pos_x] == '0') {
        if (data[pos_y + delta_y][pos_x + delta_x] == '#') return false;
        if (data[pos_y + delta_y][pos_x + delta_x + 1] == '#') return false;
        return CanMove(data, pos_x + 1, pos_y + delta_y, delta_x, delta_y) && CanMove(data, pos_x, pos_y + delta_y, delta_x, delta_y);
    }
    else if (data[pos_y][pos_x] == 'O') {
        if (data[pos_y + delta_y][pos_x + delta_x] == '#') return false;
        if (data[pos_y + delta_y][pos_x + delta_x - 1] == '#') return false;
        return CanMove(data, pos_x - 1, pos_y + delta_y, delta_x, delta_y) && CanMove(data, pos_x, pos_y + delta_y, delta_x, delta_y);
    }

    return true;
}

void Move(char** data, int pos_x, int pos_y, int delta_x, int delta_y) {
    if (data[pos_y][pos_x] == '.') return;
    if (data[pos_y][pos_x] == '0') {
        if (data[pos_y + delta_y][pos_x + delta_x] == '.' && data[pos_y + delta_y][pos_x + delta_x + 1] == '.') {
            data[pos_y][pos_x] = '.';
            data[pos_y][pos_x + 1] = '.';
            data[pos_y + delta_y][pos_x + delta_x] = '0';
            data[pos_y + delta_y][pos_x + delta_x + 1] = 'O';
        }
        else {
            Move(data, pos_x + delta_x, pos_y + delta_y, delta_x, delta_y);
            Move(data, pos_x + delta_x + 1, pos_y + delta_y, delta_x, delta_y);
            data[pos_y][pos_x] = '.';
            data[pos_y][pos_x + 1] = '.';
            data[pos_y + delta_y][pos_x + delta_x] = '0';
            data[pos_y + delta_y][pos_x + delta_x + 1] = 'O';
        }
    }
    else if (data[pos_y][pos_x] == 'O') {
        if (data[pos_y + delta_y][pos_x + delta_x] == '.' && data[pos_y + delta_y][pos_x + delta_x - 1] == '.') {
            data[pos_y][pos_x] = '.';
            data[pos_y][pos_x - 1] = '.';
            data[pos_y + delta_y][pos_x + delta_x] = 'O';
            data[pos_y + delta_y][pos_x + delta_x - 1] = '0';
        }
        else {
            Move(data, pos_x + delta_x, pos_y + delta_y, delta_x, delta_y);
            Move(data, pos_x + delta_x - 1, pos_y + delta_y, delta_x, delta_y);
            data[pos_y][pos_x] = '.';
            data[pos_y][pos_x - 1] = '.';
            data[pos_y + delta_y][pos_x + delta_x] = 'O';
            data[pos_y + delta_y][pos_x + delta_x - 1] = '0';
        }
    }
}