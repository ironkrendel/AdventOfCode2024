#include <stdio.h>
#include <vector>
#include <unordered_map>

bool check_update(std::vector<int> *update, std::unordered_map<int, std::vector<int>*> *rules);
void fix_update(std::vector<int> *update, std::unordered_map<int, std::vector<int>*> *rules);

int main() {
    FILE *input;
    input = fopen("input5.txt", "r");

    std::unordered_map<int, std::vector<int>*> rules;
    std::vector<std::vector<int>*> updates;

    int a, b;
    char c;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            break;
        }
        else {
            fseek(input, -1, SEEK_CUR);
            fscanf(input, "%d|%d", &a, &b);
            if (rules[a] == nullptr) {
                rules[a] = new std::vector<int>;
            }
            rules[a]->push_back(b);
            fseek(input, 1, SEEK_CUR);
        }
    }

    std::vector<int>* line = new std::vector<int>;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            updates.push_back(line);
            line = new std::vector<int>;
        }
        else if (c == ',') {
            continue;
        }
        else {
            fseek(input, -1, SEEK_CUR);
            fscanf(input, "%d", &a);
            line->push_back(a);
        }
    }

    fclose(input);

    int result = 0;
    for (int i = 0;i < updates.size();i++) {
        bool flag = check_update(updates[i], &rules);

        // if (flag) {
        //     int middle = updates[i]->size() / 2;
        //     result += (*updates[i])[middle];
        // }

        if (!flag) {
            while (!check_update(updates[i], &rules)) {
                fix_update(updates[i], &rules);
            }

            int middle = updates[i]->size() / 2;
            result += (*updates[i])[middle];
        }
    }

    printf("%d\n", result);
    
    return 0;
}

bool check_update(std::vector<int> *update, std::unordered_map<int, std::vector<int>*> *rules) {
    std::unordered_map<int, int> number_counters;

    for (int i = 0;i < update->size();i++) {
        int cur_num = (*update)[i];
        number_counters[cur_num]++;
        if ((*rules)[cur_num] == nullptr) continue;
        for (int j = 0;j < (*rules)[cur_num]->size();j++) {
            if (number_counters[(*(*rules)[cur_num])[j]] > 0) {
                return false;
            }
        }
    }

    return true;
}

void fix_update(std::vector<int> *update, std::unordered_map<int, std::vector<int>*> *rules) {
    std::unordered_map<int, int> number_counters;
    int tmp, index1, index2;

    for (int i = 0;i < update->size();i++) {
        int cur_num = (*update)[i];
        number_counters[cur_num]++;
        if ((*rules)[cur_num] == nullptr) continue;
        for (int j = 0;j < (*rules)[cur_num]->size();j++) {
            if (number_counters[(*(*rules)[cur_num])[j]] > 0) {
                index1 = i;
                for (int k = 0;k < update->size();k++) {
                    if ((*update)[k] == (*(*rules)[cur_num])[j]) {
                        index2 = k;
                        break;
                    }
                }

                tmp = (*update)[index2];
                (*update)[index2] = (*update)[index1];
                (*update)[index1] = tmp;

                return;
            }
        }
    }
}