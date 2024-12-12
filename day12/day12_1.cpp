#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <algorithm>

struct Vector2D {
    int x;
    int y;
};

struct Node {
    int id;
    int neighbour_count;
    int* neighbours;
};

template<typename T>
bool VectorContains(std::vector<T> vec, T val);
void GetConnectedNodes(Node** nodes, int id, std::vector<int> *result, Vector2D data_size);
int GetPerimeter(char** data, Vector2D start_pos, Vector2D data_size);
void GetConnectedVertical(Node** nodes, int id, std::vector<int> *result, Vector2D data_size);
void GetConnectedHorizontal(Node** nodes, int id, std::vector<int> *result, Vector2D data_size);

int main() {
    FILE* input = fopen("input12.txt", "r");

    char c;
    int height = 0, width = 0;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            height++;
        }
        else {
            width++;
        }
    }
    width /= height;
    fseek(input, 0, SEEK_SET);

    char** data = new char*[height];
    Node** nodes = new Node*[height];
    bool** checked = new bool*[height];
    bool** checked_left = new bool*[height];
    bool** checked_right = new bool*[height];
    bool** checked_up = new bool*[height];
    bool** checked_down = new bool*[height];
    for (int i = 0;i < height;i++) {
        data[i] = new char[width];
        nodes[i] = new Node[width];
        checked[i] = new bool[width];
        checked_left[i] = new bool[width];
        checked_right[i] = new bool[width];
        checked_up[i] = new bool[width];
        checked_down[i] = new bool[width];
        for (int j = 0;j < width;j++) {
            data[i][j] = fgetc(input);
            nodes[i][j] = Node{i * width + j, 0, new int[1]};
            checked[i][j] = false;
            checked_left[i][j] = false;
            checked_right[i][j] = false;
            checked_up[i][j] = false;
            checked_down[i][j] = false;
        }
        fseek(input, 1, SEEK_CUR);
    }

    for (int i = 0;i < height;i++) {
        for (int j = 0;j < width;j++) {
            if (i > 0 && data[i - 1][j] == data[i][j]) {
                if (nodes[i][j].neighbour_count != 0) nodes[i][j].neighbours = (int*)realloc(nodes[i][j].neighbours, sizeof(int) * (nodes[i][j].neighbour_count + 1));
                nodes[i][j].neighbours[nodes[i][j].neighbour_count] = (i - 1) * width + j;
                nodes[i][j].neighbour_count++;
            }
            if (i < height - 1 && data[i + 1][j] == data[i][j]) {
                if (nodes[i][j].neighbour_count != 0) nodes[i][j].neighbours = (int*)realloc(nodes[i][j].neighbours, sizeof(int) * (nodes[i][j].neighbour_count + 1));
                nodes[i][j].neighbours[nodes[i][j].neighbour_count] = (i + 1) * width + j;
                nodes[i][j].neighbour_count++;
            }
            if (j > 0 && data[i][j - 1] == data[i][j]) {
                if (nodes[i][j].neighbour_count != 0) nodes[i][j].neighbours = (int*)realloc(nodes[i][j].neighbours, sizeof(int) * (nodes[i][j].neighbour_count + 1));
                nodes[i][j].neighbours[nodes[i][j].neighbour_count] = i * width + j - 1;
                nodes[i][j].neighbour_count++;
            }
            if (j < width - 1 && data[i][j + 1] == data[i][j]) {
                if (nodes[i][j].neighbour_count != 0) nodes[i][j].neighbours = (int*)realloc(nodes[i][j].neighbours, sizeof(int) * (nodes[i][j].neighbour_count + 1));
                nodes[i][j].neighbours[nodes[i][j].neighbour_count] = i * width + j + 1;
                nodes[i][j].neighbour_count++;
            }

            // for (int k = 0;k < nodes[i][j].neighbour_count;k++) {
            //     printf("%d | ", nodes[i][j].neighbours[k]);
            // }
            // printf("\n");
        }
    }

    int answer = 0;
    for (int i = 0;i < width * height;i++) {
        if (checked[i / width][i % width]) continue;
        std::vector<int> *conns = new std::vector<int>();
        GetConnectedNodes(nodes, i, conns, Vector2D{width, height});
        std::sort(conns->begin(), conns->end());
        int res = 0;
        for (std::size_t j = 0;j < conns->size();j++) {
            int cur_id = (*conns)[j];
            int cur_x = cur_id % width;
            int cur_y = cur_id / width;

            std::vector<int> *conns_v = new std::vector<int>();
            std::vector<int> *conns_h = new std::vector<int>();
            GetConnectedHorizontal(nodes, cur_id, conns_h, Vector2D{width, height});
            GetConnectedVertical(nodes, cur_id, conns_v, Vector2D{width, height});

            std::sort(conns_v->begin(), conns_v->end());

            if (!checked_left[cur_y][cur_x]) {
                if ((cur_x > 0 && data[cur_y][cur_x - 1] != data[cur_y][cur_x]) || cur_x == 0) {
                    checked_left[cur_y][cur_x] = true;
                    for (std::size_t k = 0;k < conns_v->size();k++) {
                        int con_x = (*conns_v)[k] % width;
                        int con_y = (*conns_v)[k] / width;
                        // printf(" - %d %d %d %d\n", data[con_y][con_x], data[con_y][con_x - 1], con_x, con_y);
                        if (data[con_y][con_x] == data[con_y][con_x - 1]) break;
                        checked_left[con_y][con_x] = true;
                    }
                    res++;
                    // printf("|| %d %d %d\n", cur_x, cur_y, res);
                }
            }
            if (!checked_right[cur_y][cur_x]) {
                if ((cur_x < width - 1 && data[cur_y][cur_x + 1] != data[cur_y][cur_x]) || cur_x == width - 1) {
                    checked_right[cur_y][cur_x] = true;
                    for (std::size_t k = 0;k < conns_v->size();k++) {
                        // printf("| %d %ld\n", (*conns_v)[k], j);
                        int con_x = (*conns_v)[k] % width;
                        int con_y = (*conns_v)[k] / width;
                        // printf(" - %d %d %d %d\n", data[con_y][con_x], data[con_y][con_x - 1], con_x, con_y);
                        if (data[con_y][con_x] == data[con_y][con_x + 1]) break;
                        checked_right[con_y][con_x] = true;
                    }
                    res++;
                    // printf("|| %d %d %d\n", cur_x, cur_y, res);
                }
            }
            if (!checked_up[cur_y][cur_x]) {
                if ((cur_y > 0 && data[cur_y - 1][cur_x] != data[cur_y][cur_x]) || cur_y == 0) {
                    checked_up[cur_y][cur_x] = true;
                    for (std::size_t k = 0;k < conns_h->size();k++) {
                        int con_x = (*conns_h)[k] % width;
                        int con_y = (*conns_h)[k] / width;
                        // printf(" - %d %d %d %d\n", data[con_y][con_x], data[con_y][con_x - 1], con_x, con_y);
                        if (!(cur_y == 0) && data[con_y][con_x] == data[con_y - 1][con_x]) break;
                        checked_up[con_y][con_x] = true;
                    }
                    res++;
                    // printf("|| %d %d %d\n", cur_x, cur_y, res);
                }
            }
            if (!checked_down[cur_y][cur_x]) {
                if ((cur_y < height - 1 && data[cur_y + 1][cur_x] != data[cur_y][cur_x]) || cur_y == height - 1) {
                    checked_down[cur_y][cur_x] = true;
                    for (std::size_t k = 0;k < conns_h->size();k++) {
                        int con_x = (*conns_h)[k] % width;
                        int con_y = (*conns_h)[k] / width;
                        // printf(" - %d %d %d %d\n", data[con_y][con_x], data[con_y][con_x - 1], con_x, con_y);
                        if (!(cur_y == height - 1) && data[con_y][con_x] == data[con_y + 1][con_x]) break;
                        checked_down[con_y][con_x] = true;
                    }
                    res++;
                    // printf("|| %d %d %d\n", cur_x, cur_y, res);
                }
            }
            

            // checked[cur_id / width][cur_id % width] = true;
            // res += GetPerimeter(data, Vector2D{cur_id % width, cur_id / width}, Vector2D{width, height});
        }
        // printf("| %d %ld\n", res, conns->size());
        // res *= conns->size();
        answer += res * conns->size();
    }

    printf("%d\n", answer);

    return 0;
}

