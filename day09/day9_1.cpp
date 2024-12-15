#include <stdio.h>
#include <vector>
#include <unordered_map>

struct DiskBlock {
    int size;
    unsigned long long start;
    void* next_block;
};

int main() {
    FILE* input = fopen("input9.txt", "r");

    char c;
    int size;
    unsigned long long id = 0;
    bool file = true;
    std::vector<unsigned long long> res_string;
    std::unordered_map<unsigned long long, DiskBlock> files;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\n') {
            id--;
            break;
        }
        size = c - '0';
        if (file) {
            files[id] = DiskBlock{size, res_string.size(), nullptr};
            if (id > 0) {
                files[id - 1].next_block = &files[id];
            }
            for (int i = 0;i < size;i++) {
                res_string.push_back(id);
            }
            id++;
            file = false;
        }
        else {
            for (int i = 0;i < size;i++) {
                res_string.push_back(-1);
            }
            file = true;
        }
    }
    int max_id = id;

    for (unsigned long long i = 0;i < res_string.size();i++) {
        if (res_string[i] == -1) {
            printf(".");
        }
        else {
            printf("%d", res_string[i]);
        }
    }
    printf("\n");

    for (int i = max_id;i > 0;i--) {
        DiskBlock* cur_block = &files[0];
        while (cur_block->start < files[i].start) {
            DiskBlock* next_block = (DiskBlock*)cur_block->next_block;
            if (next_block->start - cur_block->start - cur_block->size >= files[i].size) {
                files[i].next_block = cur_block->next_block;
                files[i].start = cur_block->start + cur_block->size;
                files[i - 1].next_block = nullptr;
                cur_block->next_block = &files[i];
                break;
            }
            cur_block = (DiskBlock*)cur_block->next_block;
        }
    }

    for (int i = 0;i < res_string.size();i++) {
        res_string[i] = -1;
    }
    for (int i = 0;i <= max_id;i++) {
        for (int j = files[i].start;j < files[i].start + files[i].size;j++) {
            printf("%d %d\n", i, j);
            res_string[j] = i;
        }
    }

    for (unsigned long long i = 0;i < res_string.size();i++) {
        if (res_string[i] == -1) {
            printf(".");
        }
        else {
            printf("%d", res_string[i]);
        }
    }
    printf("\n");

    unsigned long long result = 0;
    for (unsigned long long i = 0;i < res_string.size();i++) {
        if (res_string[i] != -1) {
            result += i * res_string[i];
        }
    }

    printf("%lld\n", result);

    return 0;
}