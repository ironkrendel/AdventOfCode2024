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
char GetDirectionChar(MoveDelta* dir);
bool IsDeadlocked(char** data, MoveDelta data_size, MoveDelta obstruct_pos);

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
    char** visit_direction = new char*[height];
    for (int i = 0;i < height;i++) {
        data[i] = new char[width];
        visited[i] = new bool[width];
        visit_direction[i] = new char[width];
        for (int j = 0;j < width;j++) {
            data[i][j] = fgetc(input);
            visited[i][j] = false;
            visit_direction[i][j] = ' ';
            if (data[i][j] == '^') {
                pos_x = j;
                pos_y = i;
                visited[i][j] = true;
                visit_direction[i][j] = 'U';
            }
        }
        fseek(input, 1, SEEK_CUR);
    }

    fclose(input);

    int result = 0;
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

    result = 0;
    for (int i = 0;i < height;i++) {
        for (int j = 0;j < width;j++) {
            if (visited[i][j]) {
                result++;
            }
        }
    }

    // for (int i = 0;i < height;i++) {
    //     for (int j = 0;j < width;j++) {
    //         if (visited[i][j]) {
    //             printf("X");
    //         }
    //         else {
    //             printf("%c", data[i][j]);
    //         }
    //     }
    //     printf("\n");
    // }

    printf("part 1: %d\n", result);

    result = 0;
    for (int i = 0;i < height;i++) {
        for (int j = 0;j < width;j++) {
            // printf("%d %d %d\n", j, i, IsDeadlocked(data, {width, height}, {j, i}, visited));
            if (IsDeadlocked(data, {width, height}, {j, i})) {
                // printf("%d %d\n", j, i);
                result++;
            }
        }
    }

    printf("part 2: %d\n", result);
    
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

char GetDirectionChar(MoveDelta* dir) {
    if(dir->x == 0 && dir->y == -1) {
        return 'U';
    }
    else if (dir->x == 0 && dir->y == 1) {
        return 'D';
    }
    else if (dir->x == 1 && dir->y == 0) {
        return 'R';
    }
    else if (dir->x == -1 && dir->y == 0) {
        return 'L';
    }
    return ' ';
}

bool IsDeadlocked(char** data, MoveDelta data_size, MoveDelta obstruct_pos) {
    int height = data_size.y;
    int width = data_size.x;
    bool** visited = new bool*[height];
    char** visit_direction = new char*[height];
    int pos_x = 0, pos_y = 0;

    if (data[obstruct_pos.y][obstruct_pos.x] == '#') {
        return false;
    }

    for (int i = 0;i < height;i++) {
        visited[i] = new bool[width];
        visit_direction[i] = new char[width];
        for (int j = 0;j < width;j++) {
            visited[i][j] = false;
            visit_direction[i][j] = ' ';
            if (data[i][j] == '^') {
                pos_x = j;
                pos_y = i;
                visited[i][j] = true;
                visit_direction[i][j] = 'U';
            }
        }
    }

    if ((obstruct_pos.x == pos_x && obstruct_pos.y == pos_y) || (data[pos_y][pos_x] == '#')) {
        return false;
    }

    MoveDelta direction = UP;
    int move_count = 0;
    while (pos_x >= 0 && pos_x < width && pos_y >= 0 && pos_y < height) {
        if ((pos_x + direction.x < 0) || (pos_x + direction.x >= width)\
         || (pos_y + direction.y < 0) || (pos_y + direction.y >= height)) {
            return false;
        }
        // printf(" - %d %d\n", pos_x, pos_y);
        if (data[pos_y + direction.y][pos_x + direction.x] == '#') {
            // printf(" - - %d %d\n", (pos_x + direction.x), (pos_y + direction.y));
            Rotate(&direction);
        }
        else if (((pos_x + direction.x) == obstruct_pos.x && (pos_y + direction.y) == obstruct_pos.y)) {
            // printf(" - - %d %d %d %d\n", (pos_x + direction.x), obstruct_pos.x, (pos_y + direction.y), obstruct_pos.y);
            Rotate(&direction);
        }
        else {
            visited[pos_y][pos_x] = true;
            visit_direction[pos_y][pos_x] = GetDirectionChar(&direction);
            pos_x += direction.x;
            pos_y += direction.y;
            move_count++;
        }
        if (visited[pos_y][pos_x] && visit_direction[pos_y][pos_x] == GetDirectionChar(&direction) && move_count > 0) {
            // printf(" -t\n");
            return true;
        }
    }
    return false;
}