template<typename T>
bool VectorContains(std::vector<T> vec, T val) {
    for (std::size_t i = 0;i < vec.size();i++) {
        if (vec[i] == val)
            return true;
    }
    return false;
}

void GetConnectedNodes(Node** nodes, int id, std::vector<int> *result, Vector2D data_size) {
    if (VectorContains(*result, nodes[id / data_size.x][id % data_size.x].id)) return;

    int x = id % data_size.x;
    int y = id / data_size.x;
    result->push_back(nodes[y][x].id);

    for (int i = 0;i < nodes[y][x].neighbour_count;i++) {
        GetConnectedNodes(nodes, nodes[y][x].neighbours[i], result, data_size);
    }
}

void GetConnectedVertical(Node** nodes, int id, std::vector<int> *result, Vector2D data_size) {
    if (VectorContains(*result, nodes[id / data_size.x][id % data_size.x].id)) return;

    int x = id % data_size.x;
    int y = id / data_size.x;
    result->push_back(nodes[y][x].id);

    for (int i = 0;i < nodes[y][x].neighbour_count;i++) {
        if (abs(y - nodes[y][x].neighbours[i] / data_size.x) == 1 && nodes[y][x].neighbours[i] / data_size.x > y) {
            // printf(" - %d %d\n", id, nodes[y][x].neighbours[i]);
            // printf(" - %d %d\n", y, nodes[y][x].neighbours[i] / data_size.x);
            GetConnectedVertical(nodes, nodes[y][x].neighbours[i], result, data_size);
        }
    }
}

