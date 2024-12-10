#include <stdio.h>
#include <vector>

struct Vector2D {
    int x;
    int y;
};

int GetTrailScore(std::vector<std::vector<int>*> data, Vector2D start_pos, bool** visited);

int main() {
    FILE* input = fopen("input10.txt", "r");

    std::vector<std::vector<int>*> data;
    std::vector<Vector2D> starts;

    char c;
    std::vector<int>* line = new std::vector<int>;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            data.push_back(line);
            line = new std::vector<int>;
        }
        else {
            line->push_back(c - '0');
        }
    }
    delete line;

    for (size_t i = 0;i < data.size();i++) {
        for (size_t j = 0;j < data[0]->size();j++) {
            if ((*data[i])[j] == 0) {
                starts.push_back(Vector2D{static_cast<int>(j), static_cast<int>(i)});
            }
        }
    }

    int result = 0;
    for (size_t i = 0;i < starts.size();i++) {
        bool** visited = new bool*[data.size()];
        for (size_t j = 0;j < data.size();j++) {
            visited[j] = new bool[data[0]->size()];
        }
        for (size_t j = 0;j < data.size();j++) {
            for (size_t k = 0;k < data[0]->size();k++) {
                visited[j][k] = false;
            }
        }

        result += GetTrailScore(data, starts[i], visited);
    }

    printf("%d\n", result);

    return 0;
}

int GetTrailScore(std::vector<std::vector<int>*> data, Vector2D start_pos, bool** visited) {
    int current_val = (*data[start_pos.y])[start_pos.x];

    if (current_val == 9) {
        // if (visited[start_pos.y][start_pos.x]) return 0; // part1
        visited[start_pos.y][start_pos.x] = true;
        return 1;
    }

    int result = 0;
    if (start_pos.y > 0) {
        if ((*data[start_pos.y - 1])[start_pos.x] == (current_val + 1))
            result += GetTrailScore(data, Vector2D{start_pos.x, start_pos.y - 1}, visited);
    }
    if (start_pos.y < (int)data.size() - 1) {
        if ((*data[start_pos.y + 1])[start_pos.x] == (current_val + 1))
            result += GetTrailScore(data, Vector2D{start_pos.x, start_pos.y + 1}, visited);
    }
    if (start_pos.x > 0) {
        if ((*data[start_pos.y])[start_pos.x - 1] == (current_val + 1))
            result += GetTrailScore(data, Vector2D{start_pos.x - 1, start_pos.y}, visited);
    }
    if (start_pos.x < (int)data.size() - 1) {
        if ((*data[start_pos.y])[start_pos.x + 1] == (current_val + 1))
            result += GetTrailScore(data, Vector2D{start_pos.x + 1, start_pos.y}, visited);
    }

    return result;
}