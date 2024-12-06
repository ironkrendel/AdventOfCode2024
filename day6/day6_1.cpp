#include <stdio.h>

struct MoveDelta {
    int x = 0;
    int y = 0;
};

#define UP    {0, -1}
#define DOWN  {0, 1}
#define LEFT  {-1, 0}
#define RIGHT {1, 0}

void Rotate(MoveDelta* dir);

int main() {
    FILE *input;
    input = fopen("input6.txt", "r");

    char c;
    int height = 0;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n')
            height++;
    }
    fseek(input, 0, SEEK_SET);

    int width = 0;
    while ((c = fgetc(input)) != '\n') {
        width++;
    }
    fseek(input, 0, SEEK_SET);

    MoveDelta direction = UP;
    int pos_x = 0, pos_y = 0;

    char** data = new char*[height];
    bool** visited = new bool*[height];
    for (int i = 0;i < height;i++) {
        data[i] = new char[width];
        visited[i] = new bool[width];
        for (int j = 0;j < width;j++) {
            data[i][j] = fgetc(input);
            visited[i][j] = false;
            if (data[i][j] == '^') {
                pos_x = j;
                pos_y = i;
                visited[i][j] = true;
            }
        }
        fseek(input, 1, SEEK_CUR);
    }

    fclose(input);

    while (pos_x >= 0 && pos_x < width && pos_y >= 0 && pos_y < height) {
        if ((pos_x + direction.x < 0) || (pos_x + direction.x >= width)\
         || (pos_y + direction.y < 0) || (pos_y + direction.y >= height)) {
            break;
        }
        if (data[pos_y + direction.y][pos_x + direction.x] == '#') {
            Rotate(&direction);
        }
        pos_x += direction.x;
        pos_y += direction.y;
        visited[pos_y][pos_x] = true;
    }

    int result = 0;
    for (int i = 0;i < height;i++) {
        for (int j = 0;j < width;j++) {
            if (visited[i][j]) {
                result++;
            }
        }
    }

    for (int i = 0;i < height;i++) {
        for (int j = 0;j < width;j++) {
            if (visited[i][j]) {
                printf("X");
            }
            else {
                printf("%c", data[i][j]);
            }
        }
        printf("\n");
    }

    printf("%d\n", result);
    
    return 0;
}

void Rotate(MoveDelta* dir) {
    if(dir->x == 0 && dir->y == -1) {
        dir->x = 1;
        dir->y = 0;
    }
    else if (dir->x == 0 && dir->y == 1) {
        dir->x = -1;
        dir->y = 0;
    }
    else if (dir->x == 1 && dir->y == 0) {
        dir->x = 0;
        dir->y = 1;
    }
    else if (dir->x == -1 && dir->y == 0) {
        dir->x = 0;
        dir->y = -1;
    }
}