void GetConnectedHorizontal(Node** nodes, int id, std::vector<int> *result, Vector2D data_size) {
    if (VectorContains(*result, nodes[id / data_size.x][id % data_size.x].id)) return;

    int x = id % data_size.x;
    int y = id / data_size.x;
    result->push_back(nodes[y][x].id);

    for (int i = 0;i < nodes[y][x].neighbour_count;i++) {
        if (abs(x - nodes[y][x].neighbours[i] % data_size.x) == 1 && nodes[y][x].neighbours[i] % data_size.x > x) {
            // printf(" - %d %d\n", id, nodes[y][x].neighbours[i]);
            // printf(" - %d %d\n", y, nodes[y][x].neighbours[i] / data_size.x);
            GetConnectedHorizontal(nodes, nodes[y][x].neighbours[i], result, data_size);
        }
    }
}

int GetPerimeter(char** data, Vector2D start_pos, Vector2D data_size) {
    int result = 0;
    char id = data[start_pos.y][start_pos.x];

    if (start_pos.x > 0 && data[start_pos.y][start_pos.x - 1] != id) result++;
    else if (start_pos.x == 0) result++;
    if (start_pos.x < data_size.x - 1 && data[start_pos.y][start_pos.x + 1] != id) result++;
    else if (start_pos.x == data_size.x - 1) result++;
    if (start_pos.y > 0 && data[start_pos.y - 1][start_pos.x] != id) result++;
    else if (start_pos.y == 0) result++;
    if (start_pos.y < data_size.y - 1 && data[start_pos.y + 1][start_pos.x] != id) result++;
    else if (start_pos.y == data_size.y - 1) result++;

    return result;
}