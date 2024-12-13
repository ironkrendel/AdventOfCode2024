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
inline bool IsInbounds(Vector2D pos, Vector2D data_size);
int IsCorner(char** data, Vector2D start_pos, Vector2D data_size);

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
    for (int i = 0;i < height;i++) {
        data[i] = new char[width];
        nodes[i] = new Node[width];
        checked[i] = new bool[width];
        for (int j = 0;j < width;j++) {
            data[i][j] = fgetc(input);
            nodes[i][j] = Node{i * width + j, 0, new int[1]};
            checked[i][j] = false;
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
        }
    }

    int answer = 0;

    for (int i = 0;i < width * height;i++) {
        if (checked[i / width][i % width]) continue;

        std::vector<int> *result = new std::vector<int>();
        GetConnectedNodes(nodes, i, result, Vector2D{width, height});

        int res = 0;
        checked[i / width][i % width] = true;
        for (std::size_t j = 0;j < result->size();j++) {
            int cur_node_id = (*result)[j];
            checked[cur_node_id / width][cur_node_id % width] = true;

            res += IsCorner(data, Vector2D{cur_node_id % width, cur_node_id / width}, Vector2D{width, height});
        }
        answer += res * result->size();
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

inline bool IsInbounds(Vector2D pos, Vector2D data_size) {
    if (pos.x < 0) return false;
    if (pos.y < 0) return false;
    if (pos.x >= data_size.x) return false;
    if (pos.y >= data_size.y) return false;
    return true;
}

int IsCorner(char** data, Vector2D start_pos, Vector2D data_size) {
    bool outer_corner[3][3] = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};

    int answer = 0;

    int rotations_x[4] = {-1, 0, 0, -1};
    int rotations_y[4] = {-1, -1, 0, 0};
    for (int n = 0;n < 4;n++) {
        bool result = true;
        int delta_x = rotations_x[n];
        int delta_y = rotations_y[n];
        for (int i = (0 + delta_y);i < (2 + delta_y);i++) {
            for (int j = (0 + delta_x);j < (2 + delta_x);j++) {
                if (!IsInbounds(Vector2D{start_pos.x + j, start_pos.y + i}, data_size)) {
                    continue;
                }
                if ((data[start_pos.y][start_pos.x] == data[start_pos.y + i][start_pos.x + j]) != outer_corner[i + 1][j + 1]) result = false;
            }
            if (!result) break;
        }
        if (result) {
            answer++;
        }
    }

    bool inner_corner[4][3][3] = {{{0, 1, 1}, {1, 1, 1}, {1, 1, 1}}, {{1, 1, 0}, {1, 1, 1}, {1, 1, 1}}, {{1, 1, 1}, {1, 1, 1}, {1, 1, 0}}, {{1, 1, 1}, {1, 1, 1}, {0, 1, 1}}};
    bool touching_corner_outer[4][3][3] = {{{1, 0, 1}, {0, 1, 1}, {1, 1, 1}}, {{1, 0, 1}, {1, 1, 0}, {1, 1, 1}}, {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}}, {{1, 1, 1}, {0, 1, 1}, {1, 0, 1}}};
    for (int n = 0;n < 4;n++) {
        bool result_1 = true;
        bool result_2 = true;
        int delta_x = rotations_x[n];
        int delta_y = rotations_y[n];
        for (int i = (0 + delta_y);i < (2 + delta_y);i++) {
            for (int j = (0 + delta_x);j < (2 + delta_x);j++) {
                if (!IsInbounds(Vector2D{start_pos.x + j, start_pos.y + i}, data_size)) {
                    if (inner_corner[n][i + 1][j + 1] == true) result_1 = false;
                    if (touching_corner_outer[n][i + 1][j + 1] == true) result_2 = false;
                    continue;
                }
                if ((data[start_pos.y][start_pos.x] == data[start_pos.y + i][start_pos.x + j]) != inner_corner[n][i + 1][j + 1]) result_1 = false;
                if ((data[start_pos.y][start_pos.x] == data[start_pos.y + i][start_pos.x + j]) != touching_corner_outer[n][i + 1][j + 1]) result_2 = false;
            }
        }
        if (result_1) {
            answer++;
        }
        if (result_2) {
            answer++;
        }
    }

    return answer;
}